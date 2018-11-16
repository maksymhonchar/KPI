from telegram.ext import Updater, CommandHandler, MessageHandler, Filters
from tgbot.models import TGBot, TGChat, TrackedPost
import requests

_token = None
_updater = None
TGBotInstance = None
_kickedUsers = {}


def setup_bot(token):
    global _token
    global _updater
    _token = token
    _updater = Updater(token)
    dp = _updater.dispatcher
    dp.add_handler(MessageHandler(Filters.text, newpost))
    dp.add_handler(CommandHandler("start", start))
    dp.add_handler(CommandHandler("info", info))
    dp.add_handler(CommandHandler('allposts', allposts))
    dp.add_handler(CommandHandler("tracked", tracked))
    dp.add_handler(CommandHandler('track', track, pass_args=True, pass_chat_data=True))
    dp.add_handler(CommandHandler("set_autopost", set_timer, pass_args=True, pass_job_queue=True, pass_chat_data=True))
    dp.add_handler(CommandHandler("unset_autopost", unset_timer, pass_chat_data=True))
    _updater.start_polling()


def start(bot, update):
    global TGBotInstance
    if TGBotInstance is None:
        # add an admin
        TGBotInstance = TGBot(_token, update.message.from_user)
        update.message.reply_text('New user log into system {0}'.format(update.message.from_user.first_name))
    else:
        update.message.reply_text('You are already registered:\nyou:{0}\nchat:{1}'.format(
            update.message.from_user.first_name + ' ' + update.message.from_user.last_name,
            update.message.chat.title
        ))
        return
    if update['message']['chat']['type'] != 'private':
        # add a new chat to track
        if TGBotInstance.chat is None:
            TGBotInstance.chat = TGChat(update.message.chat)
            update.message.reply_text('Bot has been added to {0} by {1}'.format(
                update.message.chat.title,
                update.message.from_user.first_name + ' ' + update.message.from_user.last_name
            ))
            # add admin to chat users.
            TGBotInstance.chat.add_chat_user(update.message.from_user)


def newpost(bot, update):
    TGBotInstance.chat.add_post(update.message)
    TGBotInstance.chat.add_chat_user(update.message.from_user)
    checkPost(
        update.message.chat.id,
        update.message.from_user.id,
        update.message
    )

def checkPost(cid, uid, msg):
    if 'fuck' in msg.text:
        kickUser(cid, uid, msg.from_user)


def kickUser(cid, uid, uinst):
    url = '{0}/kickChatMember'.format(_updater.bot.base_url)
    data = {'chat_id': cid, 'user_id': uid}
    requests.post(url, data)
    _kickedUsers.update({uid: uinst})


def sendMsg(cid, text, parse_mode):
    _updater.bot.sendMessage(cid, text, parse_mode=parse_mode)


def info(bot, update):
    update.message.reply_text('admin: {0}\nchat: {1}\nusers:{2}\ntracking_posts:{3}'.format(
        TGBotInstance.admin, TGBotInstance.chat.chatinst,
        TGBotInstance.chat.chat_users, TGBotInstance.chat.tracked_posts
    ))


def tracked(bot, update):
    if not TGBotInstance.chat.tracked_posts.items():
        update.message.reply_text('No posts to track')
        return
    pretty_tracked = '\n'.join(
        ['id{0} - {1}; {2} views'.format(pid, pval.tgpost.text, pval.views)
         for pid, pval in TGBotInstance.chat.tracked_posts.items()]
    )
    update.message.reply_text(pretty_tracked)


def allposts(bot, update):
    if not TGBotInstance.chat.chat_posts.items():
        update.message.reply_text('No posts in the chat')
        return
    pretty_posts = '\n'.join([
        'id{0} - {1}{2}'.format(
            pid, pval.text,
            '\tTRACKED' if pid in TGBotInstance.chat.tracked_posts else ''
        )
        for pid, pval in TGBotInstance.chat.chat_posts.items()]
    )
    update.message.reply_text(pretty_posts)


def track(bot, update, args, chat_data):
    raw_post = TGBotInstance.chat.chat_posts[int(args[0])]
    post_to_track = TrackedPost(raw_post, args[1])
    TGBotInstance.chat.add_tracking_post(post_to_track)


def alarm(bot, job):
    bot.send_message(job.context, text='Beep!')


def set_timer(bot, update, args, job_queue, chat_data):
    chat_id = update.message.chat_id
    try:
        # args[0] should contain the time for the timer in seconds
        due = int(args[0])
        if due < 0:
            update.message.reply_text('Sorry we can not go back to future!')
            return

        # Add job to queue
        job = job_queue.run_once(alarm, due, context=chat_id)
        chat_data['job'] = job

        update.message.reply_text('Timer successfully set!')

    except (IndexError, ValueError):
        update.message.reply_text('Usage: /set <seconds>')


def unset_timer(bot, update, chat_data):
    if 'job' not in chat_data:
        update.message.reply_text('You have no active timer')
        return

    job = chat_data['job']
    job.schedule_removal()
    del chat_data['job']

    update.message.reply_text('Timer successfully unset!')
