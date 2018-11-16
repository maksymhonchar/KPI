from publication import views
from django.urls import path


urlpatterns = [
    path('', views.indexpublications)
]
