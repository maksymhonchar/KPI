from django.contrib import admin

from api.models import Employee, Payment, Payroll, Project

admin.site.register(Payroll)
admin.site.register(Employee)
admin.site.register(Project)
admin.site.register(Payment)
