from flask_wtf import FlaskForm
from wtforms import StringField, PasswordField, BooleanField, SubmitField, DateField, SelectField
from wtforms.validators import DataRequired, Email, Length, Regexp, EqualTo
from wtforms import ValidationError
import re
from ..models import User


class LoginForm(FlaskForm):
    __formname__ = 'login_form'
    is_email = True

    email_or_username = StringField('Ваш Email или никнейм', validators=[
        DataRequired(message='Это поле должно быть заполнено'),
        Length(1, 64, message='Некорректная длина ввода.'),
    ])
    password = PasswordField('Ваш Пароль', validators=[
        DataRequired(message='Это поле должно быть заполнено')
    ])
    remember_me = BooleanField('Запомнить меня')
    submit = SubmitField('Войти')

    def validate_email_or_username(self, field):
        if not re.match(r"[^@]+@[^@]+\.[^@]+", field.data, re.IGNORECASE):
            self.is_email = False


class RegistrationForm(FlaskForm):
    __formname__ = 'register_form'

    first_name = StringField('Ваше Имя', validators=[
        DataRequired(message='Это поле должно быть заполнено'),
        Length(1, 64, message='Некорректная длина ввода')
    ])
    second_name = StringField('Ваша Фамилия', validators=[
        DataRequired(message='Это поле должно быть заполнено'),
        Length(1, 64, message='Некорректная длина ввода')
    ])
    birthday = DateField('День рождения', validators=[
        DataRequired(message='Это поле должно быть заполнено')
    ], format="%d-%m-%Y")
    gender = SelectField('Пол', coerce=int)
    username = StringField('Имя пользователя', validators=[
        DataRequired(message='Это поле должно быть заполнено'),
        Length(1, 64, message='Некорректная длина ввода'),
        Regexp('^[A-Za-z0-9_.][A-Za-z0-9_.]*$',
               message='Имена пользователей могут состоять только из букв, чисел, точек и нижних подчеркиваний.')
    ])
    email = StringField('Ваш email', validators=[
        DataRequired(message='Это поле должно быть заполнено'),
        Length(1, 64, message='Некорректная длина ввода'),
        Email(message='Неправильный формат электронной почты')
    ])
    password = PasswordField('Пароль', validators=[
        DataRequired(message='Это поле должно быть заполнено'),
        EqualTo('password2', message='Пароли должны совпадать.')
    ])
    password2 = PasswordField('Подтвердите пароль', validators=[
        DataRequired(message='Это поле должно быть заполнено'),
        EqualTo('password', message='Пароли должны совпадать.')
    ])
    policy_check = BooleanField('Я согласен с правилами пользования сайтом.', validators=[
        DataRequired(message='Для регистрации Вы должны быть согласными с правилами пользования сайтом.')
    ])
    submit = SubmitField('Создать аккаунт')

    def __init__(self, *args, **kwargs):
        super(RegistrationForm, self).__init__(*args, **kwargs)
        self.gender.choices = [(1, 'Мужской'), (2, 'Женский')]

    def validate_email(self, field):
        if User.query.filter_by(email=field.data).first():
            raise ValidationError('Адрес email уже используется другим пользователем.')

    def validate_username(self, field):
        if User.query.filter_by(username=field.data).first():
            raise ValidationError('Имя пользователя занято.')


class PasswordResetRequestForm(FlaskForm):
    __formname__ = 'resetpassreq_form'

    email = StringField('Ваш Email', validators=[
        DataRequired(message='Это поле должно быть заполнено'),
        Length(1, 64, message='Некорректная длина ввода'),
        Email(message='Неправильный формат электронной почты')
    ])
    submit = SubmitField('Сбросить пароль')


class PasswordResetForm(FlaskForm):
    __formname__ = 'passreset_form'

    email = StringField('Ваш Email', validators=[
        DataRequired(message='Это поле должно быть заполнено'),
        Length(1, 64, message='Некорректная длина ввода'),
        Email(message='Неправильный формат электронной почты')
    ])
    password = PasswordField('Новый пароль', validators=[
        DataRequired(message='Это поле должно быть заполнено'),
        EqualTo('password2', message="Пароли должны совпадать.")
    ])
    password2 = PasswordField('Подтвердите новый пароль', validators=[
        DataRequired(message='Это поле должно быть заполнено'),
        EqualTo('password', message='Пароли должны совпадать.')
    ])
    submit = SubmitField('Обновить пароль')

    def validate_email(self, field):
        if User.query.filter_by(email=field.data).first() is None:
            raise ValidationError('Пользователя с даным email адресом не найдено.')


class ChangePasswordForm(FlaskForm):
    __formname__ = 'changepass_form'

    old_password = PasswordField('Старый пароль', validators=[
        DataRequired(message='Это поле должно быть заполнено')
    ])
    password = PasswordField('Новый пароль', validators=[
        DataRequired(message='Это поле должно быть заполнено'),
        EqualTo('password2', message='Пароли должны совпадать.')
    ])
    password2 = PasswordField('Подтвердите новый пароль', validators=[
        DataRequired(message='Это поле должно быть заполнено')
    ])
    submit = SubmitField('Обновить пароль')


class ChangeEmailForm(FlaskForm):
    __formname__ = 'changeemail_form'

    email = StringField('Новый email', validators=[
        DataRequired(message='Это поле должно быть заполнено'),
        Length(1, 64, message='Некорректная длина ввода'),
        Email(message='Неправильный формат электронной почты')
    ])
    password = PasswordField('Пароль для подтверждения', validators=[
        DataRequired(message='Это поле должно быть заполнено')
    ])
    submit = SubmitField('Обновить адрес email')

    def validate_email(self, field):
        if User.query.filter_by(email=field.data).first():
            raise ValidationError('Пользователь с таким именем уже существует.')
