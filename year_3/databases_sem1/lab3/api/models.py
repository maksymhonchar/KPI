import datetime
from decimal import Decimal

from django.core.serializers.json import DjangoJSONEncoder
from django.db import models


class ModelsJSONEncoder(DjangoJSONEncoder):
    def default(self, value):
        if isinstance(value, datetime.date):
            return DjangoJSONEncoder.default(self, value)
        if isinstance(value, bytes):
            def bool_from_byte(byte_value):
                return 1 if byte_value == b'\x01' else 0

            return bool_from_byte(value)
        if isinstance(value, Decimal):
            return float(value)
        else:
            return value.__dict__


class Employee(models.Model):
    full_name = models.CharField(max_length=255)
    characteristics = models.TextField()
    is_intern = models.BooleanField(default=True)


class Payment(models.Model):
    method = models.CharField(max_length=255)
    raw_salary = models.FloatField()
    tax_rate = models.FloatField()


class Project(models.Model):
    name = models.CharField(max_length=255)
    description = models.TextField()


class Payroll(models.Model):
    employee = models.ForeignKey(Employee, on_delete=models.CASCADE)
    payment = models.ForeignKey(Payment, on_delete=models.CASCADE)
    project = models.ForeignKey(Project, on_delete=models.CASCADE)
    payroll_date = models.DateField()
