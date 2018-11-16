from django.shortcuts import render, redirect
import publication.scheduling
import tgbot.botsetup


def indexpublications(request):
    return render(request, 'publicationindex.html')


def publishtext(request):
    text = request.POST.get('publication_text', 'no text')
    parse_mode = request.POST.get('parse_mode', '')
    cid = tgbot.botsetup.TGBotInstance.chat.chatinst.id
    tgbot.botsetup.sendMsg(cid, text, parse_mode)
    return redirect('indexpublications')


def addevent(request):
    return redirect('indexpublications')
    # text = request.POST.get('publication_text', 'no text')
    # time = request.POST.get('event_trime', 'no text')
    # publication.scheduling.addPostingEvent(time, [text])
