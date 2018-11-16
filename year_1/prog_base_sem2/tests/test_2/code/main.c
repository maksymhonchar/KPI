#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <WinSock2.h>
#include <windows.h>
#include <conio.h>

#include "../headers/sqlite3.h"
#include "../headers/dbModule.h"
#include "../headers/director.h"
#include "../headers/list.h"
#include "../headers/xmlModule.h"
#include "../headers/http.h"
#include "../headers/socket.h"
#include "../headers/FSHelper.h"
#include "../headers/client.h"

#ifndef TRUE
#define TRUE
#endif // TRUE

#define CURL_STATICLIB

int main(void)
{
    // Begin work with sockets.
    lib_init();

    // Initialize server socket.
    socket_t *server = socket_new();
    socket_bind(server, 5000);
    socket_listen(server);

    // Create directors set.
    director_t *directorsSet[MAX_DIRECTORS_AMOUNT];
    for (int i = 0; i < MAX_DIRECTORS_AMOUNT; i++)
    {
        directorsSet[i] = director_new_empty();
    }
    xmlModule_parseDirector(directorsSet);

    // Create database entity.
    db_t *testDB = database_new(DATABASE_FILE_PATH);
    db_t *testDB2 = database_new(DATABASE_FILE_PATH2);

    // List to hold all directors together.
    list_t *dirsList;

    // R.A. host name for second task.
    const char *hostName = "http://pb-homework.appspot.com/test/var/19?format=xml";

    // Buffer for socket messages.
    char socketBuffer[10000] = "\0";

    while (TRUE)
    {
        printf("Waiting for connection...");

        // Get message from server.
        socket_t *client = socket_accept(server);
        socket_read(client, socketBuffer, sizeof(socketBuffer));
        printf("%s", socketBuffer);

        // Parse message from server to structure http_request_t.
        http_request_t request = http_request_parse(socketBuffer);

        // Invoke certain http request method.
        if (!strcmp(request.method, "GET"))
        {
            // First task. (2)
            if (!strcmp(request.uri, "/info"))
            {
                http_sendXML(client, "src/data/Info.xml");
            }
            // Second task. (3)
            else if (!strcmp(request.uri, "/external"))
            {
                http_sendHtml(client, "src/html/notDone.html");
            }
            // Third task (5)
            else if (!strcmp(request.uri, "/database"))
            {
                dirsList = database_getDirectorsList(testDB);
                xmlModule_listToXML(dirsList);
                http_sendXML(client, "src/data/Directors.xml");
            }
            // Fourth task (10);
            else if (strstr(request.uri, "/database/tables/"))
            {
                // Buffer to hold certain table name.
                char tableName[200] = "\0";
                // Get table name.
                int checkCode = sscanf(request.uri, "/database/tables/%s", tableName);

                // User can use only two databases: Director1 or Director2.
                if (checkCode != 0 && (!strcmp("Directors", tableName) || !strcmp("Directors2", tableName)))
                {
                    // Send data about certain database!
                    if (!strcmp("Directors", tableName))
                    {
                        dirsList = database_getDirectorsList(testDB);
                        xmlModule_xmlDatabaseInfo(list_getSize(dirsList), "Directors", XML_FILE_PATH);
                        http_sendXML(client, XML_FILE_PATH);
                    }
                    else if (!strcmp("Directors2", tableName))
                    {
                        dirsList = database_getDirectorsList(testDB2);
                        xmlModule_xmlDatabaseInfo(list_getSize(dirsList), "Directors2", XML_FILE_PATH2);
                        http_sendXML(client, XML_FILE_PATH2);
                    }
                }
                // Handle situation, when there is no certain database.
                else
                {
                    http_sendHtml(client, "src/html/databaseHelp.html");
                }
            }
            else
            {
                http_sendHtml(client, "src/html/pageNotFound.html");
            }
        }
        else if (!strcmp(request.method, "KEEPALIVE"))
        {
            // Handler for empty request.
            // Program shouldn't do anything in this case.
            http_sendHtml(client, "src/html/emptyMethod.html");
        }
        else
        {
            http_sendHtml(client, "src/html/incorrectMethod.html");
        }
        socket_free(client);
    }

    // At the end of the program, free allocated memory.
    socket_free(server);
    lib_free();
    for (int i = 0; i < MAX_DIRECTORS_AMOUNT; i++)
    {
        director_delete(directorsSet[i]);
    }
    database_delete(testDB);
    database_delete(testDB2);
    list_delete(dirsList);

    // End of the program.
    return 0;
}
