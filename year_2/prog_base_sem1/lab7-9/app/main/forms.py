from flask_wtf import FlaskForm
from wtforms import StringField, TextAreaField, SubmitField, DateField, FileField
from wtforms.validators import DataRequired, Length


class EditProfileForm(FlaskForm):
    name = StringField('Имя', validators=[
        Length(1, 64, message='Слишком большое имя, сожалеем об этом.')
    ])
    surname = StringField('Фамилия', validators=[
        Length(1, 64, message='Слишком большая фамилия, сожалеем об этом.')
    ])
    birthday = DateField('Дата рождения', format="%d-%m-%Y")
    location = StringField('Текущий город', validators=[
        Length(0, 64, message='Слишком большое название местоположения, сожалеем об этом.')
    ])
    about_me = TextAreaField('Личная информация')
    submit = SubmitField('Изменить')


class PostForm(FlaskForm):
    body = TextAreaField('Что у вас на уме?', validators=[
        DataRequired(message='Запись должна иметь текст, или картинку.')
    ])
    title = StringField('Заголовок', validators=[
        DataRequired(message='Запись должна иметь заголовок.'),
        Length(0, 128, message='Слишком большой заголовок, сожалеем об этом.')
    ])
    submit = SubmitField('Опубликовать')


class EditCommentForm(FlaskForm):
    body = StringField('Ваш новый комментарий', validators=[DataRequired('Комментарий не может быть пустым.')])
    submit = SubmitField('Изменить')


class CommentForm(FlaskForm):
    body = StringField('Ваш комментарий', validators=[DataRequired('Комментарий не может быть пустым.')])
    submit = SubmitField('Комментировать')


class DevBugForm(FlaskForm):
    body = StringField('Описание бага', validators=[DataRequired('Описание не может быть пустым.')])
    title = StringField('Заголовок', validators=[
        DataRequired(message='Описание должно иметь заголовок.'),
        Length(0, 128, message='Слишком большой заголовок, сожалеем об этом.')
    ])
    submit = SubmitField('Отправить')


class AvatarForm(FlaskForm):
    avatar = FileField('Добавить фотографию', validators=[DataRequired('Пожалуйста, выберите картинку для загрузки.')])
    submit = SubmitField('Загрузить')


class SearchForm(FlaskForm):
    query = StringField('Поиск по имени, или юзернейму', validators=[DataRequired('Строка поиска не может быть пустой.')])
    submit = SubmitField('Поиск')


class DeletePostForm(FlaskForm):
    submit = SubmitField('Удалить')
