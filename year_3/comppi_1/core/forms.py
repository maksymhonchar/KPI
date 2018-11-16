from django import forms

from puborgs.modelschoices import locations, orgadditional, reports


class LogInForm(forms.Form):
    username = forms.CharField(
        label="Кодове ім'я",
        max_length=255,
        help_text="Username співробітника"
    )
    password = forms.CharField(
        label="Пароль",
        max_length=255,
        widget=forms.PasswordInput(),
        help_text="Пароль",
    )

    def clean(self):
        cleaned_data = super(LogInForm, self).clean()
        name = cleaned_data.get('username')
        password = cleaned_data.get('password')
        if not name or not password:
            raise forms.ValidationError('Усі поля мають бути непустими')


class SupportMsgForm(forms.Form):
    email_addr = forms.EmailField(
        label="Електронна адреса для зворотнього зв'язку",
        error_messages={'invalid': 'Неправильний формат пошти'}
    )
    question = forms.CharField(
        label="Ваше питання",
        widget=forms.Textarea,
    )

    def clean(self):
        cleaned_data = super(SupportMsgForm, self).clean()
        email_addr = cleaned_data.get('email_addr')
        question = cleaned_data.get('question')
        if not email_addr or not question:
            raise forms.ValidationError('Усі поля мають бути непустими або неправильний формат електронної пошти')


class NewRegistrantForm(forms.Form):
    username = forms.CharField(
        label="Кодове ім'я",
        max_length=255,
        help_text="Username співробітника"
    )
    password = forms.CharField(
        label="Пароль",
        max_length=255,
        widget=forms.PasswordInput(),
        help_text="Пароль",
    )
    hired_order_code = forms.CharField(
        max_length=50,
        label="Номер наказу про створення Реєстратора"
    )
    doc_code = forms.CharField(
        max_length=50,
        label="Номер особової справи Реєстратора"
    )
    credentials = forms.CharField(
        widget=forms.Textarea,
        label="Зворотній зв'язок із Реєстратором"
    )

    def clean(self):
        cleaned_data = super(NewRegistrantForm, self).clean()
        username = cleaned_data.get('username')
        password = cleaned_data.get('password')
        hired_order_code = cleaned_data.get('hired_order_code')
        doc_code = cleaned_data.get('doc_code')
        credentials = cleaned_data.get('credentials')
        if not username or not password or not hired_order_code or not doc_code or not credentials:
            raise forms.ValidationError('Усі поля мають бути непустими')


class EditRegistrantForm(forms.Form):
    hired_order_code = forms.CharField(
        max_length=50,
        label="Новий номер наказу про створення Реєстратора"
    )
    doc_code = forms.CharField(
        max_length=50,
        label="Новий номер особової справи Реєстратора"
    )
    credentials = forms.CharField(
        widget=forms.Textarea,
        label="Новий зворотній зв'язок із Реєстратором"
    )

    def clean(self):
        cleaned_data = super(EditRegistrantForm, self).clean()
        hired_order_code = cleaned_data.get('hired_order_code')
        doc_code = cleaned_data.get('doc_code')
        credentials = cleaned_data.get('credentials')
        if not hired_order_code or not doc_code or not credentials:
            raise forms.ValidationError('Усі поля мають бути непустими')


class NewOrganizationForm(forms.Form):
    cert_issue_date = forms.DateField(
        required=True,
        label="Дата видання сертифікату (р-м-д)"
    )
    loc_region = forms.ChoiceField(
        required=True,
        choices=locations.LOCATIONSREGIONCHOICES,
        label="Регіон",
    )
    loc_district = forms.CharField(
        max_length=100,
        required=True,
        label="Район"
    )
    loc_locality = forms.CharField(
        max_length=100,
        required=True,
        label="Населений пункт"
    )
    loc_street = forms.CharField(
        max_length=100,
        required=True,
        label="Вулиця"
    )
    loc_building = forms.CharField(
        max_length=100,
        required=True,
        label="Номер будинку/корпус"
    )
    org_type = forms.ChoiceField(
        required=True,
        choices=orgadditional.ORGTYPECHOICES,
        label="Вид ГО",
    )
    org_orientation = forms.ChoiceField(
        required=True,
        choices=orgadditional.ORGORIENTATIONCHOICES,
        label="Спрямованість ГО"
    )
    org_status = forms.ChoiceField(
        required=True,
        choices=orgadditional.ORGSTATUSCHOICES,
        label="Статус ГО"
    )
    org_full_naming = forms.CharField(
        max_length=100,
        required=True,
        label="Повне найменування громадського об'єднання"
    )
    org_short_naming = forms.CharField(
        max_length=100,
        required=True,
        label="Коротке найменування"
    )
    org_foreign_naming = forms.CharField(
        max_length=100,
        required=True,
        label="Іноземна назва"
    )
    org_edrpou = forms.CharField(
        max_length=100,
        required=True,
        label="ЄДРПОУ"
    )
    org_owner_edrpou = forms.CharField(
        max_length=100,
        required=True,
        label="ЄДРПОУ Засновника"
    )
    org_organiz_pravov_form = forms.CharField(
        max_length=100,
        required=True,
        label="Організаційно-правова форма"
    )
    org_registration_state = forms.BooleanField(
        required=True,
        initial=True,
        label="Статус реєстрації"
    )
    org_entrepreneurial_activity = forms.BooleanField(
        required=True,
        initial=True,
        label="Підприємницька активність"
    )
    org_feedback = forms.CharField(
        required=True,
        widget=forms.Textarea,
        label="Зворотній зв'язок"
    )


class EditOrganizationForm(forms.Form):
    org_type = forms.ChoiceField(
        required=True,
        choices=orgadditional.ORGTYPECHOICES,
        label="Вид ГО",
    )
    org_orientation = forms.ChoiceField(
        required=True,
        choices=orgadditional.ORGORIENTATIONCHOICES,
        label="Спрямованість ГО"
    )
    org_status = forms.ChoiceField(
        required=True,
        choices=orgadditional.ORGSTATUSCHOICES,
        label="Статус ГО"
    )
    org_full_naming = forms.CharField(
        max_length=100,
        required=True,
        label="Повне найменування громадського об'єднання"
    )
    org_short_naming = forms.CharField(
        max_length=100,
        required=True,
        label="Коротке найменування"
    )
    org_foreign_naming = forms.CharField(
        max_length=100,
        required=True,
        label="Іноземна назва"
    )
    org_edrpou = forms.CharField(
        max_length=100,
        required=True,
        label="ЄДРПОУ"
    )
    org_owner_edrpou = forms.CharField(
        max_length=100,
        required=True,
        label="ЄДРПОУ Засновника"
    )
    org_organiz_pravov_form = forms.CharField(
        max_length=100,
        required=True,
        label="Організаційно-правова форма"
    )
    org_registration_state = forms.BooleanField(
        required=True,
        initial=True,
        label="Статус реєстрації"
    )
    org_entrepreneurial_activity = forms.BooleanField(
        required=True,
        initial=True,
        label="Підприємницька активність"
    )
    org_feedback = forms.CharField(
        required=True,
        widget=forms.Textarea,
        label="Зворотній зв'язок"
    )


class OrgSearchForm(forms.Form):
    org_idnum = forms.IntegerField(
        label="Реєстраційний номер запису",
        required=False
    )
    org_full_naming = forms.CharField(
        max_length=100,
        label="Повне найменування громадського об'єднання",
        required=False
    )
    org_edrpou = forms.CharField(
        max_length=100,
        label="ЄДРПОУ",
        required=False
    )
    org_owner_edrpou = forms.CharField(
        max_length=100,
        label="ЄДРПОУ Засновника",
        required=False
    )
    org_type = forms.ChoiceField(
        choices=orgadditional.ORGTYPECHOICES,
        label="Вид ГО",
        required=False
    )
    org_orientation = forms.ChoiceField(
        choices=orgadditional.ORGORIENTATIONCHOICES,
        label="Спрямованість ГО",
        required=False
    )
    org_status = forms.ChoiceField(
        choices=orgadditional.ORGSTATUSCHOICES,
        label="Статус ГО",
        required=False
    )
    cert_issue_date = forms.DateField(
        label="Дата видання сертифікату (р-м-д)",
        required=False
    )
    loc_region = forms.ChoiceField(
        choices=locations.LOCATIONSREGIONCHOICES,
        label="Регіон",
        required=False
    )
    loc_district = forms.CharField(
        max_length=100,
        label="Район",
        required=False
    )
    loc_locality = forms.CharField(
        max_length=100,
        label="Населений пункт",
        required=False
    )
    loc_street = forms.CharField(
        max_length=100,
        label="Вулиця",
        required=False
    )
    loc_building = forms.CharField(
        max_length=100,
        label="Номер будинку/корпус",
        required=False
    )
