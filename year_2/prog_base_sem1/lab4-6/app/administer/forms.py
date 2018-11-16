from flask_wtf import FlaskForm
from wtforms import ValidationError
from ..models import Role, User
from wtforms.validators import DataRequired, Length, Email, Regexp
from wtforms import StringField, TextAreaField, BooleanField, SelectField, SubmitField, DateField


class EditProfileAdminForm(FlaskForm):
    email = StringField('Адрес email', validators=[
        DataRequired(message='Это поле должно быть заполнено'),
        Length(1, 64, message='Некорректная длина ввода'),
        Email(message='Неправильный формат электронной почты')
    ])
    username = StringField('Имя пользователя', validators=[
        DataRequired(message='Это поле должно быть заполнено'),
        Length(1, 64, message='Некорректная длина ввода'),
        Regexp('^[A-Za-z][A-Za-z0-9_.]*$', message='Usernames must have only letters, numbers, dots or underscores.')
    ])
    confirmed = BooleanField('Подтвержденный адрес электронной почты')
    role = SelectField('Роль', coerce=int)
    name = StringField('Имя', validators=[
        Length(0, 64, message='Некорректная длина ввода')
    ])
    surname = StringField('Фамилия', validators=[
        Length(0, 64, message='Некорректная длина ввода')
    ])
    gender = SelectField('Пол', coerce=int)
    birthday = DateField('День рождения', validators=[
        DataRequired(message='Это поле должно быть заполнено')
    ], format="%d-%m-%Y")
    location = StringField('Местоположение', validators=[
        Length(0, 64, message='Некорректная длина ввода')
    ])
    about_me = TextAreaField('Про себя')
    submit = SubmitField('Изменить')

    def __init__(self, user, *args, **kwargs):
        super(EditProfileAdminForm, self).__init__(*args, **kwargs)
        self.role.choices = [
            (role.id, role.name)
            for role in Role.query.order_by(Role.name).all()
        ]
        self.gender.choices = [(1, 'Мужской'), (2, 'Женский')]
        self.user = user

    def validate_email(self, field):
        if field.data != self.user.email and \
                User.query.filter_by(email=field.data).first():
            raise ValidationError('Пользователь с таким email адресом уже зарегестрирован.')

    def validate_username(self, field):
        if field.data != self.user.username and \
                User.query.filter_by(username=field.data).first():
            raise ValidationError('Пользователь с таким именем уже существует.')
