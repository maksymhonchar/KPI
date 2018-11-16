from flask import jsonify, request, current_app, url_for
from . import api
from ..models import User, Post
from .errors import bad_request


@api.route('/users/')
def get_users():
    offset = request.args.get('offset') or 5
    try:
        offset = int(offset)
    except:
        return bad_request('Bad offset argument.')
    users = User.query.order_by(User.id).slice(0, offset)

    # If request has args on /users/
    if request.args:
        users_GotArg = []
        users_all = User.query.all()
        if request.args.get('fn'):
            for user in users_all:
                if user.name == request.args.get('fn'):
                    users_GotArg.append(user)
        if request.args.get('un'):
            for user in users_all:
                if user.username.startswith(request.args.get('un')):
                    users_GotArg.append(user)
        return jsonify(
            {
                'total': len(users_GotArg),
                'users': [user.to_json() for user in users_GotArg]
            }
        )
    # If it's just a regular request on /users/
    return jsonify(
        {
            'total': User.query.count(),
            'offset': offset,
            'users': [user.to_json() for user in users]
        }
    )


@api.route('/users/<int:id>')
def get_user(id):
    user = User.query.get_or_404(id)
    return jsonify(user.to_json())


@api.route('/users/<int:id>/posts/')
def get_user_posts(id):
    user = User.query.get_or_404(id)
    page = request.args.get('page', 1, type=int)
    pagination = user.posts.order_by(Post.timestamp.desc()).paginate(
        page,
        per_page=current_app.config['WIDT_POSTS_PER_PAGE'],
    )
    posts = pagination.items
    prev_page = None
    if pagination.has_prev:
        prev_page = url_for('api.get_user_posts', id=id, page=page-1, _external=True)
    next_page = None
    if pagination.has_next:
        next_page = url_for('api.get_user_posts', id=id, page=page+1, _external=True)
    return jsonify(
        {
            'count': pagination.total,
            'posts': [post.to_json() for post in posts],
            'prev_page': prev_page,
            'next_page': next_page,
        }
    )


@api.route('/users/<int:id>/feed/')
def get_user_followed_posts(id):
    user = User.query.get_or_404(id)
    page = request.args.get('page', 1, type=int)
    pagination = user.followed_posts.order_by(Post.timestamp.desc()).paginate(
        page,
        per_page=current_app.config['WIDT_POSTS_PER_PAGE']
    )
    posts = pagination.items
    prev_page = None
    if pagination.has_prev:
        prev_page = url_for('api.get_user_followed_posts', id=id, page=page-1, _external=True)
    next_page = None
    if pagination.has_next:
        next_page = url_for('api.get_user_followed_posts', id=id, page=page+1, _external=True)
    return jsonify(
        {
            'posts': [post.to_json() for post in posts],
            'count': pagination.total,
            'prev_page': prev_page,
            'next_page': next_page
        }
    )
