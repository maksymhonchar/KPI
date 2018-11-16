import os
basedir = os.path.abspath(os.path.dirname(__file__))


class Config:
    ROOT_FOLDER = basedir + '/app'
    IMG_FOLDER = '/static/img/usr/'
    MAX_CONTENT_LENGTH = 2 * 1024 * 1024
    JSON_AS_ASCII = False
    JSON_SORT_KEYS = True
    JSONIFY_PRETTYPRINT_REGULAR = True
    SECRET_KEY = os.environ.get('SECRET_KEY')
    CSRF_ENABLED = False  # For CSRF api POST and PUT issue
    WTF_CSRF_ENABLED = False
    SQLALCHEMY_COMMIT_ON_TEARDOWN = True
    SQLALCHEMY_TRACK_MODIFICATIONS = True
    MAIL_SERVER = os.environ.get('MAIL_SERVER')
    MAIL_PORT = os.environ.get('MAIL_PORT')
    MAIL_USE_TLS = True
    MAIL_USERNAME = os.environ.get('ADMIN_MAIL_USERNAME')
    MAIL_PASSWORD = os.environ.get('ADMIN_MAIL_PASSWORD')
    WIDT_MAIL_SUBJECT_PREFIX = os.environ.get('WIDT_MAIL_SUBJECT_PREFIX')
    WIDT_MAIL_SENDER = os.environ.get('WIDT_MAIL_SENDER')
    WIDT_ADMIN = os.environ.get('WIDT_ADMIN')
    WIDT_POSTS_PER_PAGE = 15
    WIDT_FOLLOWERS_PER_PAGE = 30
    WIDT_COMMENTS_PER_PAGE = 30
    WIDT_USERS_PER_PAGE = 20

    @staticmethod
    def init_app(app):
        pass


class DevelopmentConfig(Config):
    DEBUG = True
    SQLALCHEMY_DATABASE_URI = os.environ.get('DEV_DATABASE_URL') or None


class TestingConfig(Config):
    TESTING = True
    SQLALCHEMY_DATABASE_URI = os.environ.get('TEST_DATABASE_URL') or None


class ProductionConfig(Config):
    SQLALCHEMY_DATABASE_URI = os.environ.get('DATABASE_URL') or None


config = {
    'development': DevelopmentConfig,
    'testing': TestingConfig,
    'production': ProductionConfig,

    'default': DevelopmentConfig
}
