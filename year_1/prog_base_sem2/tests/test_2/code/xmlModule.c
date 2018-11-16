#include <stdlib.h>
#include <stdio.h>
#include <strings.h>

#include <libxml/tree.h>
#include "../headers/director.h"
#include "../headers/xmlModule.h"

//----------------------------------->>> Private methods <<<-----------------------------------

static void xmlModule_DirectorFromXML(director_t *curDirector, xmlNode *curNode)
{
    char *data;

    // Get "name" string attribute
    data = (char *) xmlGetProp(curNode, (const xmlChar *)"Name");
    director_setName(curDirector, data);
    data = (char *) xmlGetProp(curNode, (const xmlChar *)"Surname");
    director_setSurname(curDirector, data);
    for (curNode = curNode->children; curNode != NULL; curNode = curNode->next)
    {
        // Get "id" field.
        if (!xmlStrcmp(curNode->name, (const xmlChar *)"Id"))
        {
            data = (char *)xmlNodeGetContent(curNode);
            director_setId(curDirector, atoi(data));
            continue;
        }
        // Get "investments" field.
        else if (!xmlStrcmp(curNode->name, (const xmlChar *)"Investments"))
        {
            data = (char *)xmlNodeGetContent(curNode);
            director_setInvestments(curDirector, atoi(data));
            continue;
        }
        // Get "Years" field.
        else if (!xmlStrcmp(curNode->name, (const xmlChar *)"Years"))
        {
            data = (char *)xmlNodeGetContent(curNode);
            director_setYears(curDirector, atof(data));
            continue;
        }
        // Get "Birthdate" field.
        else if (!xmlStrcmp(curNode->name, (const xmlChar *)"Birthdate"))
        {
            data = (char *)xmlNodeGetContent(curNode);
            director_setBirthDate(curDirector, data);
            continue;
        }
    }
}

//----------------------------------->>> Public methods <<<-----------------------------------



void xmlModule_parseDirector(director_t **directorSet)
{
    xmlDoc *doc = xmlReadFile(XML_FILE_PATH, "UTF-8", 0);
    if (NULL == doc)
    {
        xmlFreeDoc(doc);
        return;
    }
    xmlNode *xml_root = xmlDocGetRootElement(doc);
    xmlNode *curNode = xml_root->children;
    for (int i = 0; curNode != NULL; curNode = curNode->next)
    {
        if (!xmlStrcmp(curNode->name, (const xmlChar *)"director"))
        {
            xmlModule_DirectorFromXML(directorSet[i++], curNode);
        }
    }
    xmlFreeDoc(doc);
}

int xmlModule_countDirectors()
{
    xmlDoc *doc = xmlReadFile(XML_FILE_PATH, "UTF-8", 0);
    if (NULL == doc)
    {
        xmlFreeDoc(doc);
        return (-1);
    }
    xmlNode *xml_root = xmlDocGetRootElement(doc);
    xmlNode *curNode = xml_root->children;
    int amountOfDirectors;
    for (amountOfDirectors = 0; curNode != NULL; curNode = curNode->next)
    {
        if (!xmlStrcmp(curNode->name, (const xmlChar *)"director"))
        {
            amountOfDirectors++;
        }
    }
    xmlFreeDoc(doc);
    return (amountOfDirectors);
}

void xmlModule_listToXML(list_t *listObj)
{
    FILE *f = fopen(XML_FILE_PATH, "w");
    xmlDoc * doc = xmlNewDoc((xmlChar *)"1.0");
    xmlNode * rootNode = xmlNewNode(NULL, (xmlChar *)"directors");
    xmlNode * directorNode = NULL;

    for (int i = 0; i < list_getSize(listObj); i++)
    {
        // Buffer to hold integers in string.
        char strBuf[100] = "\0";
        // Create root element.
        xmlDocSetRootElement(doc, rootNode);
        // Current director entity in list.
        director_t *currentDirector = (director_t *) list_getNodeValueByIndex(listObj, i);
        // Create director tag.
        directorNode = xmlNewChild(rootNode, NULL, (xmlChar *)"director", NULL);
        // Fill certain director info.
        sprintf(strBuf, "%i", director_getId(currentDirector));
        xmlNewChild(directorNode, NULL, (xmlChar *)"id", (xmlChar *)strBuf);
        xmlNewChild(directorNode, NULL, (xmlChar *)"name", (xmlChar *)director_getName(currentDirector));
        xmlNewChild(directorNode, NULL, (xmlChar *)"surname", (xmlChar *)director_getSurname(currentDirector));
        xmlNewChild(directorNode, NULL, (xmlChar *)"birthdate", (xmlChar *)director_getBirthDate(currentDirector));
        sprintf(strBuf, "%i", director_getInvestments(currentDirector));
        xmlNewChild(directorNode, NULL, (xmlChar *)"investments", (xmlChar *)strBuf);
        sprintf(strBuf, "%.2f", director_getYears(currentDirector));
        xmlNewChild(directorNode, NULL, (xmlChar *)"years", (xmlChar *)strBuf);
    }
    // Write info to the .xml file.
    xmlBuffer * bufferPtr = xmlBufferCreate();
    xmlNodeDump(bufferPtr, NULL, (xmlNode *)doc, 0, 1);
    printf("%s", (const char *)bufferPtr->content);
    fprintf(f, "%s", (const char *)bufferPtr->content);

    xmlDocSetRootElement(doc, rootNode);

    // Free allocated memory.
    xmlBufferFree(bufferPtr);
    fclose(f);
    xmlFreeDoc(doc);
    xmlCleanupParser();
}

void xmlModule_xmlDatabaseInfo(int amount, char *dbName, char *xmlFilePath)
{
    FILE *f = fopen(xmlFilePath, "w");
    xmlDoc * doc = xmlNewDoc((xmlChar *)"1.0");
    xmlNode * rootNode = xmlNewNode(NULL, (xmlChar *)"database");

    char strBuf[1000] = "\0";
    xmlDocSetRootElement(doc, rootNode);
    // Fill certain database info.
    xmlNewChild(rootNode, NULL, (xmlChar *)"dbname", (xmlChar *)dbName);
    sprintf(strBuf, "%i", amount);
    xmlNewChild(rootNode, NULL, (xmlChar *)"capacity", (xmlChar *)strBuf);

    // Write info to the .xml file.
    xmlBuffer * bufferPtr = xmlBufferCreate();
    xmlNodeDump(bufferPtr, NULL, (xmlNode *)doc, 0, 1);
    printf("%s", (const char *)bufferPtr->content);
    fprintf(f, "%s", (const char *)bufferPtr->content);

    // Free allocated memory.
    xmlBufferFree(bufferPtr);
    fclose(f);
    xmlFreeDoc(doc);
    xmlCleanupParser();
}
