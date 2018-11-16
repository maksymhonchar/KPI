#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <strings.h>

#include "headers/chat.h"

/*-------------------------------->>>>> Private structures <<<<<--------------------------------*/
struct msg_s
{
    struct tm sendTime;
    char title[TITLE_LEN_MAX];
    char content[CONTENT_LEN_MAX];
};

struct user_s
{
    char name[NAME_LEN_MAX];
    char surname[SURNAME_LEN_MAX];
    int subFlag;
    list_t *mailBox;
};

struct chat_s
{
    char name[CHAT_NAME_MAX];
    list_t *users;
    list_t *globalMailBox;
};

/*-------------------------------->>>>> Message module <<<<<--------------------------------*/
msg_t *msg_new_empty()
{
    msg_t *out = (msg_t *) malloc ( sizeof( struct msg_s ) );
    time_t t = time(NULL);
    out->sendTime = *localtime(&t);
    strncpy(out->title, EMPTY_MESSAGE, TITLE_LEN_MAX);
    strncpy(out->content, EMPTY_MESSAGE, CONTENT_LEN_MAX);
    return (out);
}

msg_t *msg_new(const char *title, const char *content)
{
    msg_t *out = (msg_t *) malloc ( sizeof( struct msg_s ) );
    time_t t = time(NULL);
    out->sendTime = *localtime(&t);
    strncpy(out->title, title, TITLE_LEN_MAX);
    strncpy(out->content, content, CONTENT_LEN_MAX);
    return (out);
}

void msg_delete(msg_t *messageObj)
{
    free (messageObj);
}

char *msg_getTime(msg_t *messageObj)
{
    char *currentTime = (char *) malloc( MAX_CURRENTTIME_LEN );
    memset(currentTime, 0, MAX_CURRENTTIME_LEN);
    sprintf(currentTime, "%d-%d-%d %d-%d-%d",
            messageObj->sendTime.tm_year + 1900,
            messageObj->sendTime.tm_mon + 1,
            messageObj->sendTime.tm_mday,
            messageObj->sendTime.tm_hour,
            messageObj->sendTime.tm_min,
            messageObj->sendTime.tm_sec
           );
    return (currentTime);
}

char *msg_getTitle(msg_t *messageObj)
{
    return (messageObj->title);
}

char *msg_getContent(msg_t *messageObj)
{
    return (messageObj->content);
}

void msg_setTitle(msg_t *messageObj, const char *title)
{
    memset(messageObj->title, 0, TITLE_LEN_MAX);
    strncpy(messageObj->title, title, TITLE_LEN_MAX);
}

void msg_setContent(msg_t *messageObj, const char *content)
{
    memset(messageObj->content, 0, CONTENT_LEN_MAX);
    strncpy(messageObj->content, content, CONTENT_LEN_MAX);
}

msg_t *msg_copy(msg_t *msgToCopy)
{
    msg_t *out = (msg_t *) malloc ( sizeof( struct msg_s ) );
    *out = *msgToCopy;
    //out->sendTime = msgToCopy->sendTime;
    //out->title = msgToCopy->title;
    //out->content = msgToCopy->content;
    return (out);
}

void msg_print(msg_t *messageObj)
{
    printf("[%s]-[%s] [%s]\n", messageObj->title, messageObj->content, msg_getTime(messageObj));
}

/*-------------------------------->>>>> User module <<<<<--------------------------------*/
user_t *user_new_empty()
{
    user_t *out = (user_t *) malloc ( sizeof( struct user_s ) );
    memset(out->name, 0, NAME_LEN_MAX);
    memset(out->surname, 0, SURNAME_LEN_MAX);
    strncpy(out->name, EMPTY_NAME, NAME_LEN_MAX);
    strncpy(out->surname, EMPTY_NAME, SURNAME_LEN_MAX);
    out->subFlag = 0;
    out->mailBox = list_new();
    return (out);
}

user_t *user_new(const char *name, const char *surname)
{
    user_t *out = (user_t *) malloc ( sizeof( struct user_s ) );
    memset(out->name, 0, NAME_LEN_MAX);
    memset(out->surname, 0, SURNAME_LEN_MAX);
    strncpy(out->name, name, NAME_LEN_MAX);
    strncpy(out->surname, surname, SURNAME_LEN_MAX);
    out->subFlag = 1;
    out->mailBox = list_new();
    return (out);
}

void user_delete(user_t *userObj)
{
    list_delete(userObj->mailBox);
    free(userObj);
}

char *user_getName(user_t *userObj)
{
    return (userObj->name);
}

char *user_getSurname(user_t *userObj)
{
    return (userObj->surname);
}

int user_getMailsAmount(user_t *userObj)
{
    return (list_getSize(userObj->mailBox));
}

list_t *user_getMailbox(user_t *userObj)
{
    return (userObj->mailBox);
}

void user_setName(user_t *userObj, const char *name)
{
    memset(userObj->name, 0, NAME_LEN_MAX);
    strncpy(userObj->name, name, NAME_LEN_MAX);
}

void user_setSurname(user_t *userObj, const char *surname)
{
    memset(userObj->surname, 0, SURNAME_LEN_MAX);
    strncpy(userObj->surname, surname, SURNAME_LEN_MAX);
}

void user_switchSubscription(user_t *userObj)
{
    userObj->subFlag = SUBSCRIPTION_CHECKED == 1
                       ?
                       SUBSCRIPTION_UNCHECKED
                       :
                       SUBSCRIPTION_CHECKED;
}

void user_printInfo(user_t *userObj)
{
    printf("User [%s]-[%s].\nSubscription: [%s]\n",
           userObj->name,
           userObj->surname,
           userObj->subFlag == SUBSCRIPTION_CHECKED ? "ON" : "OFF");
}

void user_printMailBox(user_t *userObj)
{
    int i = 0;
    for (i = 0; i < user_getMailsAmount(userObj); i++)
    {
        msg_t *currMsg = (msg_t *)list_getNodeValueByIndex(userObj->mailBox, i);
        printf("1)");
        msg_print(currMsg);
    }
    if (0 == i)
    {
        printf("Empty mailbox.\n");
    }
}

/*-------------------------------->>>>> Chat module <<<<<--------------------------------*/
chat_t *chat_new(char *chatName)
{
    chat_t *out = (chat_t *) malloc ( sizeof( struct chat_s ) );
    memset(out->name, 0, CHAT_NAME_MAX);
    strncpy(out->name, chatName, CHAT_NAME_MAX);
    out->users = list_new();
    out->globalMailBox = list_new();
    return (out);
}

void chat_delete(chat_t *chatObj)
{
    list_delete(chatObj->users);
    list_delete(chatObj->globalMailBox);
}

char *chat_getName(chat_t *chatObj)
{
    return (chatObj->name);
}

char *chat_getUsersList(chat_t *chatObj)
{
    char *usersList = (char *) malloc (1000);
    memset(usersList, 0, 1000);
    int i = 0;
    for (i = 0; i < list_getSize(chatObj->users); i++)
    {
        user_t *current = (user_t *)list_getNodeValueByIndex(chatObj->users, i);
        strcat(usersList, current->name);
        strcat(usersList, "-");
        strcat(usersList, current->surname);
        strcat(usersList, "\n");
    }
    if (0 == i)
    {
        return ("no users");
    }
    return(usersList);
}

char *chat_getNLastMessages(chat_t *chatObj, int N)
{
    char *lastMessages = (char *) malloc (5000);
    memset(lastMessages, 0, 1000);
    int i = 0;
    for (i = 0; i < list_getSize(chatObj->globalMailBox); i++)
    {
        msg_t *current = (msg_t *)list_getNodeValueByIndex(chatObj->globalMailBox, i);
        if (NULL == current)
        {
            printf("ALERT: NULL POINTER");
            return (lastMessages);
        }
        strcat(lastMessages, current->title);
        strcat(lastMessages, "-");
        strcat(lastMessages, current->content);
        strcat(lastMessages, "\n");
    }
    if (0 == i)
    {
        return ("no messages");
    }
    return (lastMessages);
}

list_t *chat_getUsersObjects(chat_t *chatObj)
{
    return (chatObj->users);
}

void chat_setName(chat_t *chatObj, char *chatName)
{
    memset(chatObj->name, 0, CHAT_NAME_MAX);
    strncpy(chatObj->name, chatName, CHAT_NAME_MAX);
}

void chat_addUser(chat_t *chatObj, char *name, char *surname)
{
    user_t *temp = user_new(name, surname);
    list_insertLast(chatObj->users, (void *)temp);
}

void chat_deleteUser(chat_t *chatObj, char *surname)
{
    for (int i = 0; i < list_getSize(chatObj->users); i++)
    {
        user_t *temp = (user_t *)list_getNodeValueByIndex(chatObj->users, i);
        if (!strcmp(temp->surname, surname))
        {
            list_removeByIndex(chatObj->users, i);
        }
    }
}

void chat_printInfo(chat_t *chatObj)
{
    printf("Herzlich willkommen zum chat [%s]!\n", chatObj->name);
}

void user_sendMessage(chat_t *chatObj, user_t *sender, list_t *receivers, msg_t *message, alert_cb alert)
{
    // Add message to global messages list.
    list_insertLast(chatObj->globalMailBox, (void *)message);
    // Send message to certain users.
    for (int i = 0; i < list_getSize(receivers); i++)
    {
        user_t *currReceiver = (user_t *)list_getNodeValueByIndex(chatObj->users, i);
        if (NULL == currReceiver)
        {
            printf("ALERT: NULL POINTER");
            return;
        }
        // Send message.
        list_insertLast(currReceiver->mailBox, (void *)message);
        // Invoke alert.
        if (currReceiver->subFlag == SUBSCRIPTION_CHECKED)
        {
            alert(sender, currReceiver);
        }
    }
}

void user_sendMessageToAll(chat_t *chatObj, user_t *sender, msg_t *message, alert_cb alert)
{
    // Add message to global messages list.
    list_insertLast(chatObj->globalMailBox, (void *)message);
    // Send message to all users.
    for (int i = 0; i < list_getSize(chatObj->users); i++)
    {
        user_t *currReceiver = (user_t *)list_getNodeValueByIndex(chatObj->users, i);
        // Check if surnames are same.
        if (NULL == currReceiver)
        {
            printf("ALERT: NULL POINTER");
            return;
        }
        // Send message.
        list_insertLast(currReceiver->mailBox, (void *)message);
        // Invoke alert.
        if (currReceiver->subFlag == SUBSCRIPTION_CHECKED)
        {
            alert(sender, currReceiver);
        }
    }
}
