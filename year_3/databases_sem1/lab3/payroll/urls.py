from django.urls import path
import payroll.views as views


urlpatterns = [
    path('', views.index, name='indexpage'),

    path('import/', views.import_model, name='importmodel'),
    path('export/', views.export_model, name='exportmodel'),

    path('payrolls/', views.payrolls, name='payrollsindex'),
    path('employees/', views.employees, name='employeesindex'),
    path('payments/', views.payments, name='paymentsindex'),
    path('projects/', views.projects, name='projectsindex'),
]
