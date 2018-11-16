import os
from datetime import datetime
from werkzeug.security import generate_password_hash, check_password_hash
from itsdangerous import TimedJSONWebSignatureSerializer as Serializer
from flask import current_app, url_for
from flask_login import UserMixin, AnonymousUserMixin
from . import db, login_manager
from .exceptions import ValidationError


class Permission:
    FOLLOW_PERSON = 0X01
    LIKE = 0x03
    WRITE_COMMENTS = 0x04
    WRITE_ARTICLES = 0x05
    MODERATE_POSTS = 0x78
    MODERATE_COMMENTS = 0X79
    ADMINISTER = 0X87


class AnonymousUser(AnonymousUserMixin):
    """
    This class overrides AnonymousUser mixin in Flask-login.
    Anonymous User has only read-only rights on the website.
    """
    def can(self, permissions):
        return False

    def is_administrator(self):
        return False

    def __repr__(self):
        return '<Anonymous User>'

login_manager.anonymous_user = AnonymousUser


class Follow(db.Model):
    """
    Association table to represent relations between followers and those, who is followed.
    This table represents self-referential relationship between different Users.
    Fields:
    - timestamp: date, when someone has started following another.
    Relationships:
    follower_id: relation to describe, that User is following someone.
    followed_id: relation to describe, that User is followed by someone.
    """
    __tablename__ = 'follow'

    # General fields.
    timestamp = db.Column(db.DateTime, default=datetime.utcnow)

    # Relationships.
    follower_id = db.Column(db.Integer, db.ForeignKey('users.id'), primary_key=True)
    followed_id = db.Column(db.Integer, db.ForeignKey('users.id'), primary_key=True)


class Role(db.Model):
    """
    A table to represent a Role of the user.
    Possible roles: administrator, moderator, user.
    Default role is a user.
    For detailed info about permissions of certain role, See Permission class.
    Fields:
    - name: name of the role.
    - default: indicator, which shows if role is default.
    - permissions: role permissions.
    Relationships:
    - users: backref to the User instance.
    Methods:
    - insert_roles: method, which inserts all roles to the DB.
    """
    __tablename__ = 'role'
    id = db.Column(db.Integer, primary_key=True)

    # General fields.
    name = db.Column(db.String(64), unique=True)
    default = db.Column(db.Boolean, default=False, index=True)
    permissions = db.Column(db.Integer)

    # Relationships.
    users = db.relationship('User', backref='role', lazy='dynamic')

    @staticmethod
    def insert_roles():
        roles = {
            'User': (
                Permission.FOLLOW_PERSON |
                Permission.LIKE |
                Permission.WRITE_COMMENTS |
                Permission.WRITE_ARTICLES,
                True
            ),
            'Moderator': (
                Permission.FOLLOW_PERSON |
                Permission.LIKE |
                Permission.WRITE_ARTICLES |
                Permission.WRITE_COMMENTS |
                Permission.MODERATE_POSTS |
                Permission.MODERATE_COMMENTS,
                False
            ),
            'Administrator': (
                0xFF,
                False
            )
        }
        for r in roles:
            role = Role.query.filter_by(name=r).first()
            if role is None:
                role = Role(name=r)
            role.permissions = roles[r][0]
            role.default = roles[r][1]
            db.session.add(role)
        db.session.commit()

    def __repr__(self):
        return '<Role %r>' % self.name


class User(UserMixin, db.Model):
    """
    A table to represent a User instance with all relations inside.
    Fields:
    - email: user's email address.
    - username: user's nickname.
    - password_hash: hashed password.
    - confirmed: indicator, which shows, if user has confirmed his email address.
    - last_seen: last time, when the user has done something on the website.
    - member_since: date, when the user has signed up.
    - name: user's first name.
    - surname: user`s last name.
    - gender: user's gender. 1 - male, 0 - female.
    - birthday: a date, when user was born.
    - location: town where the user lives.
    - about: user's information about himself.
    - avatar: base64 representation of users avatar.
    Relationships:
    - role_id: current role of the user. Foreign key, used in 'roles' table.
    - fave: posts, that user has liked. Relation ID to 'faves' table.
    - followed: different Users, that current User is subscribed to.
    - followers: different Users, that are subscribed to current User.
    """
    __tablename__ = 'users'
    id = db.Column(db.Integer, primary_key=True)

    # General fields.
    email = db.Column(db.String(64), unique=True, index=True)
    username = db.Column(db.String(64), unique=True, index=True)
    password_hash = db.Column(db.String(128))
    confirmed = db.Column(db.Boolean, default=False)
    last_seen = db.Column(db.DateTime(), default=datetime.utcnow)
    member_since = db.Column(db.DateTime(), default=datetime.utcnow)

    # More specific fields.
    name = db.Column(db.String(64))
    surname = db.Column(db.String(64))
    gender = db.Column(db.Integer)
    birthday = db.Column(db.Date, default=datetime.utcnow)
    location = db.Column(db.String(64))
    about = db.Column(db.Text())
    avatar = db.Column(db.LargeBinary)

    # Relationships.
    role_id = db.Column(db.Integer, db.ForeignKey('role.id'))
    fave = db.relationship('Fave', backref='user', lazy='dynamic')
    followed = db.relationship(
        'Follow',
        foreign_keys=[Follow.follower_id],
        backref=db.backref(
            'follower',
            lazy='joined'
        ),
        lazy='dynamic',
        cascade='all, delete-orphan'
    )
    followers = db.relationship(
        'Follow',
        foreign_keys=[Follow.followed_id],
        backref=db.backref(
            'followed',
            lazy='joined'
        ),
        lazy='dynamic',
        cascade='all, delete-orphan'
    )
    comments = db.relationship('Comment', backref='author', lazy='dynamic')
    posts = db.relationship('Post', backref='author', lazy='dynamic')

    @property
    def password(self):
        raise AttributeError("Password is not a readable attribute.")

    @password.setter
    def password(self, password):
        self.password_hash = generate_password_hash(password)

    @property
    def followed_posts(self):
        return Post.query.join(
            Follow, Follow.followed_id == Post.author_id
        ).filter(Follow.follower_id == self.id)

    def __init__(self, **kwargs):
        super(User, self).__init__(**kwargs)
        if self.role is None:
            if self.email == current_app.config['WIDT_ADMIN']:
                self.role = Role.query.filter_by(permissions=0xff).first()
                self.confirmed = True
            if self.role is None:
                self.role = Role.query.filter_by(default=True).first()
        self.follow(self)

    def ping(self):
        self.last_seen = datetime.utcnow()
        db.session.add(self)

    def is_online(self):
        date_to_compare = datetime.utcnow()
        if date_to_compare.minute < 5:
            date_to_compare.replace(minute=55)
            try:
                date_to_compare.replace(hour=date_to_compare.hour-1)
            except ValueError:
                date_to_compare.replace(hour=0)
        else:
            date_to_compare = date_to_compare.replace(minute=date_to_compare.minute-5)
        return self.last_seen >= date_to_compare

    def is_following(self, user):
        return self.followed.filter_by(followed_id=user.id).first() is not None

    def is_followed_by(self, user):
        return self.followers.filter_by(follower_id=user.id).first() is not None

    def follow(self, user):
        if not self.is_following(user):
            f = Follow(follower=self, followed=user)
            db.session.add(f)

    def unfollow(self, user):
        f = self.followed.filter_by(followed_id=user.id).first()
        if f:
            db.session.delete(f)

    def verify_password(self, password):
        return check_password_hash(self.password_hash, password)

    def generate_confirmation_token(self, expiration=3600):
        s = Serializer(current_app.config['SECRET_KEY'], expiration)
        return s.dumps({'confirm': self.id})

    def confirm(self, token):
        s = Serializer(current_app.config['SECRET_KEY'])
        try:
            data = s.loads(token)
        except:
            return False
        if data.get('confirm') != self.id:
            return False
        self.confirmed = True
        db.session.add(self)
        return True

    def generate_reset_token(self, expiration=3600):
        s = Serializer(current_app.config['SECRET_KEY'], expiration)
        return s.dumps({'reset': self.id})

    def reset_password(self, token, new_password):
        s = Serializer(current_app.config['SECRET_KEY'])
        try:
            data = s.loads(token)
        except:
            return False
        if data.get('reset') != self.id:
            return False
        self.password = new_password
        db.session.add(self)
        return True

    def generate_email_change_token(self, new_email, expiration=3600):
        s = Serializer(current_app.config['SECRET_KEY'], expiration)
        return s.dumps(
            {
                'change_email': self.id,
                'new_email': new_email
            }
        )

    def change_email(self, token):
        s = Serializer(current_app.config['SECRET_KEY'])
        try:
            data = s.loads(token)
        except:
            return False
        if data.get('change_email') != self.id:
            return False
        if data.get('new_email') is None:
            return False
        new_email = data.get('new_email')
        if self.query.filter_by(email=new_email).first() is not None:
            return False
        self.email = new_email
        db.session.add(self)
        return True

    def generate_auth_token(self, expiration=3600):
        s = Serializer(current_app.config['SECRET_KEY'], expiration)
        return s.dumps({'id': self.id}).decode('ascii')

    def can(self, permissions):
        check_if_can = (self.role.permissions & permissions) == permissions
        return (self.role is not None) and check_if_can

    def is_administrator(self):
        return self.can(Permission.ADMINISTER)

    def to_json(self):
        user_location = ''
        if self.location:
            user_location = "https://maps.google.com/?q=%s" % self.location
        json_user = {
            'id': self.id,
            'url': url_for('api.get_user', id=self.id, _external=True),
            'confirmed': self.confirmed,
            'personal': {
                'username': self.username,
                'first_name': self.name,
                'second_name': self.surname,
                'location': user_location
            },
            'timings': {
                'member_since': self.member_since,
                'last_seen': self.last_seen,
            }
        }
        return json_user

    @staticmethod
    def generate_fake(count=100):
        from sqlalchemy.exc import IntegrityError
        from random import seed, randint
        import forgery_py

        seed()
        for i in range(count):
            u = User(
                email=forgery_py.internet.email_address(),
                username=forgery_py.internet.user_name(True),
                password=forgery_py.lorem_ipsum.word(),
                confirmed=True,
                name=forgery_py.name.first_name(),
                surname=forgery_py.name.last_name(),
                gender=randint(0, 1),
                location=forgery_py.address.city(),
                birthday=forgery_py.date.date(True),
                about=forgery_py.lorem_ipsum.sentence(),
                member_since=forgery_py.date.date(True)
            )
            db.session.add(u)
            try:
                db.session.commit()
            except IntegrityError:
                db.session.rollback()
            except:
                pass

    @staticmethod
    def verify_auth_token(token):
        s = Serializer(current_app.config['SECRET_KEY'])
        try:
            data = s.loads(token)
        except:
            return None
        return User.query.get(data['id'])

    def __repr__(self):
        return '<User %r>' % self.username


class Fave(db.Model):
    """
    Table to represent posts, that was liked by Users in WIDT blog.
    That means, that when User likes a post, a post is appended to fave list.
    Relationships:
    - user_id: key that represents a user, who liked a post. A relation ID to 'users' table.
    - post_id: key that represents a liked post. A relation ID to 'posts' table.
    """
    __tablename__ = 'fave'
    id = db.Column(db.Integer, primary_key=True)

    # Relationships.
    user_id = db.Column(db.Integer, db.ForeignKey('users.id'))
    post_id = db.Column(db.Integer, db.ForeignKey('post.id'))

    def __repr__(self):
        return '<Fave user id%r, post id%r>' % (self.user_id, self.post_id)


class Post(db.Model):
    """
    Table for the Post, written by User.
    Fields:
    - title: title of the post.
    - body: text in the post.
    - timestamp: date, when a post was created.
    - disabled: state, if post was disabled by moderator/admin.
    - category: a category, to which the object belongs.
    Relationships:
    - author_od: a User, who created a post. Foreign key to 'users' table.
    - comments: Comments under the Post. Relation ID to 'comments' table.
    """
    __tablename__ = 'post'
    id = db.Column(db.Integer, primary_key=True)

    # General fields.
    title = db.Column(db.String(128))
    body = db.Column(db.Text)
    timestamp = db.Column(db.DateTime, default=datetime.utcnow)
    disabled = db.Column(db.Boolean, default=False)

    # Relationships.
    author_id = db.Column(db.Integer, db.ForeignKey('users.id'))
    comments = db.relationship('Comment', backref='post', lazy='dynamic')
    faved_by = db.relationship('Fave', backref='post', lazy='dynamic')

    def faved_users(self):
        return [fave.user for fave in Fave.query.filter_by(post_id=self.id).all()]

    def is_curuser_liked(self, user_id):
        return User.query.get(user_id) in self.faved_users()

    def to_json(self):
        json_post = {
            'id': self.id,
            'disabled': self.disabled,
            'author': self.author_id,
            'time_created': self.timestamp,
            'comments': {
                'count': self.comments.count(),
                'link': url_for('api.get_post_comments', id=self.id, _external=True)
            },
            'text': {
                'title': self.title,
                'body': self.body
            }
        }
        return json_post

    @staticmethod
    def from_json(json_post):
        def is_empty(item):
            if item is None or item == '':
                return True
            return False

        body = json_post.get('body')
        title = json_post.get('title')
        if is_empty(body) or is_empty(title):
            raise ValidationError('Post does not have full text structure.')
        return Post(body=body, title=title)

    @staticmethod
    def generate_fake(count=100):
        from random import seed, randint
        import forgery_py

        seed()
        user_count = User.query.count()

        for i in range(count):
            u = User.query.get(randint(0, user_count - 1))
            p = Post(
                title=forgery_py.lorem_ipsum.words(randint(1, 5)),
                body=forgery_py.lorem_ipsum.sentences(randint(1, 5)),
                timestamp=forgery_py.date.date(True),
                disabled=False,
                author=u
            )
            db.session.add(p)
            db.session.commit()

    def __repr__(self):
        return '<Post %r>' % self.title


class Comment(db.Model):
    """
    Table to represent comments, leaved under Posts by Users.
    Fields:
    - body: text of the comment.
    - timestamp: time, when User created a Comment.
    - disabled: state, if a Comment was disabled by Administrator/Admin.
    Relationships:
    - author_id: author of the Comment. Foreign key to 'users' table.
    - post_id: post, which contains a Comment. Foreign key to 'posts' table.
    """
    __tablename__ = 'comment'
    id = db.Column(db.Integer, primary_key=True)

    # General fields.
    body = db.Column(db.Text)
    timestamp = db.Column(db.DateTime, default=datetime.utcnow, index=True)
    disabled = db.Column(db.Boolean, default=False)

    # Relationships.
    author_id = db.Column(db.Integer, db.ForeignKey('users.id'))
    post_id = db.Column(db.Integer, db.ForeignKey('post.id'))

    def to_json(self):
        json_comment = {
            'id': self.id,
            'url': url_for('api.get_comment', id=self.id, _external=True),
            'post': url_for('api.get_post', id=self.post_id, _external=True),
            'author': url_for('api.get_user', id=self.author_id, _external=True),
            'timestamp': self.timestamp,
            'body': self.body,
        }
        return json_comment

    @staticmethod
    def from_json(json_comment):
        body = json_comment.get('body')
        if body is None or body == '':
            raise ValidationError('Comment does not have a body.')
        return Comment(body=body)

    @staticmethod
    def generate_fake(count=100):
        from sqlalchemy.exc import IntegrityError
        from random import seed, randint
        import forgery_py

        seed()
        user_count = User.query.count()
        posts_count = Post.query.count()

        for i in range(count):
            c = Comment(
                body=forgery_py.lorem_ipsum.sentences(randint(1, 5)),
                timestamp=forgery_py.date.date(True),
                disabled=False,
                author=User.query.offset(randint(0, user_count-1)).first(),
                post=Post.query.offset(randint(0, posts_count)).first(),
            )
            db.session.add(c)
            try:
                db.session.commit()
            except IntegrityError:
                db.session.rollback()

    def __repr__(self):
        return '<Comment id%r. Author: id%r. Post: id%r.>' % (self.id, self.author_id, self.post_id)


class DevBug(db.Model):
    """
    Table to represent messages about bugs in blog.
    Used in /dev section of site.
    Fields:
    - title: a title of an issue.
    - body: description of an issue.
    - timestamp: time, when a bug was reported.
    """
    __tablename__ = 'devbugs'
    id = db.Column(db.Integer, primary_key=True)

    # General fields.
    title = db.Column(db.String(128))
    body = db.Column(db.Text)
    timestamp = db.Column(db.DateTime, default=datetime.utcnow, index=True)

    def __repr__(self):
        return '<Bug id%r. %s>' % (self.id, self.title)


@login_manager.user_loader
def load_user(user_id):
    return User.query.get(int(user_id))
