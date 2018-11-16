import datetime
import json

import simplexml
from django.http import HttpResponse, JsonResponse
from django.utils.decorators import method_decorator
from django.views.decorators.csrf import csrf_exempt

from api.models import Employee, ModelsJSONEncoder, Payment, Payroll, Project


def index(request):
    if request.method == 'GET':
        return JsonResponse({
            'text': 'welcome to API index!',
        })


def dict_from_class(cls):
    return dict(
        (k, v) for (k, v) in cls.__dict__.items()
    )


def export(request, data, dbmodelname):
    if request.method == 'GET':
        data = {
            dbmodelname: [
                {dbmodelname[:-1]: el} for el in data
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
        employee_id=payroll_fields['employee_id'],
        payment_id=payroll_fields['payment_id'],
        project_id=payroll_fields['project_id'],
        payroll_date=datetime.datetime.strptime(payroll_fields['payroll_date'], "%Y-%m-%d")
    )
    return payroll


@method_decorator(csrf_exempt, name='dispatch')
def get_payrolls(request):
    if request.method == 'GET':
        payrolls = list(Payroll.objects.all().values())
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
        payroll.save()
        return HttpResponse(status=200)
    return HttpResponse(status=400)


@method_decorator(csrf_exempt, name='dispatch')
def update_payroll(request, payroll_id):
    if request.method == 'PUT':
        try:
            payroll = _req_body_to_payroll(request)
            payroll.id = payroll_id
        except (TypeError, KeyError) as e:
            print(e)
            return HttpResponse(status=400)
        payroll.save()
        return HttpResponse(status=200)
    return HttpResponse(status=400)


@method_decorator(csrf_exempt, name='dispatch')
def remove_payroll(request, payroll_id):
    if request.method == 'DELETE':
        payroll = Payroll.objects.get(id=payroll_id)
        payroll.delete()
        return HttpResponse(status=200)
    return HttpResponse(status=400)


def _req_body_to_employee(request):
    request_body_fields = request.body.decode('utf-8')
    employee_fields = json.loads(request_body_fields)
    employee = Employee(
        full_name=employee_fields['full_name'].encode('utf-8'),
        characteristics=employee_fields['characteristics'].encode('utf-8'),
        is_intern=employee_fields['is_intern']
    )
    return employee


@method_decorator(csrf_exempt, name='dispatch')
def get_employees(request):
    if request.method == 'GET':
        employees = list(Employee.objects.all().values())
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
        employee.save()
        return HttpResponse(status=200)
    return HttpResponse(status=400)


@method_decorator(csrf_exempt, name='dispatch')
def update_employee(request, employee_id):
    if request.method == 'PUT':
        try:
            employee = _req_body_to_employee(request)
            employee.id = employee_id
        except (TypeError, KeyError) as e:
            print(e)
            return HttpResponse(status=400)
        employee.save()
        return HttpResponse(status=200)
    return HttpResponse(status=400)


@method_decorator(csrf_exempt, name='dispatch')
def remove_employee(request, employee_id):
    if request.method == 'DELETE':
        employee = Employee.objects.get(id=employee_id)
        employee.delete()
        return HttpResponse(status=200)
    return HttpResponse(status=400)


@method_decorator(csrf_exempt, name='dispatch')
def search_employee(request):
    if request.method == 'GET':
        characteristicssearch = request.GET.get('characteristics', None)  # FULLTEXT search
        fullnamesearch = request.GET.get('full_name', None)  # LIKE search
        isinternsearch = request.GET.get('is_intern', None)  # WHERE search

        if characteristicssearch:
            employees = list(Employee.objects.filter(
                characteristics__icontains=characteristicssearch
            ).values())
        elif characteristicssearch:
            employees = list(Employee.objects.filter(
                full_name__icontains=fullnamesearch
            ).values())
        elif isinternsearch:
            employees = list(Employee.objects.filter(
                is_intern=isinternsearch
            ).values())
        else:
            raise RuntimeError('Missing all search arguments in employee.search')
        return JsonResponse(employees, safe=False, encoder=ModelsJSONEncoder)
    return HttpResponse(status=400)


@method_decorator(csrf_exempt, name='dispatch')
def export_employees(request):
    employees = list(Employee.objects.all().values())
    return export(request, employees, 'employees')


@method_decorator(csrf_exempt, name='dispatch')
def import_employees(request):
    if request.method == 'POST':
        Employee.objects.all().delete()
        req_body = request.FILES['file'].read()
        employees_dict = simplexml.loads(req_body)['employees']
        for e in employees_dict:
            e_is_intern = 1 if '1' in e['is_intern'] else 0
            employee_tosave = Employee(
                full_name=e['full_name'],
                characteristics=e['characteristics'],
                is_intern=e_is_intern
            )
            employee_tosave.save()
        return HttpResponse(status=200)
    return HttpResponse(status=400)


def _req_body_to_payment(request):
    request_body_fields = request.body.decode('utf-8')
    payment_fields = json.loads(request_body_fields)
    payment = Payment(
        method=payment_fields['method'].encode('utf-8'),
        raw_salary=payment_fields['raw_salary'],
        tax_rate=payment_fields['tax_rate']
    )
    return payment


@method_decorator(csrf_exempt, name='dispatch')
def get_payments(request):
    if request.method == 'GET':
        payments = list(Payment.objects.all().values())
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
        payment.save()
        return HttpResponse(status=200)
    return HttpResponse(status=400)


@method_decorator(csrf_exempt, name='dispatch')
def update_payment(request, payment_id):
    if request.method == 'PUT':
        try:
            payment = _req_body_to_payment(request)
            payment.id = payment_id
        except (TypeError, KeyError) as e:
            print(e)
            return HttpResponse(status=400)
        payment.save()
        return HttpResponse(status=200)
    return HttpResponse(status=400)


@method_decorator(csrf_exempt, name='dispatch')
def remove_payment(request, payment_id):
    if request.method == 'DELETE':
        payment = Payment.objects.get(id=payment_id)
        payment.delete()
        return HttpResponse(status=200)
    return HttpResponse(status=400)


@method_decorator(csrf_exempt, name='dispatch')
def search_payment(request):
    if request.method == 'GET':
        salaryminrange = request.GET.get('min', None)
        salarymaxrange = request.GET.get('max', None)
        payments = list(Payment.objects.filter(
            raw_salary__gte=salaryminrange, raw_salary__lte=salarymaxrange
        ).values())
        return JsonResponse(payments, safe=False, encoder=ModelsJSONEncoder)
    return HttpResponse(status=400)


@method_decorator(csrf_exempt, name='dispatch')
def export_payments(request):
    payments = list(Payment.objects.all().values())
    return export(request, payments, 'payments')


@method_decorator(csrf_exempt, name='dispatch')
def import_payments(request):
    if request.method == 'POST':
        Employee.objects.all().delete()
        req_body = request.FILES['file'].read()
        payments_dict = simplexml.loads(req_body)['payments']
        for p in payments_dict:
            payment_tosave = Payment(
                method=p['method'],
                raw_salary=p['raw_salary'],
                tax_rate=p['tax_rate']
            )
            payment_tosave.save()
        return HttpResponse(status=200)
    return HttpResponse(status=400)


def _req_body_to_project(request):
    request_body_fields = request.body.decode('utf-8')
    project_fields = json.loads(request_body_fields)
    project = Project(
        name=project_fields['name'].encode('utf-8'),
        description=project_fields['description'].encode('utf-8'),
    )
    return project


@method_decorator(csrf_exempt, name='dispatch')
def get_projects(request):
    if request.method == 'GET':
        projects = list(Project.objects.all().values())
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
        project.save()
        return HttpResponse(status=200)
    return HttpResponse(status=400)


@method_decorator(csrf_exempt, name='dispatch')
def update_project(request, project_id):
    if request.method == 'PUT':
        try:
            project = _req_body_to_project(request)
            project.id = project_id
        except (TypeError, KeyError) as e:
            print(e)
            return HttpResponse(status=400)
        project.save()
        return HttpResponse(status=200)
    return HttpResponse(status=400)


@method_decorator(csrf_exempt, name='dispatch')
def remove_project(request, project_id):
    if request.method == 'DELETE':
        project = Project.objects.get(id=project_id)
        project.delete()
        return HttpResponse(status=200)
    return HttpResponse(status=400)


@method_decorator(csrf_exempt, name='dispatch')
def search_project(request):
    if request.method == 'GET':
        descriptionlikesearch = request.GET.get('descr', None)
        projects = list(Project.objects.filter(
            description__icontains=descriptionlikesearch
        ).values())
        return JsonResponse(projects, safe=False, encoder=ModelsJSONEncoder)
    return HttpResponse(status=400)


@method_decorator(csrf_exempt, name='dispatch')
def export_projects(request):
    projects = list(Project.objects.all().values())
    return export(request, projects, 'projects')


@method_decorator(csrf_exempt, name='dispatch')
def import_projects(request):
    if request.method == 'POST':
        Project.objects.all().delete()
        req_body = request.FILES['file'].read()
        projects_dict = simplexml.loads(req_body)['projects']
        for p in projects_dict:
            project_tosave = Project(
                name=p['name'], description=p['description']
            )
            project_tosave.save()
        return HttpResponse(status=200)
    return HttpResponse(status=400)
