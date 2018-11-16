from django.http import HttpResponse
from django.shortcuts import redirect, render


def index(request):
    return render(request, 'index.html')


def payrolls(request):
    return render(request, 'payrollsindex.html')


def employees(request):
    return render(request, 'employeesindex.html')


def payments(request):
    return render(request, 'paymentsindex.html')


def projects(request):
    return render(request, 'projectsindex.html')


def export_model(request):
    if request.method == 'GET':
        model_to_export = request.GET.get('model_name')
        model_redirect_path = 'http://localhost:8000/api/{0}/export/'.format(model_to_export)
        return redirect(model_redirect_path)
    return HttpResponse(status=400)


def import_model(request):
    if request.method == 'POST':
        if request.FILES['file']:
            model_to_export = request.GET.get('model_name')
            model_redirect_path = 'http://localhost:8000/api/{0}/import/'.format(model_to_export)
            return redirect(model_redirect_path)
        return redirect('indexpage')
    return HttpResponse(status=400)
