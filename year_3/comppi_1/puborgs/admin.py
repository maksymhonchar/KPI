from django.contrib import admin

from .models import Organization, GoverningBody, SubDivision, Founder, Location, Certificate, ActionReport

admin.site.register(Organization)
admin.site.register(GoverningBody)
admin.site.register(SubDivision)
admin.site.register(Founder)
admin.site.register(Location)
admin.site.register(Certificate)
admin.site.register(ActionReport)
