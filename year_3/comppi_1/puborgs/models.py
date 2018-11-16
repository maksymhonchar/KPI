import datetime

from django.core.serializers.json import DjangoJSONEncoder
from django.db import models

from managers.models import PubOrgRegistrant
from .modelschoices import locations, orgadditional, reports


class OrgsModelsJSONEncoder(DjangoJSONEncoder):
    def default(self, value):
        if isinstance(value, datetime.date):
            return DjangoJSONEncoder.default(self, value)
        elif isinstance(value, bytes):
            def bool_from_byte(byte_value):
                return 1 if byte_value == b'\x01' else 0
            return bool_from_byte(value)
        else:
            value_to_return = value.__dict__
            if '_state' in value_to_return.keys():
                del value_to_return['_state']
            return value_to_return


class Certificate(models.Model):
    issue_date = models.DateField(default=datetime.date.today, blank=False)


class Location(models.Model):
    region = models.CharField(max_length=100, blank=False,
                              choices=locations.LOCATIONSREGIONCHOICES,
                              default=locations.DEFAULTLOCATIONSREGIONCHOICES)
    district = models.CharField(max_length=100, blank=False)
    locality = models.CharField(max_length=100, blank=False)
    street = models.CharField(max_length=100, blank=False)
    building = models.CharField(max_length=100, blank=False)


class Founder(models.Model):
    name = models.CharField(max_length=100, blank=False)
    surname = models.CharField(max_length=100, blank=False)


class GoverningBody(models.Model):
    name = models.CharField(max_length=100, blank=False)
    surname = models.CharField(max_length=100, blank=False)
    position = models.CharField(max_length=100, blank=False)
    restrictions = models.CharField(max_length=100, blank=True)


class SubDivision(models.Model):
    location = models.OneToOneField(Location, on_delete=models.CASCADE, blank=False)
    full_name = models.CharField(max_length=100, blank=False)
    registration_state = models.BooleanField(blank=False)
    manager_full_name = models.CharField(max_length=100, blank=False)
    last_change_datetime = models.DateField(default=datetime.date.today, blank=False)


class Organization(models.Model):
    # Foreign fields.
    created_by = models.ForeignKey(PubOrgRegistrant, on_delete=models.CASCADE, blank=False)
    certificate = models.OneToOneField(Certificate, on_delete=models.CASCADE, blank=False)
    location = models.OneToOneField(Location, on_delete=models.CASCADE, blank=False)
    # Fields with choices.
    type = models.CharField(max_length=100, blank=False,
                            choices=orgadditional.ORGTYPECHOICES,
                            default=orgadditional.DEFAULTORGTYPECHOICE)
    orientation = models.CharField(max_length=100,
                                   choices=orgadditional.ORGORIENTATIONCHOICES,
                                   default=orgadditional.DEFAULTORGORIENTCHOICE)

    status = models.CharField(max_length=100, blank=False,
                              choices=orgadditional.ORGSTATUSCHOICES,
                              default=orgadditional.DEFAULTORGSTATUSCHOICE)
    # Fields as list of ids.
    founders_ids_list = models.TextField(blank=True)
    governing_bodies_ids_list = models.TextField(blank=True)
    separated_subdivisions_ids_list = models.TextField(blank=True)
    # Other fields.
    full_naming = models.CharField(max_length=100, blank=False)
    short_naming = models.CharField(max_length=100, blank=False)
    edrpou = models.CharField(max_length=100, blank=False)
    owner_edrpou = models.CharField(max_length=100, blank=False)
    foreign_naming = models.CharField(max_length=100, blank=True)
    organiz_pravov_form = models.CharField(max_length=100, blank=True)
    registration_state = models.BooleanField(default=False, blank=False)
    entrepreneurial_activity = models.BooleanField(default=False, blank=False)
    registration_date = models.DateField(default=datetime.date.today, blank=False)
    feedback = models.TextField(blank=False)


class ActionReport(models.Model):
    # Foreign fields
    registrant = models.ForeignKey(PubOrgRegistrant, on_delete=models.CASCADE, blank=False)
    organization = models.ForeignKey(Organization, on_delete=models.CASCADE, blank=False)
    # Fields with choices
    action = models.CharField(max_length=100, blank=False,
                              choices=reports.REPACTIONCHOICES,
                              default=reports.DEFAULTREPACTIONCHOICE)
    # Other fields.
    action_datetime = models.DateTimeField(default=datetime.datetime.now, blank=False)
