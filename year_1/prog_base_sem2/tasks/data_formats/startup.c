#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include <time.h>

#include <libxml/tree.h>
#include "startupDirector.h"

// private:
static void startup_from_xml(Startup_T *startup, xmlNode * curNode)
{
    char * data;
    for(curNode = curNode->children; curNode != NULL; curNode = curNode->next)
    {
        // Get "name" string field.
        if(!xmlStrcmp(curNode->name, (const xmlChar *)"name"))
        {
            data = (char *)xmlNodeGetContent(curNode);
            strcpy(startup->name, data);
            continue;
        }
        // Get "budget" integer field.
        if(!xmlStrcmp(curNode->name, (const xmlChar *)"budget"))
        {
            data = (char *)xmlNodeGetContent(curNode);
            startup->budget = atoi(data);
            continue;
        }
    }
}

static Director_T *director_from_xml(Director_T *curDirector, xmlNode * curNode)
{
    char *data;
    char *properties;

    // Get "name" string attribute.
    properties = (char *) xmlGetProp(curNode, (const xmlChar *)"name");
    strcpy(curDirector->name, properties);
    // Get "surname" string attribute.
    properties = (char *)xmlGetProp(curNode, (const xmlChar *)"surname");
    strcpy(curDirector->surname, properties);
    for(curNode = curNode->children; curNode != NULL; curNode = curNode->next)
    {
        // Get "nationality" string field.
        if(!xmlStrcmp(curNode->name, (const xmlChar *)"nationality"))
        {
            data = (char *)xmlNodeGetContent(curNode);
            strcpy(curDirector->nationality, data);
            continue;
        }
        // Get "birthdate" UTC ISO 8601 field.
        if(!xmlStrcmp(curNode->name, (const xmlChar *)"birthdate"))
        {
            data = (char *)xmlNodeGetContent(curNode);
            sscanf(data, "%d-%d-%d",
                   &curDirector->birthDate.tm_year,
                   &curDirector->birthDate.tm_mday,
                   &curDirector->birthDate.tm_mon);
            continue;
        }
        // Get "enthusiasm" integer field.
        if(!xmlStrcmp(curNode->name, (const xmlChar *)"enthusiasm"))
        {
            data = (char *)xmlNodeGetContent(curNode);
            curDirector->enthusiasm = atoi(data);
            continue;
        }
        // Get "experience" double field.
        if(!xmlStrcmp(curNode->name, (const xmlChar *)"experience"))
        {
            data = (char *)xmlNodeGetContent(curNode);
            curDirector->experience = atof(data);
            continue;
        }
        // Get "money" integer field.
        if(!xmlStrcmp(curNode->name, (const xmlChar *)"money"))
        {
            data = (char *)xmlNodeGetContent(curNode);
            curDirector->money = atoi(data);
            continue;
        }
        // Get "startup" (string,integer) complex field.
        if(!xmlStrcmp(curNode->name, (xmlChar *)"startup"))
        {
            startup_from_xml(&(curDirector->startup), curNode);
            continue;
        }
    }
    return (curDirector);
}
// public:
Director_T *director_new(void)
{
    Director_T *director = (Director_T *)malloc(sizeof(struct Director_S));
    strcpy(director->name, "");
    strcpy(director->surname, "");
    strcpy(director->nationality, "");
    memset(&director->birthDate, 0, sizeof(director->birthDate));
    director->enthusiasm = 0;
    director->experience = 0;
    director->money = 0;
    strcpy(director->startup.name, "");
    director->startup.budget = 0;
    return (director);
}

void director_delete(Director_T *director)
{
    free(director);
}

void xmlParse(Director_T **directorSet, const char * XMLFileName)
{
    xmlDoc * doc = xmlReadFile(XMLFileName, "UTF-8", 0);
    if(doc == NULL)
    {
        xmlFreeDoc(doc);
        return;
    }
    xmlNode *xml_root = xmlDocGetRootElement(doc);
    xmlNode *curNode;
    int i;
    for(i = 0, curNode = xml_root->children; curNode != NULL; curNode = curNode->next)
    {
        if(!xmlStrcmp(curNode->name, (const xmlChar *)"director"))
        {
            director_from_xml(directorSet[i++], curNode);
        }
    }
    xmlFreeDoc(doc);
}

void printDirectorInfo(Director_T *director)
{
    printf("\t[%s]\n"
           "\t[%s]\n"
           "\t[%s]\n"
           "\t%d-%d-%d\n"
           "\t%i\n"
           "\t%f\n"
           "\t%i\n"
           "\t[%s]\n"
           "\t%i\n\n",
           director->name,
           director->surname,
           director->nationality,
           director->birthDate.tm_year, director->birthDate.tm_mon, director->birthDate.tm_mday,
           director->enthusiasm,
           director->experience,
           director->money,
           director->startup.name,
           director->startup.budget
          );
}
