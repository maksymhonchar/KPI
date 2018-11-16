#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <strings.h>

#include "director.h"
#include "socket.h"
#include "http.h"

#ifndef TRUE
#define TRUE 1
#endif

#define XML_FILEPATH "StartupDirector.xml"

int main()
{
    lib_init();
    socket_t * server = socket_new();
    socket_bind(server, 5000);
    socket_listen(server);
    char buf[100000];
    int currentDirectors_Count = DIRECTORS_COUNT;

    Director_T *directorSet[100];
    for(int i = 0; i < 100; i++)
        directorSet[i] = director_new();
    xmlParse(directorSet, XML_FILEPATH);

    while(TRUE)
    {
        socket_t * client = socket_accept(server);
        socket_read(client, buf, sizeof(buf));
        printf("%s", buf);
        http_request_t request = http_request_parse(buf);

        if(!strcmp(request.method, "GET"))
        {
            if(!strcmp(request.uri, "/"))
            {
                http_sendHtml(client, "html/index.html");
            }
            else if(!strcmp(request.uri, "/directors"))
            {
                char buffer[10000] = "";
                char htmlPageContent[10000] = "";
                char bufferToWrite[100000] = "";

                strcat(htmlPageContent, "<html><title>Directors list.</title><body><pre>");
                for(int i = 0, dirCounter = 0; i < currentDirectors_Count; i++)
                {
                    if(!strcmp(directorSet[i]->name, "EMPTY"))
                        continue;
                    sprintf(buffer, "Director %i:\n"
                            "\tname: %s\n"
                            "\tsurname: %s\n"
                            "\tnationality: %s\n"
                            "\tbirthdate: %d-%d-%d\n"
                            "\tenthusiasm: %d\n"
                            "\texperience: %.2f\n"
                            "\tmoney: %d\n"
                            "\tstartup: %s\n"
                            "\tstartup budget: %d\n\n",
                            (dirCounter+1),
                            directorSet[i]->name,
                            directorSet[i]->surname,
                            directorSet[i]->nationality,
                            directorSet[i]->birthDate.tm_year, directorSet[i]->birthDate.tm_mon, directorSet[i]->birthDate.tm_mday,
                            directorSet[i]->enthusiasm,
                            directorSet[i]->experience,
                            directorSet[i]->money,
                            directorSet[i]->startup.name,
                            directorSet[i]->startup.budget);
                    strcat(htmlPageContent, buffer);
                    dirCounter++;
                }
                strcat(htmlPageContent, "</pre></body></html>\n");
                sprintf(bufferToWrite,
                        "\nHTTP/1.1 200 OK\n"
                        "Content-Type: text/html\n"
                        "Content-Length: %i\n"
                        "\n%s", strlen(htmlPageContent), htmlPageContent)
                ;
                socket_write_string(client, bufferToWrite);
            }
            else if(strstr(request.uri, "/directors/"))
            {
                int id = 0;
                int checkCode = sscanf(request.uri, "/directors/%d", &id);

                if(checkCode != 0 && id > 0 && id <= currentDirectors_Count)
                {
                    char htmlPageContent[100000] = "";
                    char buffer[100000] = "";
                    char bufferToWrite[100000] = "";

                    strcat(htmlPageContent, "<html><title>Director page.</title><body><pre>");
                    if(!strcmp(directorSet[id]->name, "EMPTY"))
                    {
                        sprintf(buffer, "Director with id %i was deleted.", id);
                    }
                    else
                    {
                        sprintf(buffer, "Director %i:\n"
                                "\tname: %s\n"
                                "\tsurname: %s\n"
                                "\tnationality: %s\n"
                                "\tbirthdate: %d-%d-%d\n"
                                "\tenthusiasm: %d\n"
                                "\texperience: %.2f\n"
                                "\tmoney: %d\n"
                                "\tstartup: %s\n"
                                "\tstartup budget: %d\n\n",
                                id,
                                directorSet[id - 1]->name,
                                directorSet[id - 1]->surname,
                                directorSet[id - 1]->nationality,
                                directorSet[id - 1]->birthDate.tm_year, directorSet[id - 1]->birthDate.tm_mon, directorSet[id - 1]->birthDate.tm_mday,
                                directorSet[id - 1]->enthusiasm,
                                directorSet[id - 1]->experience,
                                directorSet[id - 1]->money,
                                directorSet[id - 1]->startup.name,
                                directorSet[id - 1]->startup.budget);
                        strcat(htmlPageContent, buffer);
                    }
                    strcat(htmlPageContent, "</pre></body></html>\n");
                    sprintf(bufferToWrite,
                            "\nHTTP/1.1 200 OK\n"
                            "Content-Type: text/html\n"
                            "Content-Length: %i\n"
                            "\n%s", strlen(htmlPageContent), htmlPageContent
                           );
                    socket_write_string(client, bufferToWrite);
                }
                else
                {
                    http_sendHtml(client, "html/pageNotFound.html");
                }
            }
            else
            {
                http_sendHtml(client, "html/pageNotFound.html");
            }
        }
        else if(!strcmp(request.method, "DELETE"))
        {
            int id;
            int checkCode = sscanf(request.uri, "/directors/%d", &id);
            if(checkCode != 0 && id > 0 && id <= currentDirectors_Count)
            {
                // Write empty fields to director.
                strcpy(directorSet[id - 1]->name, "EMPTY");
                strcpy(directorSet[id - 1]->surname, "EMPTY");
                strcpy(directorSet[id - 1]->nationality, "EMPTY");
                directorSet[id - 1]->birthDate.tm_year = 0;
                directorSet[id - 1]->birthDate.tm_mon = 0;
                directorSet[id - 1]->birthDate.tm_mday = 0;
                directorSet[id - 1]->enthusiasm = 0;
                directorSet[id - 1]->experience = 0;
                directorSet[id - 1]->money = 0;
                strcpy(directorSet[id - 1]->startup.name, "EMPTY");
                directorSet[id - 1]->startup.budget = 0;
                // Write 'result page' to http socket.
                http_sendHtml(client, "html/directordeleted.html");
            }
            else
            {
                http_sendHtml(client, "html/pageNotFound.html");
            }

        }
        else if(!strcmp(request.method, "POST"))
        {
            const char *name = http_request_getArg(&request, "name");
            const char *surname = http_request_getArg(&request, "surname");
            const char *nationality = http_request_getArg(&request, "nationality");
            const char *birthDate = http_request_getArg(&request, "birthdate");
            const char *enthusiasm = http_request_getArg(&request, "enthusiasm");
            const char *experience = http_request_getArg(&request, "experience");
            const char *money = http_request_getArg(&request, "money");
            const char *startupName = http_request_getArg(&request, "sname");
            const char *startupBudget = http_request_getArg(&request, "sbudget");

            // Set director fields
            strcpy(directorSet[currentDirectors_Count-1]->name, name);
            strcpy(directorSet[currentDirectors_Count-1]->surname, surname);
            strcpy(directorSet[currentDirectors_Count-1]->nationality, nationality);
            directorSet[currentDirectors_Count-1]->birthDate.tm_year = 1998;
            directorSet[currentDirectors_Count-1]->birthDate.tm_mon = 1;
            directorSet[currentDirectors_Count-1]->birthDate.tm_mday = 12;
            directorSet[currentDirectors_Count-1]->enthusiasm = atoi(enthusiasm);
            directorSet[currentDirectors_Count-1]->experience = atof(experience);
            directorSet[currentDirectors_Count-1]->money = atoi(money);
            strcpy(directorSet[currentDirectors_Count-1]->startup.name, startupName);
            directorSet[currentDirectors_Count-1]->startup.budget = atoi(startupBudget);

            http_sendHtml(client, "html/userwritten.html");
            // Increase current directors amount.
            currentDirectors_Count++;
        }
        else if(!strcmp(request.method, "KEEPALIVE"))
        {
            // Handler for empty request.
            // Program shouldn't do anything in this case.
            printf("User did an empty request.");
        }
        else
        {
            http_sendHtml(client, "html/incorrectMethod.html");
        }

        socket_free(client);
    }
    socket_free(server);
    lib_free();
    return 0;
}
