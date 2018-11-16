#pragma once

#include "../headers/http.h"
#include "../headers/socket.h"

void server_analyzeGETRequest(http_request_t * request, socket_t * client);
void server_analyzePOSTRequest(http_request_t * request, socket_t * client);
void server_analyzeDELETERequest(http_request_t * request, socket_t * client);
