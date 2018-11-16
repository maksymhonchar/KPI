from django.urls import path

from .views import (
    apisearchorg, apimanageorg,
    apimanagecertificate, apimanagefounder, apimanagegovbody, apimanagelocation, apimanagesubdiv,
    apisearchreport, apimanagereport
)

urlpatterns = [
    path('searchorg/', apisearchorg, name='apisearchorg'),
    path('org/', apimanageorg, name='apimanageorg'),
    path('certificate/', apimanagecertificate, name='apimanagecertificate'),
    path('founder/', apimanagefounder, name='apimanagefounder'),
    path('govbody/', apimanagegovbody, name='apimanagegovbody'),
    path('location/', apimanagelocation, name='apimanagelocation'),
    path('subdiv/', apimanagesubdiv, name='apimanagesubdiv'),

    path('searchreport/', apisearchreport, name='apisearchreport'),
    path('report/', apimanagereport, name='apimanagereport'),
]
