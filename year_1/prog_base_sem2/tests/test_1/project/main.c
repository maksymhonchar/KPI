#include <stdio.h>
#include <windows.h>

#include "headers/list.h"
#include "headers/chat.h"

void testCallback(user_t *sender, user_t *receiver);

int main()
{
    // Change console appearance.
    SetConsoleTitle("Chat - Maxim Gonchar Var8");
    SMALL_RECT windowSize = { 0, 0, 79, 49 };
    SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), TRUE, &windowSize);

    // Testing module.
    chat_t *testChat = chat_new("KR_1 chat");
    list_t *usersList = chat_getUsersObjects(testChat);

    chat_printInfo(testChat);
    puts("");

    chat_addUser(testChat, "Maxim", "Gonchar");
    chat_addUser(testChat, "Sergei", "Romaniyk");
    chat_addUser(testChat, "Fedya", "Andrienko");

    printf("Users list:\n%s\n", chat_getUsersList(testChat));
    puts("");

    printf("This guy will send messages now: \n");
    user_t *tempSender = (user_t *) list_getNodeValueByIndex(usersList, 0);
    user_printInfo(tempSender);
    msg_t *tempMessage = msg_new("Hello", "World");
    user_sendMessageToAll(testChat, tempSender, tempMessage, testCallback);

    // Free allocated memory.
    chat_delete(testChat);
    return 0;
}

void testCallback(user_t *sender, user_t *receiver)
{
    printf("[CALLBACK] >User [%s-%s] sent message to user [%s-%s].\n",
           user_getName(sender), user_getSurname(sender),
           user_getName(receiver), user_getSurname(receiver)
          );
}
