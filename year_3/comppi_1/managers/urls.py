from django.urls import path

from .views import (
    apilogin, apilogout,
    apimanageadmin, apimanageregistrant
)

urlpatterns = [
    path('login/', apilogin, name='apilogin'),
    path('logout/', apilogout, name='apilogout'),

    path('admin/', apimanageadmin, name='apimanageadmin'),
    path('registrant/', apimanageregistrant, name='apimanageregistrant')
]
