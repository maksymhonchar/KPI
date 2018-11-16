import datetime
import json

import MySQLdb
import simplexml
from django.http import HttpResponse, JsonResponse
from django.utils.decorators import method_decorator
from django.views.decorators.csrf import csrf_exempt

from api.dbmodels import Employees, Payments, Payrolls, Projects
from api.models import Employee, ModelsJSONEncoder, Payment, Payroll, Project


def connect():
    db = MySQLdb.connect(
        host='localhost',
        user='max',
        password='pass',
        db='lab2project',
        port=8888
    )
    db.set_character_set('utf8')
    return db


def index(request):
    if request.method == 'GET':
        connect()
        return JsonResponse({
            'text': 'welcome to API index',
            'mysqldb_conn': 'success'
        })


def dict_from_class(cls):
    return dict(
        (k, v) for (k, v) in cls.__dict__.items()
    )


def export(request, data, dbmodelname):
    if request.method == 'GET':
        data = {
            dbmodelname: [
                {dbmodelname[:-1]: dict_from_class(el)} for el in data
            ]
        }
        xml_to_export = simplexml.dumps(data)
        response = HttpResponse(xml_to_export, content_type='application/json')
        response['Content-Disposition'] = 'attachment; filename="%s.xml"' % dbmodelname
        return response
    return HttpResponse(status=400)


def _req_body_to_payroll(request):
    request_body_fields = request.body.decode('utf-8')
    payroll_fields = json.loads(request_body_fields)
    payroll = Payroll(
        0,
        payroll_fields['employee_id'],
        payroll_fields['payment_id'],
        payroll_fields['project_id'],
        datetime.datetime.strptime(payroll_fields['payroll_date'], "%Y-%m-%d")
    )
    return payroll


@method_decorator(csrf_exempt, name='dispatch')
def get_payrolls(request):
    if request.method == 'GET':
        with connect() as conn:
            dbpayrolls = Payrolls(conn)
            payrolls = dbpayrolls.readall()
        return JsonResponse(payrolls, safe=False, encoder=ModelsJSONEncoder, json_dumps_params={'indent': 2})
    return HttpResponse(status=400)


@method_decorator(csrf_exempt, name='dispatch')
def add_payroll(request):
    if request.method == 'POST':
        try:
            payroll = _req_body_to_payroll(request)
        except (TypeError, KeyError) as e:
            print(e)
            return HttpResponse(status=400)
        with connect() as conn:
            dbpayroll = Payrolls(conn)
            dbpayroll.add(payroll)
        return HttpResponse(status=200)
    return HttpResponse(status=400)


@method_decorator(csrf_exempt, name='dispatch')
def update_payroll(request, payroll_id):
    if request.method == 'PUT':
        try:
            payroll = _req_body_to_payroll(request)
        except (TypeError, KeyError) as e:
            print(e)
            return HttpResponse(status=400)
        with connect() as conn:
            dbpayroll = Payrolls(conn)
            dbpayroll.update(payroll, payroll_id)
        return HttpResponse(status=200)
    return HttpResponse(status=400)


@method_decorator(csrf_exempt, name='dispatch')
def remove_payroll(request, payroll_id):
    if request.method == 'DELETE':
        with connect() as conn:
            dbpayroll = Payrolls(conn)
            dbpayroll.remove(payroll_id)
        return HttpResponse(status=200)
    return HttpResponse(status=400)


def _req_body_to_employee(request):
    request_body_fields = request.body.decode('utf-8')
    employee_fields = json.loads(request_body_fields)
    employee = Employee(
        0,
        employee_fields['full_name'],
        employee_fields['characteristics'],
        employee_fields['is_intern']
    )
    return employee


@method_decorator(csrf_exempt, name='dispatch')
def get_employees(request):
    if request.method == 'GET':
        with connect() as conn:
            dbemployees = Employees(conn)
            employees = dbemployees.readall()
        return JsonResponse(employees, safe=False, encoder=ModelsJSONEncoder, json_dumps_params={'indent': 2})
    return HttpResponse(status=400)


@method_decorator(csrf_exempt, name='dispatch')
def add_employee(request):
    if request.method == 'POST':
        try:
            employee = _req_body_to_employee(request)
        except (TypeError, KeyError) as e:
            print(e)
            return HttpResponse(status=400)
        with connect() as conn:
            dbemployees = Employees(conn)
            dbemployees.add(employee)
        return HttpResponse(status=200)
    return HttpResponse(status=400)


@method_decorator(csrf_exempt, name='dispatch')
def update_employee(request, employee_id):
    if request.method == 'PUT':
        try:
            employee = _req_body_to_employee(request)
        except (TypeError, KeyError) as e:
            print(e)
            return HttpResponse(status=400)
        with connect() as conn:
            dbemployees = Employees(conn)
            dbemployees.update(employee, employee_id)
        return HttpResponse(status=200)
    return HttpResponse(status=400)


@method_decorator(csrf_exempt, name='dispatch')
def remove_employee(request, employee_id):
    if request.method == 'DELETE':
        with connect() as conn:
            dbemployees = Employees(conn)
            dbemployees.remove(employee_id)
        return HttpResponse(status=200)
    return HttpResponse(status=400)


@method_decorator(csrf_exempt, name='dispatch')
def search_employee(request):
    if request.method == 'GET':
        with connect() as conn:
            dbemployees = Employees(conn)
            characteristicssearch = request.GET.get('characteristics', None)  # FULLTEXT search
            fullnamesearch = request.GET.get('full_name', None)  # LIKE search
            isinternsearch = request.GET.get('is_intern', None)  # WHERE search
            employees = dbemployees.search(characteristicssearch, fullnamesearch, isinternsearch)
        return JsonResponse(employees, safe=False, encoder=ModelsJSONEncoder)
    return HttpResponse(status=400)


@method_decorator(csrf_exempt, name='dispatch')
def export_employees(request):
    with connect() as conn:
        dbemployees = Employees(conn)
        employees = dbemployees.readall()
    return export(request, employees, 'employees')


@method_decorator(csrf_exempt, name='dispatch')
def import_employees(request):
    if request.method == 'POST':
        req_body = request.FILES['file'].read()
        employees_dict = simplexml.loads(req_body)['employees']
        employees = []
        for e in employees_dict:
            e_is_intern = 1 if '1' in e['is_intern'] else 0
            employees.append(Employee(
                0, e['full_name'], e['characteristics'], e_is_intern
            ))
        with connect() as conn:
            dbemployees = Employees(conn)
            dbemployees.importall(employees)
        return HttpResponse(status=200)
    return HttpResponse(status=400)


def _req_body_to_payment(request):
    request_body_fields = request.body.decode('utf-8')
    payment_fields = json.loads(request_body_fields)
    payment = Payment(
        0,
        payment_fields['method'],
        payment_fields['raw_salary'],
        payment_fields['tax_rate']
    )
    return payment


@method_decorator(csrf_exempt, name='dispatch')
def get_payments(request):
    if request.method == 'GET':
        with connect() as conn:
            dbpayments = Payments(conn)
            payments = dbpayments.readall()
        return JsonResponse(payments, safe=False, encoder=ModelsJSONEncoder, json_dumps_params={'indent': 2})
    return HttpResponse(status=400)


@method_decorator(csrf_exempt, name='dispatch')
def add_payment(request):
    if request.method == 'POST':
        try:
            payment = _req_body_to_payment(request)
        except (TypeError, KeyError) as e:
            print(e)
            return HttpResponse(status=400)
        with connect() as conn:
            dbpayments = Payments(conn)
            dbpayments.add(payment)
        return HttpResponse(status=200)
    return HttpResponse(status=400)


@method_decorator(csrf_exempt, name='dispatch')
def update_payment(request, payment_id):
    if request.method == 'PUT':
        try:
            payment = _req_body_to_payment(request)
        except (TypeError, KeyError) as e:
            print(e)
            return HttpResponse(status=400)
        with connect() as conn:
            dbpayments = Payments(conn)
            dbpayments.update(payment, payment_id)
        return HttpResponse(status=200)
    return HttpResponse(status=400)


@method_decorator(csrf_exempt, name='dispatch')
def remove_payment(request, payment_id):
    if request.method == 'DELETE':
        with connect() as conn:
            dbpayments = Payments(conn)
            dbpayments.remove(payment_id)
        return HttpResponse(status=200)
    return HttpResponse(status=400)


@method_decorator(csrf_exempt, name='dispatch')
def search_payment(request):
    if request.method == 'GET':
        with connect() as conn:
            dbpayments = Payments(conn)
            salarymaxrange = request.GET.get('max', None)
            salaryminrange = request.GET.get('min', None)
            payments = dbpayments.search(salarymaxrange, salaryminrange)
        return JsonResponse(payments, safe=False, encoder=ModelsJSONEncoder)
    return HttpResponse(status=400)


@method_decorator(csrf_exempt, name='dispatch')
def export_payments(request):
    with connect() as conn:
        dbpayments = Payments(conn)
        payments = dbpayments.readall()
    return export(request, payments, 'payments')


@method_decorator(csrf_exempt, name='dispatch')
def import_payments(request):
    if request.method == 'POST':
        req_body = request.FILES['file'].read()
        payments_dict = simplexml.loads(req_body)['payments']
        payments = [
            Payment(0, p['method'], p['raw_salary'], p['tax_rate'])
            for p in payments_dict
        ]
        with connect() as conn:
            dbpayments = Payments(conn)
            dbpayments.importall(payments)
        return HttpResponse(status=200)
    return HttpResponse(status=400)


def _req_body_to_project(request):
    request_body_fields = request.body.decode('utf-8')
    project_fields = json.loads(request_body_fields)
    project = Project(
        0,
        project_fields['name'],
        project_fields['description'],
    )
    return project


@method_decorator(csrf_exempt, name='dispatch')
def get_projects(request):
    if request.method == 'GET':
        with connect() as conn:
            dbprojects = Projects(conn)
            projects = dbprojects.readall()
        return JsonResponse(projects, safe=False, encoder=ModelsJSONEncoder, json_dumps_params={'indent': 2})
    return HttpResponse(status=400)


@method_decorator(csrf_exempt, name='dispatch')
def add_project(request):
    if request.method == 'POST':
        try:
            project = _req_body_to_project(request)
        except (TypeError, KeyError) as e:
            print(e)
            return HttpResponse(status=400)
        with connect() as conn:
            dbprojects = Projects(conn)
            dbprojects.add(project)
        return HttpResponse(status=200)
    return HttpResponse(status=400)


@method_decorator(csrf_exempt, name='dispatch')
def update_project(request, project_id):
    if request.method == 'PUT':
        try:
            project = _req_body_to_project(request)
        except (TypeError, KeyError) as e:
            print(e)
            return HttpResponse(status=400)
        with connect() as conn:
            dbprojects = Projects(conn)
            dbprojects.update(project, project_id)
        return HttpResponse(status=200)
    return HttpResponse(status=400)


@method_decorator(csrf_exempt, name='dispatch')
def remove_project(request, project_id):
    if request.method == 'DELETE':
        with connect() as conn:
            dbprojects = Projects(conn)
            dbprojects.remove(project_id)
        return HttpResponse(status=200)
    return HttpResponse(status=400)


@method_decorator(csrf_exempt, name='dispatch')
def search_project(request):
    if request.method == 'GET':
        with connect() as conn:
            dbprojects = Projects(conn)
            descriptionlikesearch = request.GET.get('descr', None)
            projects = dbprojects.search(descriptionlikesearch)
        return JsonResponse(projects, safe=False, encoder=ModelsJSONEncoder)
    return HttpResponse(status=400)


@method_decorator(csrf_exempt, name='dispatch')
def export_projects(request):
    with connect() as conn:
        dbprojects = Projects(conn)
        projects = dbprojects.readall()
    return export(request, projects, 'projects')


@method_decorator(csrf_exempt, name='dispatch')
def import_projects(request):
    if request.method == 'POST':
        req_body = request.FILES['file'].read()
        projects_dict = simplexml.loads(req_body)['projects']
        projects = [
            Project(0, p['name'], p['description'])
            for p in projects_dict
        ]
        with connect() as conn:
            dbprojects = Projects(conn)
            dbprojects.importall(projects)
        return HttpResponse(status=200)
    return HttpResponse(status=400)
