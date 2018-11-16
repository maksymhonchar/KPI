#include <strings.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "../headers/director.h"
#include "../headers/xmlModule.h"
#include "../headers/server.h"

//--------------------------------------->>> Private methods <<<---------------------------------------

void _server_generateBadRequestHTML(const char *errorTitle, const char *errorMsg)
{
    char htmlBuf[10000] = "\0";

    sprintf(htmlBuf, "<html><head><style type =\"text/css\" >.footer { position: fixed; text-align: center; bottom: 10px; width: 100%;}h3"
            "{ font-family: verdana; font-size: 150%; margin-bottom: 5px; margin-top: 1px;}</style><title> %s</title>"
            "</head><h3>%s-%s</h3><div class=\"footer\">Maxim Gonchar Lab4 <br/> <a href=\"http://127.0.0.1:5000/home\">Home</a>"
            "</div></body></html>", errorTitle, errorMsg, errorTitle);

    FILE *f = fopen("src/html/badhtmlrequest.html", "w");
    fprintf(f, "%s", htmlBuf);
    fclose(f);
}

int _server_checkRequest(http_request_t *request, director_t *directorObj)
{
    // Pointer to handle strings about directors fields.
    char *data = NULL;
    // Analyze info in http request. Return 0 (false) if something goes wrong.
    // Check "name" field.
    data = (char *)http_request_getArg(request, "name");
    if (NULL == data)
    {
        _server_generateBadRequestHTML("405 error", "Bad POST request (error in name)");
        return (0);
    }
    if (strlen(data) >= 25)
    {
        _server_generateBadRequestHTML("343 error", "Bad POST request - error in \"name\" field.");
        return (0);
    }
    director_setName(directorObj, data);
    // Check "surname" field.
    data = (char *)http_request_getArg(request, "surname");
    if (NULL == data)
    {
        _server_generateBadRequestHTML("405 error", "Bad POST request (error in surname)");
        return (0);
    }
    if (strlen(data) >= 25)
    {
        _server_generateBadRequestHTML("343 error", "Bad POST request - error in \"surname\" field.");
        return (0);
    }
    director_setSurname(directorObj, data);
    // Check "investments" field.
    data = (char *)http_request_getArg(request, "investments");
    if (NULL == data)
    {
        _server_generateBadRequestHTML("405 error", "Bad POST request (error in investments)");
        return (0);
    }
    if (atoi(data) <= 0 || !isdigit(data[0]) || strlen(data) > 15)
    {
        _server_generateBadRequestHTML("343 error", "Bad POST request - error in \"investments\" field");
        return (0);
    }
    director_setInvestments(directorObj, atoi(data));
    // Check "years" field.
    data = (char *)http_request_getArg(request, "years");
    if (NULL == data)
    {
        _server_generateBadRequestHTML("405 error", "Bad POST request (error in years)");
        return (0);
    }
    if (atof(data) < 0.0 || !isdigit(data[0]) || strlen(data) > 15)
    {
        _server_generateBadRequestHTML("343 error", "Bad POST request - error in \"years\" field.");
        return (0);
    }
    director_setYears(directorObj, atof(data));
    // Check "birthdate" field.
    data = (char *)http_request_getArg(request, "birthdate");
    if (NULL == data)
    {
        _server_generateBadRequestHTML("405 error", "Bad POST request (error in birthdate)");
        return (0);
    }
    int y = 0, m = 0, d = 0;
    int returnCode = sscanf(data, "%d-%d-%d", &y, &m, &d);
    if (!returnCode)
    {
        _server_generateBadRequestHTML("343 error", "Bad POST request - error in \"birthdate\" field.");
        return (0);
    }
    if (y < 1970 || y > 2500 || m < 0 || m > 12 || d < 0 || d > 31)
    {
        _server_generateBadRequestHTML("343 error", "Bad POST request - error in \"birthdate\" field. - are you kidding?");
        return (0);
    }
    director_setBirthDate(directorObj, data);
    // At the end - return true - that means, everything was cool!
    return (1);
}

//--------------------------------------->>> Public methods <<<---------------------------------------

void server_analyzeGETRequest(http_request_t * request, socket_t * client)
{
    if (!strcmp(request->uri, "/home") || !strcmp(request->uri, "/"))
    {
        http_sendHtml(client, "src/html/homepage.html");
    }
    else if (!strcmp(request->uri, "/help") || !strcmp(request->uri, "/home/help"))
    {
        http_sendHtml(client, "src/html/htmlhelp.html");
    }
    else if (!strcmp(request->uri, "/directors"))
    {
        xmlModule_prepHtmlAllDirectors("src/data/directors.xml");
        http_sendHtml(client, "src/html/directors.html");
    }
    else if (!strcmp(request->uri, "/new-director"))
    {
        http_sendHtml(client, "src/html/newdirector.html");
    }
    else if (!strcmp(request->uri, "/api") || !strcmp(request->uri, "/api/help"))
    {
        http_sendHtml(client, "src/html/apihelp.html");
    }
    else if (!strcmp(request->uri, "/api/directors"))
    {
        http_sendXML(client, "src/data/directors.xml");
    }
    else if (!strcmp(request->uri, "/api/directors/about"))
    {
        xmlModule_getXMLInfo("src/data/directors.xml", "src/data/dirsAbout.xml");
        http_sendXML(client, "src/data/dirsAbout.xml");
    }
    else if (strstr(request->uri, "/api/directors/"))
    {
        int id = 0;
        int checkCode = sscanf(request->uri, "/api/directors/%d", &id);
        if (checkCode != 0 && id > 0)
        {
            int isFound = xmlModule_fillSingleDirector(id, "src/data/directors.xml");
            if (isFound == 1)
            {
                puts("Director found!");
                http_sendXML(client, "src/data/singleDirector.xml");
            }
            else
            {
                puts("Sending 404 page...");
                http_sendHtml(client, "src/html/404page.html");
            }
        }
        else
        {
            _server_generateBadRequestHTML("Error 400 page", "Wrong html request");
            http_sendHtml(client, "src/html/badhtmlrequest.html");
        }
    }
    else if (strstr(request->uri, "/directors/"))
    {
        int id = 0;
        int checkCode = sscanf(request->uri, "/directors/%d", &id);
        if (checkCode != 0 && id > 0)
        {
            int isFound = xmlModule_prepHtmlOneDirector(id, "src/data/directors.xml");
            if (isFound)
            {
                puts("Director found!");
                http_sendHtml(client, "src/html/singleDirector.html");
            }
            else
            {
                puts("Director not found - sending 404 page");
                http_sendHtml(client, "src/html/404page.html");
            }
        }
        else
        {
            _server_generateBadRequestHTML("Error 400 page", "Wrong html request");
            http_sendHtml(client, "src/html/badhtmlrequest.html");
        }
    }
    else
    {
        http_sendHtml(client, "src/html/404page.html");
    }
}

void server_analyzePOSTRequest(http_request_t * request, socket_t * client)
{
    if (!strcmp(request->uri, "/new-director"))
    {
        director_t *dirToAdd = director_new_empty();
        int checkCode = _server_checkRequest(request, dirToAdd);
        if (!checkCode)
        {
            http_sendHtml(client, "src/html/badhtmlrequest.html");
            return;
        }
        // Add new investor to .xml file.
        xmlModule_appendDirector(dirToAdd, "src/data/directors.xml");
        // Send html file about all directors.
        xmlModule_prepHtmlAllDirectors("src/data/directors.xml");
        http_sendHtml(client, "src/html/directors.html");
        // Free allocated memory.
        director_delete(dirToAdd);
    }
    else
    {
        http_sendHtml(client, "src/html/404page.html");
    }
}

void server_analyzeDELETERequest(http_request_t * request, socket_t * client)
{
    if (strstr(request->uri, "/api/directors/"))
    {
        int id = 0;
        int checkCode = sscanf(request->uri, "/api/directors/%d", &id);
        if (checkCode != 0 && id > 0)
        {
            xmlModule_deleteDirector(id, "src/data/directors.xml");
            http_sendXML(client, "src/data/directors.xml");
        }
        else
        {
            _server_generateBadRequestHTML("Error 400 page", "Wrong html request");
            http_sendHtml(client, "src/html/badhtmlrequest.html");
        }
    }
    else if (strstr(request->uri, "/directors/"))
    {
        int id = 0;
        int checkCode = sscanf(request->uri, "/directors/%d", &id);
        if (checkCode != 0 && id > 0)
        {
            xmlModule_deleteDirector(id, "src/data/directors.xml");
            http_sendHtml(client, "ALERT: director was deleted!");
        }
        else
        {
            _server_generateBadRequestHTML("Error 400 page", "Wrong html request");
            http_sendHtml(client, "src/html/badhtmlrequest.html");
        }
    }
    else
    {
        http_sendHtml(client, "src/html/404page.html");
    }
}
