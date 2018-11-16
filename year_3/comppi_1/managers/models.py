import datetime

from django.contrib.auth.models import User
from django.core.serializers.json import DjangoJSONEncoder
from django.db import models


class ManagersModelsJSONEncoder(DjangoJSONEncoder):
    def default(self, value):
        if isinstance(value, datetime.date):
            return DjangoJSONEncoder.default(self, value)
        elif isinstance(value, bytes):
            def bool_from_byte(byte_value):
                return 1 if byte_value == b'\x01' else 0
            return bool_from_byte(value)
        else:
            value_to_return = value.__dict__
            return value_to_return


class PubOrgAdmin(models.Model):
    user = models.OneToOneField(User, on_delete=models.CASCADE, primary_key=True)
    is_admin = models.BooleanField(default=True, blank=False)
    doc_code = models.CharField(max_length=50, blank=False)
    credentials = models.TextField(blank=False)


class PubOrgRegistrant(models.Model):
    user = models.OneToOneField(User, on_delete=models.CASCADE, primary_key=True)
    hired_by = models.ForeignKey(PubOrgAdmin, on_delete=models.CASCADE, blank=False)
    hired_order_code = models.CharField(max_length=50, blank=False)
    is_admin = models.BooleanField(default=False, blank=False)
    doc_code = models.CharField(max_length=50, blank=False)
    credentials = models.TextField(blank=False)
