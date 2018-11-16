#include <stdio.h>
#include <stdlib.h>

#include "../headers/socket.h"
#include "../headers/http.h"
#include "../headers/server.h"
#include "../headers/list.h"
#include "../headers/dbModule.h"
#include "../headers/xmlModule.h"

#ifndef TRUE
#define TRUE 1
#endif // TRUE

int main()
{
    // Begin work with sockets.
    lib_init();

    // Initialize server socket.
    socket_t *server = socket_new();
    socket_bind(server, 5000);
    socket_listen(server);

    // Initialize database entity.
    db_t *directorsDB = database_new("src/data/Directors.db");

    // Buffer for socket messages.
    char socketBuffer[10000] = "\0";

    while(TRUE)
    {
        server_updateDirectorsXML(directorsDB);

        puts("Waiting for connection...");
        // Get message from server.
        socket_t *client = socket_accept(server);
        socket_read(client, socketBuffer, sizeof(socketBuffer));

        // Parse message from server to structure http_structure_t.
        http_request_t request = http_request_parse(socketBuffer);

        // Print formatted message from server.
        printf("Request method: %s\nRequest uri:%s\n", request.method, request.uri);
        puts("");

        // Invoke certain http request method.
        if (!strcmp(request.method, "GET"))
        {
            server_analyzeGETRequest(&request, client, directorsDB);
        }
        else if (!strcmp(request.method, "DELETE"))
        {
            server_analyzeDELETERequest(&request, client, directorsDB);
        }
        else if (!strcmp(request.method, "POST"))
        {
            server_analyzePOSTRequest(&request, client, directorsDB);
        }
        else
        {
            http_sendHtml(client, "src/html/badhtmlrequest.html");
        }

        socket_free(client);
    }

    // At the end of the program, free allocated memory;
    socket_free(server);
    lib_free();

    return 0;
}
