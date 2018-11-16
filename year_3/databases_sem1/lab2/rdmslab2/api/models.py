from decimal import Decimal
import datetime

from django.core.serializers.json import DjangoJSONEncoder


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


class Payroll(object):
    def __init__(self, payroll_id, employee_id, payment_id, project_id, payroll_date):
        self.payroll_id = payroll_id
        self.employee_id = employee_id
        self.payment_id = payment_id
        self.project_id = project_id
        self.payroll_date = payroll_date


class Employee(object):
    def __init__(self, employee_id, full_name, characteristics, is_intern):
        self.employee_id = employee_id
        self.full_name = full_name
        self.characteristics = characteristics
        self.is_intern = is_intern


class Payment(object):
    def __init__(self, payment_id, method, raw_salary, tax_rate):
        self.payment_id = payment_id
        self.method = method
        self.raw_salary = raw_salary
        self.tax_rate = tax_rate


class Project(object):
    def __init__(self, project_id, name, description):
        self.project_id = project_id
        self.name = name
        self.description = description
