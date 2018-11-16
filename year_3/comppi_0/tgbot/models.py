class TGBot(object):
    def __init__(self, token, admin):
        self.token = token
        self.admin = admin
        self.chat = None  # type of TGChat


class TGChat(object):
    def __init__(self, chatinst):
        self.chatinst = chatinst
        self.chat_posts = {}  # post_id: telegram.Post
        self.chat_users = {}  # user_id: telegram.User
        self.tracked_posts = {}  # post_id : telegram.Post, views

    def add_post(self, postinst):
        self.chat_posts.update({postinst.message_id: postinst})

    def add_tracking_post(self, postinst):
        self.tracked_posts.update({postinst.tgpost.message_id: postinst})

    def delete_tracking_post(self, postinst):
        return self.tracked_posts.pop(postinst.id)

    def add_chat_user(self, userinst):
        self.chat_users.update({userinst.id: userinst})


class TrackedPost(object):
    def __init__(self, tgpost, redirect_to):
        self.tgpost = tgpost
        self.views = 0
        self.redirect_to = redirect_to or 'google.com'
        self.utm_campaign_source = 'telegram-campaign-source'
        self.utm_campaign_medium = 'telegram-campaign-medium'
