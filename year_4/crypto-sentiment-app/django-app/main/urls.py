from django.urls import path
from django.views.generic import TemplateView

from . import views


urlpatterns = [
    path('', views.index, name='index'),
    path('currencies/', views.currencies, name='currencies'),
    path('market/', views.market, name='market'),
    path('news/', views.news, name='news'),
    path('dev/', views.dev, name='dev'),
    path('signup/', views.signup, name='signup'),

    path('userguide/', TemplateView.as_view(template_name='userguide.html'), name='userguide'),
    path('devguide/', TemplateView.as_view(template_name='devguide.html'), name='devguide'),
    path('apppurpose/', TemplateView.as_view(template_name='apppurpose.html'), name='apppurpose'),
    path('aboutalgo/', TemplateView.as_view(template_name='aboutalgo.html'), name='aboutalgo'),

    path('api/', views.api_index, name='api_index'),
    path('api/get_market_last', views.api_get_market_last, name='api_get_market_last'),
    path('api/get_price_last', views.api_get_price_last, name='api_get_price_last'),
    path('api/get_tweets_last', views.api_get_tweets_last, name='api_get_tweets_last'),
    path('api/get_reddit_last', views.api_get_reddit_last, name='api_get_reddit_last'),
    path('api/get_news_last', views.api_get_news_last, name='api_get_news_last'),
    path('api/update_last_data', views.api_update_last_data, name='api_update_last_data'),
    path('api/update_range_data', views.api_update_range_data, name='api_update_range_data'),
]
