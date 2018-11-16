"""
TGAdmin URL Configuration
"""
from django.contrib import admin
from django.conf.urls import url
from django.urls import path

from tgadmincore import views as coreviews
from analytics import views as anlviews
from managing import views as mngviews
from publication import views as pblviews
from tgbot import views as tgbotviews


urlpatterns = [
    path('admin/', admin.site.urls),
    url(r'^$', coreviews.indexcore, name='indexcore'),
    url(r'^anl/', anlviews.indexanalytics, name='indexanalytics'),
    url(r'^mng/$', mngviews.indexmanaging, name='indexmanaging'),
    url(r'^mng/kick/$', mngviews.managingkick, name='managingkick'),
    url(r'^pbl/$', pblviews.indexpublications, name='indexpublications'),
    url(r'^pbl/pbltext/$', pblviews.publishtext, name='publishtext'),
    url(r'^pbl/addev/$', pblviews.addevent, name='addevent'),
    url(r'^tgbot/$', tgbotviews.tgbotapi, name='tgbotapi'),
    url(r'^tgbot/setup/$', tgbotviews.tgbotsetup, name='tgbotsetup'),
    url(r'^tgbot/rdr/$', tgbotviews.tgbottrack, name='tgbotrdr'),
]
