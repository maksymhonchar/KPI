from flask import render_template, current_app, request, redirect, url_for, flash
from flask_login import login_required
from ..main.forms import EditCommentForm, PostForm
from ..models import User, Permission, Comment, Role, Post
from ..decorators import permission_required, admin_required
from .. import db
from .forms import EditProfileAdminForm
from . import administer


@administer.route('/')
@login_required
@admin_required
def admin_index():
    return render_template('admin/index.html')


@administer.route('/users')
@login_required
@admin_required
def admin_users():
    page = request.args.get('page', 1, type=int)
    pagination = User.query.order_by(User.id.asc()).paginate(
        page,
        per_page=current_app.config['WIDT_USERS_PER_PAGE']
    )
    users = pagination.items
    return render_template(
        'admin/users.html',
        users=users, pagination=pagination
    )


@administer.route('/posts')
@login_required
@admin_required
def admin_posts():
    page = request.args.get('page', 1, type=int)
    pagination = Post.query.order_by(Post.id.asc()).paginate(
        page,
        per_page=current_app.config['WIDT_POSTS_PER_PAGE']
    )
    posts = pagination.items
    return render_template(
        'admin/posts.html',
        posts=posts, pagination=pagination
    )


@administer.route('/comments')
@login_required
@admin_required
def admin_comments():
    page = request.args.get('page', 1, type=int)
    pagination = Comment.query.order_by(Comment.timestamp.asc()).paginate(
        page,
        per_page=current_app.config['WIDT_FOLLOWERS_PER_PAGE'],
        error_out=True
    )
    comments = pagination.items
    return render_template(
        'admin/comments.html',
        comments=comments, pagination=pagination
    )


@administer.route('/edit/u/<int:id>', methods=['GET', 'POST'])
@login_required
@admin_required
def edit_profile_admin(id):
    user = User.query.get_or_404(id)
    form = EditProfileAdminForm(user=user)
    if form.validate_on_submit():

        user.email = form.email.data
        user.username = form.username.data
        user.confirmed = form.confirmed.data
        user.role = Role.query.get(form.role.data)
        user.name = form.name.data
        user.surname = form.surname.data
        user.gender = form.gender.data
        user.birthday = form.birthday.data
        user.location = form.location.data
        user.about = form.about_me.data
        db.session.add(user)
        flash('Профиль был обновлен.')
        return redirect(url_for('main.user', username=user.username))
    form.email.data = user.email
    form.username.data = user.username
    form.confirmed.data = user.confirmed
    form.role.data = user.role_id
    form.name.data = user.name
    form.surname.data = user.surname
    form.gender.data = user.gender
    form.birthday.data = user.birthday
    form.location.data = user.location
    form.about_me.data = user.about
    return render_template('admin/edit_profile.html', form=form, user=user)


@administer.route('/edit/p/<int:id>', methods=['GET', 'POST'])
@login_required
@permission_required(Permission.MODERATE_POSTS)
def edit_post_admin(id):
    post = Post.query.get_or_404(id)
    form = PostForm()
    if form.validate_on_submit():
        post.body = form.body.data
        post.title = form.title.data
        db.session.add(post)
        flash('Ваша запись была изменена.')
        return redirect(url_for('main.post', id=id))
    form.body.data = post.body
    form.title.data = post.title
    return render_template('admin/edit_post.html', post=post, form=form)


@administer.route('/enable/<int:id>')
@login_required
@permission_required(Permission.MODERATE_COMMENTS)
def moderate_enable(id):
    comment = Comment.query.get_or_404(id)
    comment.disabled = False
    db.session.add(comment)
    return redirect(
        url_for('main.post', id=comment.post.id)
    )


@administer.route('/disable/<int:id>')
@login_required
@permission_required(Permission.MODERATE_COMMENTS)
def moderate_disable(id):
    comment = Comment.query.get_or_404(id)
    comment.disabled = True
    db.session.add(comment)
    return redirect(
        url_for('main.post', id=comment.post.id)
    )
