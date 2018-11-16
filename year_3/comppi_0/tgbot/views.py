import tgbot.botsetup
from django.shortcuts import render, redirect, HttpResponseRedirect
from tgbot.botsetup import setup_bot


def tgbotapi(request):
    print(tgbot.botsetup._token, tgbot.botsetup.TGBotInstance)
    return render(request, 'tgbotindex.html', {
        'token': tgbot.botsetup._token,
        'bot': tgbot.botsetup.TGBotInstance,
    })


def tgbotsetup(request):
    token = 'secret'
    setup_bot(token)
    return redirect('tgbotapi')


def tgbottrack(request):
    redirect_path = request.GET.get('redirect_to')
    tgpostid = int(request.GET.get('post_id', -1))
    utm_campaign_source = request.GET.get('utm_campaign_source', 'None')
    utm_campaign_medium = request.GET.get('utm_campaign_medium', 'None')
    if tgpostid in tgbot.botsetup.TGBotInstance.chat.tracked_posts.keys():
        if utm_campaign_source and utm_campaign_medium:
            tgbot.botsetup.TGBotInstance.chat.tracked_posts[tgpostid].views += 1
            return redirect(redirect_path)
    return redirect('tgbotapi')
