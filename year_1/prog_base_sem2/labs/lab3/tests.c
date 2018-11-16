#include <stdlib.h> // cmocka unit-tests
#include <stddef.h> // cmocka unit-tests
#include <stdarg.h> // cmocka unit-tests
#include <setjmp.h> // cmocka unit-tests

#include <cmocka.h>

#include "user.h"

static void sdNew_userNew_dataNew__dataName_dataValue__memoryAllocated(void **state)
{
    data_t *testData = data_new("testName", "testValue");
    user_t *testUser = user_new("testUserName");
    supaDrive_t *testSD = sd_new();
    assert_non_null(testData);
    assert_non_null(testData);
    assert_non_null(testData);
    assert_string_equal(testData->dataName, "testName");
    assert_string_equal(testData->dataValue, "testValue");
    assert_string_equal(testUser->dataSet[0]->dataName, "empty");
    assert_string_equal(testSD->repository[0]->dataSet[0]->dataName, "empty");
}

static void addData_deleteData__user_data_SD__userFilledCorrectly(void **state)
{
    data_t *testData = data_new("testName", "testValue");
    user_t *testUser = user_new("testUserName");
    supaDrive_t *testSD = sd_new();
    // Add data to SD.
    sd_addUser(testSD, testUser);
    user_addData(testSD, testUser, testData, alertAddingSuccess, alertAddingWarning);
    assert_string_equal(testSD->repository[0]->name, "testUserName");
    assert_string_equal(testSD->repository[0]->dataSet[0]->dataName, "testName");
    assert_string_equal(testSD->repository[0]->dataSet[0]->dataValue, "testValue");
    // Delete data from SD.
    user_deleteData(testUser);
    assert_string_equal(testSD->repository[0]->dataSet[0]->dataName, "empty");
    assert_string_equal(testSD->repository[0]->dataSet[0]->dataValue, "empty");
}

static void getUsers_getDatas__SD_user_data__userDataWasAdded(void **state)
{
    data_t *testData = data_new("testName", "testValue");
    user_t *testUser = user_new("testUserName");
    supaDrive_t *testSD = sd_new();
    // Add data to SD.
    sd_addUser(testSD, testUser);
    user_addData(testSD, testUser, testData, alertAddingSuccess, alertAddingWarning);
    // Count users and total data amount in SD.
    assert_int_equal(sd_getUsersInDrive(testSD), 1);
    assert_int_equal(sd_getTotalDatasAmount(testSD), 1);
}

static void setRandomData__data__dataWasFilled(void **state)
{
    data_t *testData = data_new("hello", "world");
    data_setRandomData(testData);
    assert_string_not_equal(testData->dataName, "hello");
    assert_string_not_equal(testData->dataValue, "world");
}


int main(void) {
    const struct CMUnitTest tests[] =
    {
        cmocka_unit_test(sdNew_userNew_dataNew__dataName_dataValue__memoryAllocated),
        cmocka_unit_test(addData_deleteData__user_data_SD__userFilledCorrectly),
        cmocka_unit_test(getUsers_getDatas__SD_user_data__userDataWasAdded),
        cmocka_unit_test(setRandomData__data__dataWasFilled),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
