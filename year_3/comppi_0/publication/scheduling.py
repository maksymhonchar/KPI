from publication.models import ScheduledEvent
import tgbot.botsetup
import datetime

_scheduledEventsStorage = []

def checkForEventsToExecute():
    time_now = datetime.datetime.now()
    for e in _scheduledEventsStorage:
        if e.timeexecute < time_now:
            f = e.callback
            arg = e.arguments
            f(arg)


def addPostingEvent(timeexecute, arg):
    to_append = ScheduledEvent(timeexecute, tgbot.botsetup.sendMsg, arg)
    _scheduledEventsStorage.append(to_append)
