#pragma once

#include <time.h>
#include "list.h"

#define TITLE_LEN_MAX 100
#define CONTENT_LEN_MAX 1000

#define NAME_LEN_MAX 100
#define SURNAME_LEN_MAX 100
#define MAILBOX_CPCTY_MAX 20

#define MAX_CURRENTTIME_LEN 100

#define CHAT_NAME_MAX 100

#define EMPTY_MESSAGE "__nomessage__"
#define EMPTY_NAME "__noname__"

#define SUBSCRIPTION_CHECKED 1
#define SUBSCRIPTION_UNCHECKED 0

/*-------------------------------->>>>> Message module <<<<<--------------------------------*/
typedef struct msg_s msg_t;

// Constructor and destructor.
msg_t *msg_new_empty();
msg_t *msg_new(const char *title, const char *content);
void msg_delete(msg_t *messageObj);

// Getters and setters.
char *msg_getTime(msg_t *messageObj);
char *msg_getTitle(msg_t *messageObj);
char *msg_getContent(msg_t *messageObj);
void msg_setTitle(msg_t *messageObj, const char *title);
void msg_setContent(msg_t *messageObj, const char *content);

// Other functions.
msg_t *msg_copy(msg_t *msgToCopy);
void msg_print(msg_t *messageObj);

/*-------------------------------->>>>> User module <<<<<--------------------------------*/
typedef struct user_s user_t;

// Callback typedef.
typedef void(* alert_cb)(user_t *sender, user_t *receiver);

// Constructor and destructor.
user_t *user_new_empty();
user_t *user_new(const char *name, const char *surname);
void user_delete(user_t *userObj);

// Getters and setters.
char *user_getName(user_t *userObj);
char *user_getSurname(user_t *userObj);
int user_getMailsAmount(user_t *userObj);
list_t *user_getMailbox(user_t *userObj);
void user_setName(user_t *userObj, const char *name);
void user_setSurname(user_t *userObj, const char *surname);
void user_switchSubscription(user_t *userObj);

// Other functions.
void user_printInfo(user_t *userObj);
void user_printMailBox(user_t *userObj);

/*-------------------------------->>>>> Chat module <<<<<--------------------------------*/
typedef struct chat_s chat_t;

// Constructor and destructor.
chat_t *chat_new(char *chatName);
void chat_delete(chat_t *chatObj);

// Getters and setters.
char *chat_getName(chat_t *chatObj);
char *chat_getUsersList(chat_t *chatObj);
char *chat_getNLastMessages(chat_t *chatObj, int N);
list_t *chat_getUsersObjects(chat_t *chatObj);
void chat_setName(chat_t *chatObj, char *chatName);

// Adding and deleting users to/from chat.
void chat_addUser(chat_t *chatObj, char *name, char *surname);
void chat_deleteUser(chat_t *chatObj, char *surname);

// Other functions.
void chat_printInfo(chat_t *chatObj);

/*-------------------------------->>>>> Sending module <<<<<--------------------------------*/
// Adding and deleting mails to/from the mailbox.
void user_sendMessage(chat_t *chatObj, user_t *sender, list_t *receivers, msg_t *message, alert_cb alert);
void user_sendMessageToAll(chat_t *chatObj, user_t *sender, msg_t *message, alert_cb alert);
