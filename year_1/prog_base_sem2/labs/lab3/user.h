#pragma once

#define MAX_NAME_LEN 100
#define MAX_DATANAME_LEN 100
#define MAX_DATAVALUE_LEN 100
#define MAX_DATASET_LEN 5

#define MAX_DRIVE_SIZE 5
#define MAX_CLIENTS_AMOUNT 10

#define EMPTY_STRING "empty"

typedef struct data_s {
    char dataName[MAX_DATANAME_LEN];
    char dataValue[MAX_DATAVALUE_LEN];
} data_t;

typedef struct user_s {
    char name[MAX_NAME_LEN];
    int dataCount;
    data_t *dataSet[MAX_DATASET_LEN];
} user_t;

typedef struct supaDrive_s
{
    int usersInDrive;
    user_t *repository[MAX_CLIENTS_AMOUNT];
} supaDrive_t;

typedef void(* alert_cb)(user_t *userObj, data_t *dataObj);

// Constructors and destructors.
supaDrive_t *sd_new();
user_t *user_new(const char *name);
data_t *data_new(const char *dataName, const char *dataVaslue);
void sd_delete(supaDrive_t *sdObj);
void user_delete(user_t *userObj);
void data_delete(data_t *dataObj);

// Getter.
int sd_getUsersInDrive(const supaDrive_t *sdObj);
int sd_getTotalDatasAmount(const supaDrive_t *sdObj);

// Functions for adding and deleting users to/from supaDrive.
void sd_addUser(supaDrive_t *sdObj, user_t *newUserObj);
void sd_deleteUser(supaDrive_t *sdObj);

// Functions for adding and deleting data to/from user.
void user_addData(supaDrive_t *sdObj, user_t *userObj, data_t *dataObj, alert_cb alertOK, alert_cb alertWrong);
void user_deleteData(user_t *userObj);

// Other functions.
void data_setRandomData(data_t *dataObj);
void sd_printUsers(const supaDrive_t *sdObj);
void user_printUserData(const user_t *userObj);
void sd_printDetailedUserData(const supaDrive_t *sdObj);

// Callback functions.
void alertAddingSuccess(user_t *userObj, data_t *dataObj);
void alertAddingWarning(user_t *userObj, data_t *dataObj);

//TODO: alerts for delete method
