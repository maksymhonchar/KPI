#pragma once

#include "../headers/http.h"
#include "../headers/socket.h"
#include "../headers/dbModule.h"

void server_analyzeGETRequest(http_request_t * request, socket_t * client, db_t *dbObj);
void server_analyzePOSTRequest(http_request_t * request, socket_t * client, db_t *dbObj);
void server_analyzeDELETERequest(http_request_t * request, socket_t * client, db_t *dbObj);

void server_updateDirectorsXML(db_t *dbObj);

