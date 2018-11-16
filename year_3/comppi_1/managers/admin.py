from django.contrib import admin

from .models import PubOrgRegistrant, PubOrgAdmin

admin.site.register(PubOrgAdmin)
admin.site.register(PubOrgRegistrant)
