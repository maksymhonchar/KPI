from django.urls import path
import api.views as views


urlpatterns = [
    path('', views.index, name='apiindex'),

    # Registered views for Payrolls.
    path('payrolls/', views.get_payrolls),
    path('payrolls/add/', views.add_payroll),
    path('payrolls/upd/<int:payroll_id>/', views.update_payroll),
    path('payrolls/del/<int:payroll_id>/', views.remove_payroll),

    # Registered views for Employees.
    path('employees/', views.get_employees),
    path('employees/add/', views.add_employee),
    path('employees/upd/<int:employee_id>/', views.update_employee),
    path('employees/del/<int:employee_id>/', views.remove_employee),
    path('employees/search/', views.search_employee),
    path('employees/export/', views.export_employees),
    path('employees/import/', views.import_employees),

    # Registered views for Payments.
    path('payments/', views.get_payments),
    path('payments/add/', views.add_payment),
    path('payments/upd/<int:payment_id>/', views.update_payment),
    path('payments/del/<int:payment_id>/', views.remove_payment),
    path('payments/search/', views.search_payment),
    path('payments/export/', views.export_payments),
    path('payments/import/', views.import_payments),

    # Registered views for Projects.
    path('projects/', views.get_projects),
    path('projects/add/', views.add_project),
    path('projects/upd/<int:project_id>/', views.update_project),
    path('projects/del/<int:project_id>/', views.remove_project),
    path('projects/search/', views.search_project),
    path('projects/export/', views.export_projects),
    path('projects/import/', views.import_projects),
]
