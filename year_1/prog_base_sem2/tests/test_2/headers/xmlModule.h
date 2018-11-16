#pragma once

#include "../headers/director.h"
#include "../headers/list.h"

#define XML_FILE_PATH "src/data/Directors.xml"
#define XML_FILE_PATH2 "src/data/Directors2.xml"

void xmlModule_parseDirector(director_t **directorSet);
int xmlModule_countDirectors();
void xmlModule_listToXML(list_t *listObj);
void xmlModule_xmlDatabaseInfo(int amount, char *dbName, char *xmlFilePath);
