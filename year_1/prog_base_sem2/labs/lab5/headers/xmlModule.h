#pragma once

#define SINGLEDIR_PATH "src/data/singleDirector.xml"

#include "../headers/director.h"
#include "../headers/list.h"

// Parsing methods.
void xmlModule_parseDirectorSet(director_t **directorSet, const char *xmlFilePath);
int xmlModule_countDirectors(const char *xmlFilePath);

// Methods to prepare html or xml files.
void xmlModule_getXMLInfo(const char *from_xmlFilePath, const char *to_xmlFilePath);
int xmlModule_fillSingleDirector(int id, const char *xmlFilePath);
void xmlModule_prepHtmlAllDirectors(const char *xmlFilePath);
int xmlModule_prepHtmlOneDirector(int id, const char *xmlFilePath);

// Deletion and adding to .xml file methods.
void xmlModule_appendDirector(director_t *dirToAdd, const char *xmlFilePath);
void xmlModule_deleteDirector(int id, const char *xmlFilePath);
void xmlModule_listToXML(list_t *listObj, const char *xmlFilePath);
