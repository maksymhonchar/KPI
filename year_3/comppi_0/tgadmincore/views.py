from django.shortcuts import render


def indexcore(request):
    return render(request, 'index.html')

