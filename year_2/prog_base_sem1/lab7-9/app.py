import os
from app import create_app, db
from app.models import Role
from flask_migrate import Migrate


app = create_app(os.getenv('FLASK_CONFIG') or 'default')
migrate = Migrate(app, db)


@app.before_first_request
def create_database():
    db.create_all()
    Role.insert_roles()

if __name__ == '__main__':
    port = int(os.environ.get('PORT') or 5000)
    app.run(port=port, debug=False, host='0.0.0.0')
