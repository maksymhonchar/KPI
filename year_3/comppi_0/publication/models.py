class ScheduledEvent(object):
    def __init__(self, time, cb, arg):
        self.timeexecute = time
        self.callback = cb
        self.arguments = arg
