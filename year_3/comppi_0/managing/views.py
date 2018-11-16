from django.shortcuts import render, redirect
import tgbot.botsetup


def indexmanaging(request):
    kicked_users = tgbot.botsetup._kickedUsers
    chat_users = tgbot.botsetup.TGBotInstance.chat.chat_users
    return render(request, 'managingindex.html', {
        'kicked': kicked_users,
        'chat': chat_users
    })


def managingkick(request):
    uid = int(request.POST.get('uid', -1))
    cid = tgbot.botsetup.TGBotInstance.chat.chatinst.id
    uinst = tgbot.botsetup.TGBotInstance.chat.chat_users[uid]
    tgbot.botsetup.kickUser(cid, uid, uinst)
    return redirect('indexmanaging')
