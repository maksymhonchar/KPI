from flask import render_template, redirect, request, url_for, flash
from flask_login import login_user, logout_user, login_required, current_user
from .email import send_email
from . import auth
from .forms import LoginForm, RegistrationForm, ChangePasswordForm, \
    PasswordResetForm, PasswordResetRequestForm, ChangeEmailForm
from .. import db
from ..models import User
from .utils import redirect_back, get_redirect_target


@auth.before_app_request
def before_request():
    if current_user.is_authenticated \
            and not current_user.confirmed \
            and request.endpoint[:5] != 'auth.' \
            and request.endpoint != 'static':
        return redirect(url_for('auth.unconfirmed'))


@auth.route('/unconfirmed')
def unconfirmed():
    if current_user.is_anonymous or current_user.confirmed:
        return redirect(url_for('main.index'))
    return render_template('auth/unconfirmed.html')


@auth.route('/login', methods=['GET', 'POST'])
def login():
    if current_user.is_authenticated:
        return redirect(url_for('main.index'))
    form = LoginForm()
    next_link = get_redirect_target()
    if form.validate_on_submit():
        if not form.is_email:
            user = User.query.filter_by(username=form.email_or_username.data).first()
        else:
            user = User.query.filter_by(email=form.email_or_username.data).first()
        if user is not None and user.verify_password(form.password.data):
            login_user(user, form.remember_me.data)
            return redirect_back('main.index')
        flash('Неверное имя или пароль.')
    return render_template('auth/login.html', form=form, next=next_link)


@auth.route('/logout')
@login_required
def logout():
    logout_user()
    flash('Вы успешно вышли из своего аккаунта.')
    return redirect(url_for('auth.login'))


@auth.route('/signup', methods=['GET', 'POST'])
def signup():
    if current_user.is_authenticated:
        return redirect(url_for('main.index'))
    form = RegistrationForm()
    if form.validate_on_submit():
        user = User(
            name=form.first_name.data,
            surname=form.second_name.data,
            birthday=form.birthday.data,
            gender=form.gender.data,
            username=form.username.data,
            email=form.email.data,
            password=form.password.data
        )
        db.session.add(user)
        db.session.commit()
        token = user.generate_confirmation_token()
        send_email(
            user.email, 'Подтвердите Ваш Аккаунт',
            'auth/email/confirm',
            user=user, token=token
        )
        flash('Письмо с подтверждением отправлено на ваш email.')
        return redirect(url_for('auth.login'))
    return render_template('auth/signup.html', form=form)


@auth.route('/confirm/<token>')
@login_required
def confirm(token):
    if current_user.confirmed:
        flash('Ваша страница уже подтверждена.')
        return redirect(url_for('main.index'))
    if current_user.confirm(token):
        flash('Вы подтвердили свой аккант. Спасибо!')
    else:
        flash('Ссылка для подтверждения была повреждена, или устарела. Попробуйте еще раз.')
    return redirect(url_for('main.index'))


@auth.route('/confirm')
@login_required
def resend_confirmation():
    token = current_user.generate_confirmation_token()
    send_email(
        current_user.email,
        'Подтвердите Ваш Аккаунт',
        'auth/email/confirm',
        user=current_user, token=token
    )
    flash('Новое письмо с подтверждением выслано на Вашу почту.')
    return redirect(url_for('main.index'))


@auth.route('/change-password', methods=['GET', 'POST'])
@login_required
def change_password():
    form = ChangePasswordForm()
    if form.validate_on_submit():
        if current_user.verify_password(form.old_password.data):
            current_user.password = form.password.data
            db.session.add(current_user)
            flash('Ваш пароль обновлен.')
            return redirect(url_for('main.index'))
        else:
            flash('Неверный пароль.')
    return render_template('auth/change_password.html', form=form)


@auth.route('/lostinfo', methods=['GET', 'POST'])
def password_reset_request():
    if not current_user.is_anonymous:
        return redirect(url_for('main.index'))
    form = PasswordResetRequestForm()
    if form.validate_on_submit():
        user = User.query.filter_by(email=form.email.data).first()
        if user:
            token = user.generate_reset_token()
            send_email(
                user.email,
                'Сброс Вашего Пароля',
                'auth/email/reset_password',
                user=user, token=token, next=request.args.get('next')
            )
            flash('Электронное письмо с инструкциями для сброса Вашего пароля было отправлено на вашу почту.')
        else:
            flash('Пользователя с email адресом %s еще нет в системе.' % form.email.data)
            return redirect(url_for('auth.password_reset_request'))
        return redirect(url_for('auth.login'))
    return render_template('auth/reset_password_request.html', form=form)


@auth.route('/reset/<token>', methods=['GET', 'POST'])
def password_reset(token):
    if not current_user.is_anonymous:
        return redirect(url_for('main.index'))
    form = PasswordResetForm()
    if form.validate_on_submit():
        user = User.query.filter_by(email=form.email.data).first()
        if user is None:
            flash('Токен для обновления пароля был поврежден.')
            return redirect(url_for('main.index'))
        if user.reset_password(token, form.password.data):
            flash('Ваш пароль успешно обновлен.')
            return redirect(url_for('auth.login'))
        else:
            flash('Случилась ошибка. Попробуйте еще раз, пожалуйста.')
            return redirect(url_for('main.index'))
    return render_template('auth/reset_password.html', form=form, token=token)


@auth.route('/change-email', methods=['GET', 'POST'])
@login_required
def change_email_request():
    form = ChangeEmailForm()
    if form.validate_on_submit():
        if current_user.verify_password(form.password.data):
            new_email = form.email.data
            token = current_user.generate_email_change_token(new_email)
            send_email(
                new_email,
                'Подтвердите ваш адрес',
                'auth/email/change_email',
                user=current_user, token=token
            )
            flash('Электронное письмо с инструкциями для подтверждения нового пароля было отправлено на вашу почту.')
            return redirect(url_for('main.index'))
        else:
            flash('Неверный пароль или адрес email.')
    return render_template('auth/change_email.html', form=form)


@auth.route('/change-email/<token>')
@login_required
def change_email(token):
    if current_user.change_email(token):
        flash('Ваш адрес email был успешно обновлен.')
    else:
        flash('Ошибка в запросе, или токен был поврежден. Попробуйте еще раз.')
    return redirect(url_for('main.index'))
