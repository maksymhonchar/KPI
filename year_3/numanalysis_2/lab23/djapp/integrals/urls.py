from django.urls import path

from .views import index, romberg, trapezoid

urlpatterns = [
    path('', index, name='index'),
    path('romberg/', romberg, name='romberg'),
    path('trapezoid/', trapezoid, name='trapezoid')
]
