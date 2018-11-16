#include <stdlib.h>  // cmocka unit-tests
#include <stdarg.h>  // cmocka unit-tests
#include <stddef.h>  // cmocka unit-tests
#include <setjmp.h>  // cmocka unit-tests

#include <cmocka.h>

#include "headers/list.h"

/*

Dear Hadinyak R.A. ,

Path to unit-test modules:
includes folder: C:\Program Files (x86)\cmocka\include
libcmocka dll: C:\Program Files (x86)\cmocka\lib\libcmocka.dll.a;
main dll contains in ./bin/Release folder.

*/

static void getNLastMsges__fiveMessages__messagesAdded(void **state)
{
	chat_t *testChat = chat_new("KR_1 chat");
        list_t *usersList = chat_getUsersObjects(testChat);
	chat_addUser(testChat, "Maxim", "Gonchar");
	msg_t *tempMessage1 = msg_new("Hello1", "World");
	msg_t *tempMessage2 = msg_new("Hello2", "World");
	msg_t *tempMessage3 = msg_new("Hello3", "World");
	msg_t *tempMessage4 = msg_new("Hello4", "World");
	msg_t *tempMessage5 = msg_new("Hell5", "World");
	
	// This task isn`t done yet. Agree with -marks.
}

int main()
{
    const struct CMUnitTest tests[] =
    {
        cmocka_unit_test(getNLastMsges__fiveMessages__messagesAdded),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
