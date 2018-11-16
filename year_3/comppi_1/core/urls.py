from django.urls import path

from .views import (
    index, support, about,
    apimap,
    login, logout,
    adminindex, manageadmin, editregistrant, deleteregistrant, change_org_active_status,
    registrantindex, manageregistrant, editorg,
    manageorg, searchorgindex,
    managereport, searchreportindex,
)

urlpatterns = [
    path('', index, name='index'),
    path('apimap/', apimap, name='apimap'),
    path('support/', support, name='support'),
    path('about/', about, name='about'),

    path('login/', login, name='login'),
    path('logout/', logout, name='logout'),

    path('admin/', adminindex, name='adminindex'),
    path('adminmng/', manageadmin, name='adminmng'),
    path('adminregedit/<int:regid>/', editregistrant, name='adminregedit'),
    path('adminregdelete/<int:regid>/', deleteregistrant, name='adminregdelete'),

    path('registrant/', registrantindex, name='registrantindex'),
    path('registrantmng/', manageregistrant, name='registrantmng'),
    path('registrantorgedit/<int:orgid>/', editorg, name='registrantedit'),
    path('registrantchst/<int:orgid>/', change_org_active_status, name='registrantchst'),

    path('org/<int:orgid>/', manageorg, name='manageorg'),
    path('searchorg/', searchorgindex, name='searchorg'),

    path('report/<int:reportid>/', managereport, name='managereport'),
    path('searchrep/', searchreportindex, name='searchreportindex'),
]
