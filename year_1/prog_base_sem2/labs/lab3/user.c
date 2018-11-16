#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include <time.h>

#include "user.h"

// private:
static void data_addData(data_t *dataObj, const char *dataName, const char *dataValue)
{
    // Clear previous data.
    memset(dataObj->dataName, 0, MAX_DATANAME_LEN);
    memset(dataObj->dataValue, 0, MAX_DATAVALUE_LEN);
    // Copy data to data object.
    strncpy(dataObj->dataName, dataName, MAX_DATANAME_LEN);
    strncpy(dataObj->dataValue, dataValue, MAX_DATAVALUE_LEN);
}

static void data_deleteData(data_t *dataObj)
{
    // Clear previous data.
    memset(dataObj->dataName, 0, MAX_DATANAME_LEN);
    memset(dataObj->dataValue, 0, MAX_DATAVALUE_LEN);
    // Add 'empty' data.
    strncpy(dataObj->dataName, EMPTY_STRING, MAX_DATANAME_LEN);
    strncpy(dataObj->dataValue, EMPTY_STRING, MAX_DATAVALUE_LEN);
}

// public:
supaDrive_t *sd_new()
{
    supaDrive_t *out = (supaDrive_t *)malloc(sizeof(struct supaDrive_s));
    for(int i = 0; i < MAX_CLIENTS_AMOUNT; i++)
        out->repository[i] = user_new(EMPTY_STRING);
    out->usersInDrive = 0;
    return (out);
}

user_t *user_new(const char *name)
{
    user_t *out = (user_t *)malloc(sizeof(struct user_s));
    strncpy(out->name, name, MAX_NAME_LEN);
    for( int i = 0; i < MAX_DATASET_LEN; i++)
        out->dataSet[i] = data_new(EMPTY_STRING, EMPTY_STRING);
    out->dataCount = 0;
    return (out);
}

data_t *data_new(const char *dataName, const char *dataValue)
{
    data_t *out = (data_t *)malloc(sizeof(struct data_s));
    strncpy(out->dataName, dataName, MAX_DATANAME_LEN);
    strncpy(out->dataValue, dataValue, MAX_DATAVALUE_LEN);
    return (out);
}

void sd_delete(supaDrive_t *sdObj)
{
    for(int i = 0; i < MAX_CLIENTS_AMOUNT; i++)
        user_delete(sdObj->repository[i]);
    free(sdObj);
}

void user_delete(user_t *userObj)
{
    for(int i = 0; i < MAX_DATASET_LEN; i++)
        data_delete(userObj->dataSet[i]);
    free (userObj);
}

void data_delete(data_t *dataObj)
{
    free (dataObj);
}

int sd_getUsersInDrive(const supaDrive_t *sdObj)
{
    return (sdObj->usersInDrive);
}

int sd_getTotalDatasAmount(const supaDrive_t *sdObj)
{
    int total = 0;
    for(int i = 0; i < MAX_CLIENTS_AMOUNT; i++)
    {
        total += sdObj->repository[i]->dataCount;
    }
    return (total);
}

void sd_addUser(supaDrive_t *sdObj, user_t *newUserObj)
{
    if(sdObj->usersInDrive >= MAX_CLIENTS_AMOUNT)
    {
        fprintf(stderr, "[CONSOLE] >Cannot add user [%s] - limit of users reached in supaDrive.\n", newUserObj->name);
        return;
    }
    printf("[CONSOLE] >New user was added: %s\n", newUserObj->name);
    sdObj->repository[sdObj->usersInDrive] = newUserObj;
    sdObj->usersInDrive++;
}

void sd_deleteUser(supaDrive_t *sdObj)
{
    if(sdObj->usersInDrive <= 0)
    {
        fprintf(stderr, "[CONSOLE] >Cannot delete user from empty repository.\n");
        return;
    }
    printf("[CONSOLE] >User %s was deleted.\n", sdObj->repository[sdObj->usersInDrive - 1]->name);
    sdObj->repository[sdObj->usersInDrive - 1]->dataCount = 0;
    user_delete(sdObj->repository[sdObj->usersInDrive - 1]);
    sdObj->repository[sdObj->usersInDrive - 1] = user_new(EMPTY_STRING);
    sdObj->usersInDrive--;
}

void user_addData(supaDrive_t *sdObj, user_t *userObj, data_t *dataObj, alert_cb alertOK, alert_cb alertWrong)
{
    if(sd_getTotalDatasAmount(sdObj) >= MAX_DRIVE_SIZE)
    {
        alertWrong(userObj, dataObj);
        return;
    }

    alertOK(userObj, dataObj);
    if (userObj->dataCount >= MAX_DATASET_LEN)
    {
        fprintf(stderr, "[CONSOLE] >Limit of posts reached by user %s\n.", userObj->name);
        return;
    }
    printf("[CONSOLE] >Data [%s]-[%s] was added to user [%s].\n", dataObj->dataName, dataObj->dataValue, userObj->name);
    data_addData(userObj->dataSet[userObj->dataCount],
                 dataObj->dataName,
                 dataObj->dataValue);
    userObj->dataCount++;
}

void user_deleteData(user_t *userObj)
{
    if (userObj->dataCount <= 0)
    {
        fprintf(stderr, "[CONSOLE] >Cannot delete from empty data pool by user %s.\n", userObj->name);
        return;
    }
    printf("[CONSOLE] >Data [%s]-[%s] was deleted from user [%s].\n",
           userObj->dataSet[userObj->dataCount - 1]->dataName,
           userObj->dataSet[userObj->dataCount - 1]->dataValue,
           userObj->name);
    data_deleteData(userObj->dataSet[userObj->dataCount - 1]);
    userObj->dataCount--;
}

void data_setRandomData(data_t *dataObj)
{
    time_t t;
    srand((unsigned int)time(&t));
    // Come up with random string.
    int randomLength = rand()%8 + 2;
    char randomData[randomLength];
    for(int i = 0; i < randomLength; i++)
        randomData[i] = rand()%126 + 34;
    randomData[randomLength] = '\0';
    // Fill dataName field.
    memset(dataObj->dataName, 0, MAX_DATANAME_LEN);
    strncpy(dataObj->dataName, "Random", strlen("Random") + 1);
    // Fill dataValue field.
    memset(dataObj->dataValue, 0, MAX_DATAVALUE_LEN);
    strncpy(dataObj->dataValue, randomData, randomLength);
    printf("[CONSOLE] >Generated random data %s.\n", randomData);
}

void sd_printUsers(const supaDrive_t *sdObj)
{
    printf("[CONSOLE] >Printing information about supaDrive.\n");
    int counter = 0;
    printf("SupaDrive users amount: %d\n", sdObj->usersInDrive);
    puts("Users in supaDrive:");
    for(int i = 0; i < MAX_CLIENTS_AMOUNT; i++)
    {
        if(strcmp(sdObj->repository[i]->name, EMPTY_STRING))
        {
            printf("%d. %s\n", counter + 1, sdObj->repository[i]->name);
            counter++;
        }
    }
    if (0 == counter)
        puts("Empty SupaDrive.");
    else if(MAX_CLIENTS_AMOUNT == counter)
        puts("SupaDrive is full.");
    else
        puts("");
}

void user_printUserData(const user_t *userObj)
{
    printf("[CONSOLE] >Printing user data.\n");
    int counter = 0;
    printf("Name:[%s]\n"
           "Data amount:[%d]\n",
           userObj->name, userObj->dataCount);
    puts("SD account:");
    for(int i = 0; i < MAX_DATASET_LEN; i++)
    {
        if(strcasecmp(userObj->dataSet[i]->dataValue, EMPTY_STRING))
        {
            printf("%d. %s - %s\n", counter + 1, userObj->dataSet[i]->dataName, userObj->dataSet[i]->dataValue);
            counter++;
        }
    }
    if(0 == counter)
        puts("Empty user account.");
    else if (MAX_DATASET_LEN == counter)
        puts("Full user account.");
    else
        puts("");
}

void sd_printDetailedUserData(const supaDrive_t *sdObj)
{
    for(int i = 0; i < MAX_CLIENTS_AMOUNT; i++) {
        if(strcmp(sdObj->repository[i]->name, EMPTY_STRING))
        {
            user_printUserData(sdObj->repository[i]);
            puts("");
        }
    }
}

// Callback functions.
void alertAddingSuccess(user_t *userObj, data_t *dataObj)
{
    printf("[CALLBACK] >Success adding data [%s]-[%s] by user [%s].\n", dataObj->dataName, dataObj->dataValue, userObj->name);
}

void alertAddingWarning(user_t *userObj, data_t *dataObj)
{
    fprintf(stderr, "[CALLBACK] >Error by adding data [%s]-[%s] by user [%s].\n", dataObj->dataName, dataObj->dataValue, userObj->name);
}
