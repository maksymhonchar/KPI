import os
from flask import render_template, redirect, url_for, abort, flash, request, current_app, send_from_directory, jsonify
from flask_login import login_required, current_user
from . import main
from .forms import EditProfileForm, PostForm, CommentForm, AvatarForm, EditCommentForm, DevBugForm, SearchForm, DeletePostForm
from .. import db
from ..models import Permission, User, Post, Comment, Fave, DevBug
from ..decorators import permission_required


@main.before_app_request
def before_request():
    if current_user.is_authenticated:
        current_user.ping()


@main.route('/favicon.ico')
def favicon():
    return send_from_directory(
        os.path.join(current_app.root_path, 'static/img'),
        'favicon.ico',
        mimetype='image/vnd.microsoft.icon'
    )


@main.route('/')
def index():
    if current_user.is_authenticated:
        return redirect(url_for('main.feed'))
    return redirect(url_for('main.greetings'))


@main.route('/greetings')
def greetings():
    return render_template('greetings.html')


@main.route('/about')
def about():
    return render_template('about.html')


@main.route('/contacts')
def contacts():
    return render_template('contacts.html')


@main.route('/dev')
def dev():
    return render_template('dev.html')


@main.route('/bugtracker', methods=['GET', 'POST'])
def bugtracker():
    bugs = DevBug.query.all()
    form = DevBugForm()
    if form.validate_on_submit():
        bug_to_add = DevBug(
            title=form.title.data,
            body=form.body.data
        )
        db.session.add(bug_to_add)
        flash('Заявка на решение бага была отправлена.')
        return redirect(url_for('main.bugtracker'))
    return render_template('bugtracker.html', bugs=bugs, form=form)


@main.route('/legal')
def legal():
    return render_template('legal.html')


@main.route('/feed')
@login_required
def feed():
    page = request.args.get('page', 1, type=int)
    pagination = current_user.followed_posts.order_by(Post.timestamp.desc()).paginate(
        page,
        per_page=current_app.config['WIDT_POSTS_PER_PAGE']
    )
    posts = pagination.items
    return render_template('feed.html', posts=posts, pagination=pagination)


@main.route('/top')
@login_required
def top():
    all_posts = list({faveobj.post for faveobj in Fave.query.all()})
    if all_posts:
        all_posts.sort(key=lambda post_obj: post_obj.faved_by.count(), reverse=True)
        all_posts = all_posts[0:10]
    return render_template('top.html', posts=all_posts)


@main.route('/users', methods=['GET', 'POST'])
@login_required
def users():
    form = SearchForm()
    page = request.args.get('page', 1, type=int)
    pagination = User.query.order_by(User.id.desc()).paginate(
        page,
        per_page=current_app.config['WIDT_USERS_PER_PAGE']
    )
    pag_users = pagination.items
    return render_template('users.html', users=pag_users, pagination=pagination, form=form)


@main.route('/u/<username>', methods=['GET', 'POST'])
@login_required
def user(username):
    form = PostForm()
    if current_user.can(Permission.WRITE_ARTICLES) and \
            form.validate_on_submit():
        post_to_add = Post(
            title=form.title.data,
            body=form.body.data,
            author=User.query.get(current_user.id)
        )
        db.session.add(post_to_add)
        return redirect(url_for('main.user', username=current_user.username))
    user_to_display = User.query.filter_by(username=username).first_or_404()
    page = request.args.get('page', 1, type=int)
    pagination = user_to_display.posts.order_by(Post.timestamp.desc()).paginate(
        page,
        per_page=current_app.config['WIDT_POSTS_PER_PAGE'],
        error_out=True
    )
    posts = pagination.items
    is_owner = current_user.username == username
    return render_template(
        'user.html',
        user=user_to_display, posts=posts, pagination=pagination, form=form, is_owner=is_owner
    )


@main.route('/u/settings', methods=['GET', 'POST'])
@login_required
def settings():
    form = EditProfileForm()
    if form.validate_on_submit():
        current_user.name = form.name.data
        current_user.surname = form.surname.data
        current_user.birthday = form.birthday.data
        current_user.location = form.location.data
        current_user.about = form.about_me.data
        db.session.add(current_user)
        flash('Ваш профиль успешно обновлен.')
        return redirect(url_for('main.user', username=current_user.username))
    form.name.data = current_user.name
    form.surname.data = current_user.surname
    form.birthday.data = current_user.birthday
    form.location.data = current_user.location
    form.about_me.data = current_user.about
    return render_template('settings.html', form=form)


@main.route('/u/settings/avatar', methods=['GET', 'POST'])
@login_required
def upload_avatar():
    form = AvatarForm()
    if form.validate_on_submit():
        current_user.avatar = form.avatar.data.read()
        flash('Фотография профиля обновлена.')
        return redirect(url_for('main.user', username=current_user.username))
    else:
        filename = None
    return render_template('upload_avatar.html', form=form, filename=filename)


@main.route('/u/pics/<int:id>')
@login_required
def userpic(id):
    pic_owner = User.query.get_or_404(id)
    return current_app.response_class(pic_owner.avatar, mimetype='application/octet-stream')


@main.route('/p/<int:id>', methods=['GET', 'POST', 'DELETE'])
@login_required
def post(id):
    post = Post.query.get_or_404(id)
    form = CommentForm()
    if form.validate_on_submit():
        comment = Comment(
            body=form.body.data,
            post=post,
            author=User.query.get(current_user.id)
        )
        db.session.add(comment)
        flash('Ваш комментарий был опубликован.')
        return redirect(url_for('main.post', id=post.id, page=-1))

    form_delete = DeletePostForm()
    if form_delete.validate_on_submit():
        fave_obj = Fave.query.filter_by(
            user_id=current_user.id,
            post_id=post.id
        ).first()
        db.session.delete(post)
        if fave_obj:
            db.session.delete(fave_obj)
        flash('Запись была успешно удалена.')
        return redirect(url_for('main.user', username=post.author.username))

    page = request.args.get('page', 1, type=int)
    if page == -1:
        page = (post.comments.count() - 1) // \
                current_app.config['WIDT_COMMENTS_PER_PAGE'] + 1
    pagination = post.comments.order_by(Comment.timestamp.asc()).paginate(
        page,
        per_page=current_app.config['WIDT_COMMENTS_PER_PAGE']
    )
    comments = pagination.items
    text = 'Like'
    if post.is_curuser_liked(current_user.id):
        text = 'Dislike'
    return render_template(
        'post.html',
        post=post, form=form, comments=comments, pagination=pagination, text=text, form_delete=form_delete
    )


@main.route('/p/<int:id>/likes')
@login_required
def likes(id):
    post = Post.query.get_or_404(id)
    return render_template('postlikes.html', post=post, liked_by=post.faved_users())


@main.route('/p/<int:id>/likes/do')
@login_required
def dolike(id):
    post = Post.query.get_or_404(id)
    if not current_user in post.faved_users():
        faveObj = Fave(user_id=current_user.id, post_id=post.id)
        db.session.add(faveObj)
    else:
        faveObj = Fave.query.filter_by(user_id=current_user.id, post_id=post.id).first()
        db.session.delete(faveObj)
    return redirect(url_for('main.post', id=post.id))


@main.route('/p/<int:id>/edit', methods=['GET', 'POST'])
@login_required
def edit(id):
    post = Post.query.get_or_404(id)
    if current_user != post.author and \
            not current_user.can(Permission.ADMINISTER):
        abort(403)
    form = PostForm()
    if form.validate_on_submit():
        post.title = form.title.data
        post.body = form.body.data
        db.session.add(post)
        flash('Ваша запись была обновлена.')
        return redirect(url_for('main.post', id=post.id))
    form.body.data = post.body
    form.title.data = post.title
    return render_template('edit_post.html', form=form, post_id=id, author=post.author.username)


@main.route('/c/<int:id>/')
@login_required
def comment(id):
    comment = Comment.query.get_or_404(id)
    return render_template('comment.html', comment=comment)


@main.route('/c/edit/<int:id>', methods=['GET', 'POST'])
@login_required
def edit_comment(id):
    comment = Comment.query.get_or_404(id)
    if current_user != comment.author and \
            not current_user.can(Permission.ADMINISTER):
        abort(403)
    form = EditCommentForm()
    if form.validate_on_submit():
        comment.body = form.body.data
        flash('Комментарий был обновлен.')
        return redirect(url_for('main.post', id=comment.post.id))
    form.body.data = comment.body
    return render_template('edit_comment.html', form=form, comment=comment)


@main.route('/<username>/follow')
@login_required
@permission_required(Permission.FOLLOW_PERSON)
def follow(username):
    user = User.query.filter_by(username=username).first()
    if user is None:
        flash('Неверный пользователь.')
        return redirect(url_for('main.index'))
    if current_user.is_following(user):
        flash('Вы уже подписаны на этого пользователя.')
        return redirect(url_for('main.user', username=username))
    current_user.follow(user)
    flash('Теперь Вы подписаны на пользователя %s.' % username)
    return redirect(url_for('main.user', username=username))


@main.route('/<username>/unfollow')
@login_required
@permission_required(Permission.FOLLOW_PERSON)
def unfollow(username):
    user = User.query.filter_by(username=username).first()
    if user is None:
        flash('Неверное имя пользователя.')
        return redirect(url_for('main.index'))
    if not current_user.is_following(user):
        flash('Вы не подписаны на этого пользователя.')
        return redirect(url_for('main.user', username=username))
    current_user.unfollow(user)
    flash('Вы успешно отписались от пользователя.')
    return redirect(url_for('main.user', username=username))


@main.route('/<username>/followers')
@login_required
def followers(username):
    user = User.query.filter_by(username=username).first()
    if user is None:
        flash('Неверный пользователь.')
        return redirect(url_for('main.index'))
    page = request.args.get('page', 1, type=int)
    pagination = user.followers.paginate(
        page,
        per_page=current_app.config['WIDT_FOLLOWERS_PER_PAGE'],
        error_out=True
    )
    follows = [
        {'user': item.follower, 'timestamp': item.timestamp}
        for item in pagination.items
    ]
    return render_template(
        'followers.html',
        user=user, title="Подписчики", endpoint='main.followers',
        pagination=pagination, follows=follows
    )


@main.route('/<username>/followed-by')
@login_required
def followed_by(username):
    user = User.query.filter_by(username=username).first()
    if user is None:
        flash('Неверный пользователь.')
        return redirect(url_for('main.index'))
    page = request.args.get('page', 1, type=int)
    pagination = user.followed.paginate(
        page,
        per_page=current_app.config['WIDT_FOLLOWERS_PER_PAGE'],
        error_out=True
    )
    follows = [
        {'user': item.followed, 'timestamp': item.timestamp}
        for item in pagination.items
    ]
    return render_template(
        'followers.html',
        user=user, title="Подписаны на", endpoint='main.followed_by',
        pagination=pagination, follows=follows
    )


@main.route('/search', methods=['GET', 'POST'])
@login_required
def search():
    form = SearchForm()
    all_users = User.query.all()
    search_results = []
    text_to_display = False

    if form.validate_on_submit():
        for user in all_users:
            if user.username.startswith(form.query.data):
                search_results.append(user)
            if user.name.startswith(form.query.data):
                search_results.append(user)
            if user.surname.startswith(form.query.data):
                search_results.append(user)
            text_to_display = True

    return render_template('search.html', form=form, users=search_results, text=text_to_display)
