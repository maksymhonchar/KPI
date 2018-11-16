import os
from app import create_app, db
from app.models import User, Role, Permission, Post, Follow, Comment, Fave, DevBug
from flask_script import Manager, Shell
from flask_migrate import Migrate, MigrateCommand


app = create_app(os.getenv('FLASK_CONFIG') or 'default')
manager = Manager(app)
migrate = Migrate(app, db)


def make_shell_context():
    return dict(
        app=app, db=db, User=User, Follow=Follow, Role=Role,
        Permission=Permission, Post=Post, Comment=Comment,
        Fave=Fave, DevBug=DevBug
    )
manager.add_command('shell', Shell(make_context=make_shell_context))
manager.add_command('db', MigrateCommand)


@manager.command
def test():
    """
    Run the unit tests.
    """
    import unittest
    tests = unittest.TestLoader().discover('tests')
    unittest.TextTestRunner(verbosity=2).run(tests)


@manager.command
def deploy():
    """
    Run all deployment tasks:
    - Upgrade database to latest revision.
    - Initialize user roles and add them to DB.
    """
    from flask_migrate import upgrade
    from app.models import Role

    # Migrate database to latest revision.
    upgrade()
    # Create user roles.
    Role.insert_roles()


if __name__ == '__main__':
    manager.run()
