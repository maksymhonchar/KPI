#include <stdlib.h>
#include <stdio.h>
#include <strings.h>

#include "../headers/director.h"
#include "../headers/xmlModule.h"

#include <libxml/tree.h>
#include <libxml/parser.h>
#include <libxml/xmlmemory.h>
#include <libxml/xpath.h>

//----------------------------------->>> Private methods <<<-----------------------------------

static void xmlModule_DirectorFromXML(director_t *curDirector, xmlNode *curNode)
{
    char *data;
    // Get "name" string attribute
    data = (char *) xmlGetProp(curNode, (const xmlChar *)"name");
    director_setName(curDirector, data);
    data = (char *) xmlGetProp(curNode, (const xmlChar *)"surname");
    director_setSurname(curDirector, data);
    for (curNode = curNode->children; curNode != NULL; curNode = curNode->next)
    {
        // Get "id" integer field.
        if (!xmlStrcmp(curNode->name, (const xmlChar *)"id"))
        {
            data = (char *)xmlNodeGetContent(curNode);
            director_setId(curDirector, atoi(data));
            continue;
        }
        // Get "investments" integer field.
        else if (!xmlStrcmp(curNode->name, (const xmlChar *)"investments"))
        {
            data = (char *)xmlNodeGetContent(curNode);
            director_setInvestments(curDirector, atoi(data));
            continue;
        }
        // Get "Years" real field.
        else if (!xmlStrcmp(curNode->name, (const xmlChar *)"years"))
        {
            data = (char *)xmlNodeGetContent(curNode);
            director_setYears(curDirector, atof(data));
            continue;
        }
        // Get "Birthdate" string field.
        else if (!xmlStrcmp(curNode->name, (const xmlChar *)"birthdate"))
        {
            data = (char *)xmlNodeGetContent(curNode);
            director_setBirthDate(curDirector, data);
            continue;
        }
    }
}

//----------------------------------->>> Public methods <<<-----------------------------------

void xmlModule_parseDirectorSet(director_t **directorSet, const char *xmlFilePath)
{
    xmlDoc *doc = xmlReadFile(xmlFilePath, "UTF-8", 0);
    if (NULL == doc)
    {
        xmlFreeDoc(doc);
        fprintf(stderr, "ERROR: in xmlModule_parseDirector\n");
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

int xmlModule_countDirectors(const char *xmlFilePath)
{
    xmlDoc *doc = xmlReadFile(xmlFilePath, "UTF-8", 0);
    if (NULL == doc)
    {
        xmlFreeDoc(doc);
        fprintf(stderr, "ERROR: in xmlModule_countDirectors\n");
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

void xmlModule_getXMLInfo(const char *from_xmlFilePath, const char *to_xmlFilePath)
{
    FILE *f = fopen(to_xmlFilePath, "w");
    xmlDoc * doc = xmlNewDoc((xmlChar *)"1.0");
    xmlNode * rootNode = xmlNewNode(NULL, (xmlChar *)"dirXML");

    char strBuf[1000] = "\0";
    xmlDocSetRootElement(doc, rootNode);
    // Fill certain database info.
    const char *xmlName = "directors";
    xmlNewChild(rootNode, NULL, (xmlChar *)"xmlname", (xmlChar *)xmlName);
    int amount = xmlModule_countDirectors(from_xmlFilePath);
    sprintf(strBuf, "%i", amount);
    xmlNewChild(rootNode, NULL, (xmlChar *)"capacity", (xmlChar *)strBuf);

    // Write info to the .xml file.
    xmlBuffer * bufferPtr = xmlBufferCreate();
    xmlNodeDump(bufferPtr, NULL, (xmlNode *)doc, 0, 1);
    fprintf(f, "%s", (const char *)bufferPtr->content);

    // Free allocated memory.
    xmlBufferFree(bufferPtr);
    fclose(f);
    xmlFreeDoc(doc);
    xmlCleanupParser();
}

int xmlModule_fillSingleDirector(int id, const char *xmlFilePath)
{
    // Objects to go through big XML file.
    xmlDoc *doc = xmlReadFile(xmlFilePath, "UTF-8", 0);
    if (NULL == doc)
    {
        xmlFreeDoc(doc);
        fprintf(stderr, "ERROR: in xmlModule_fillSingleDirector\n");
        return 0;
    }
    xmlNode *xml_root = xmlDocGetRootElement(doc);
    xmlNode *curNode = xml_root->children;
    char *data = NULL;

    // Objects to write a new XML file.
    FILE *f = fopen(SINGLEDIR_PATH, "w");
    int flag = 0;
    director_t *singleDirector = director_new_empty();
    xmlDoc *SD_doc = xmlNewDoc((xmlChar *)"1.0");
    xmlNode *SD_rootNode = xmlNewNode(NULL, (xmlChar *)"director");

    // Go through big XML file and find certain Id!
    for (; curNode != NULL; curNode = curNode->next)
    {
        if (!xmlStrcmp(curNode->name, (const xmlChar *)"director"))
        {
            for (xmlNode *directorCurNode = curNode->children; directorCurNode != NULL; directorCurNode = directorCurNode->next)
            {
                if (!xmlStrcmp(directorCurNode->name, (xmlChar *)"id"))
                {
                    data = (char *)xmlNodeGetContent(directorCurNode);
                    if (id == atoi(data))
                    {
                        flag = 1;
                        break;
                    }
                }
            }
            if (flag)
            {
                xmlModule_DirectorFromXML(singleDirector, curNode);
                break;
            }
        }
    }
    if (!flag)
    {
        printf("Didn`t found a director with id %d\n", id);
        xmlFreeDoc(doc);
        xmlFreeDoc(SD_doc);
        xmlCleanupParser();
        fclose(f);
        director_delete(singleDirector);
        return (0);
    }

    // Fill .xml object.
    char strBuf[1000] = "\0";
    xmlDocSetRootElement(SD_doc, SD_rootNode);
    xmlNewProp(SD_rootNode, (xmlChar *)"name", (xmlChar *)director_getName(singleDirector));
    xmlNewProp(SD_rootNode, (xmlChar *)"surname", (xmlChar *)director_getSurname(singleDirector));
    sprintf(strBuf, "%i", director_getId(singleDirector));
    xmlNewChild(SD_rootNode, NULL, (xmlChar *)"id", (xmlChar *)strBuf);
    sprintf(strBuf, "%i", director_getInvestments(singleDirector));
    xmlNewChild(SD_rootNode, NULL, (xmlChar *)"investments", (xmlChar *)strBuf);
    sprintf(strBuf, "%.2f", director_getYears(singleDirector));
    xmlNewChild(SD_rootNode, NULL, (xmlChar *)"years", (xmlChar *)strBuf);
    xmlNewChild(SD_rootNode, NULL, (xmlChar *)"birthdate", (xmlChar *)director_getBirthDate(singleDirector));

    // Write info to the .xml file.
    xmlBuffer *bufferPtr = xmlBufferCreate();
    xmlNodeDump(bufferPtr, NULL, (xmlNode *)SD_doc, 0, 1);
    fprintf(f, "%s", (const char *)bufferPtr->content);

    // Close stream and free allocated memory.
    xmlBufferFree(bufferPtr);
    xmlFreeDoc(doc);
    xmlFreeDoc(SD_doc);
    xmlCleanupParser();
    fclose(f);
    director_delete(singleDirector);
    return (1);
}

void xmlModule_prepHtmlAllDirectors(const char *xmlFilePath)
{
    char htmlBuf[10000] = "\0";
    char directorURL[1000] = "\0";
    char directorData[1000] = "\0";
    memset(htmlBuf, 0, 10000);

    // Fill buffer with HTML content.
    sprintf(htmlBuf,
            "<html><head><title> Directors page</title></head>"
            "<body link=\"#808080\"><table border=\"1\" align=\"center\""
            "<tr><td>URL</td>"
            "<td>Name</td>"
            "<td>Surname</td></tr>"
           );

    // Insert all data from xml to html file.
    director_t *directorSet[100];
    for (int i = 0; i < 100; i++)
        directorSet[i] = director_new_empty();
    xmlModule_parseDirectorSet(directorSet, xmlFilePath);
    for (int i = 0; i < 100; i++)
    {
        if (strcmp("Noname", director_getName(directorSet[i])))
        {
            sprintf(directorURL,
                    "<a href=\"http://127.0.0.1:5000/directors/%d\">Director #%d</a>",
                    director_getId(directorSet[i]), i + 1
                   );
            sprintf(directorData,
                    "<tr><td>%s</td>"
                    "<td>%s</td>"
                    "<td>%s</td></tr>",
                    directorURL,
                    director_getName(directorSet[i]),
                    director_getSurname(directorSet[i])
                   );
            strcat(htmlBuf, directorData);
        }
    }

    // End filling buffer with HTML content.
    strcat(htmlBuf, "</table>");

    // Add link to "Add new director" page.
    strcat(htmlBuf, "<br /><p align=\"center\">");
    strcat(htmlBuf, "Add new director: <a href=\"http://127.0.0.1:5000/new-director\">link</a>");
    strcat(htmlBuf, "</p></body></html>");

    // Write data to html file.
    FILE *f = fopen("src/html/directors.html", "w");
    fprintf(f, "%s", htmlBuf);
    fclose(f);
}

int xmlModule_prepHtmlOneDirector(int id, const char *xmlFilePath)
{
    char htmlBuf[10000] = "\0";
    char directorData[1000] = "\0";
    memset(htmlBuf, 0, 10000);

    director_t *directorSet[100];
    for (int i = 0; i < 100; i++)
        directorSet[i] = director_new_empty();
    xmlModule_parseDirectorSet(directorSet, xmlFilePath);

    int flag = 0;
    for (int i = 0; i < 100; i++)
    {
        if (director_getId(directorSet[i]) == id)
        {
            // Fill buffer with HTML content.
            sprintf(htmlBuf,
                    "<html><head><title> Directors page</title></head>"
                    "<body><table border=\"1\""
                    "<tr>"
                    "<td>Id</td>"
                    "<td>Name</td>"
                    "<td>Surname</td>"
                    "<td>Investments</td>"
                    "<td>Years</td>"
                    "<td>Birth date</td>"
                    "</tr>"
                   );
            // Fill data about certain director.
            sprintf(directorData,
                    "<tr>"
                    "<td>%d</td>"
                    "<td>%s</td>"
                    "<td>%s</td>"
                    "<td>%d</td>"
                    "<td>%.2f</td>"
                    "<td>%s</td>"
                    "</tr>",
                    director_getId(directorSet[i]),
                    director_getName(directorSet[i]),
                    director_getSurname(directorSet[i]),
                    director_getInvestments(directorSet[i]),
                    director_getYears(directorSet[i]),
                    director_getBirthDate(directorSet[i])
                   );
            strcat(htmlBuf, directorData);
            strcat(htmlBuf, "</table>");
            flag = 1;
            break;
        }
    }

    if (!flag)
    {
//        char tmpp[1000] = "\0";
//        sprintf(tmpp, "<h4>There is no director with id %d</h4>", id);
//        strcat(htmlBuf, tmpp);
//
//        // End filling buffer with HTML content.
//        strcat(htmlBuf, "</body></html>");
//
//        // Write data to html file.
//        FILE *f = fopen("src/html/singleDirector.html", "w");
//        fprintf(f, "%s", htmlBuf);
//        fclose(f);
        return (0);
    }

    char jsDeleteButton[1000] = "\0";
    sprintf(jsDeleteButton,
            "<a href=\"http://127.0.0.1:5000/directors\" onclick=\"doDelete()\">Delete</a>"
            "<script>"
            "function doDelete() {"
            "var xhttp = new XMLHttpRequest();"
            "xhttp.open(\"DELETE\", \"http://127.0.0.1:5000/directors/%d\", true);"
            "xhttp.send();"
            "alert(\"This director is deleted.\")}"
            "</script>",
            id);
    strcat(htmlBuf, jsDeleteButton);

    // End filling buffer with HTML content.
    strcat(htmlBuf, "</body></html>");

    // Write data to html file.
    FILE *f = fopen("src/html/singleDirector.html", "w");
    fprintf(f, "%s", htmlBuf);
    fclose(f);

    return (1);
}

void xmlModule_appendDirector(director_t *dirToAdd, const char *xmlFilePath)
{
    director_t *directorSet[100];
    for (int i = 0; i < 100; i++)
        directorSet[i] = director_new_empty();
    xmlModule_parseDirectorSet(directorSet, xmlFilePath);
    // Get free index
    int index = 0;
    for (int i = 0; i < 100; i++)
    {
        if (!strcmp(director_getName(directorSet[i]), "Noname") && !strcmp(director_getSurname(directorSet[i]), "Nosurname"))
        {
            index = i;
            break;
        }
    }
    // Fill director by index
    directorSet[index] = dirToAdd;
    // Write everything to .xml file.
    xmlDoc * doc = xmlNewDoc((xmlChar *)"1.0");
    xmlNode * rootNode = xmlNewNode(NULL, (xmlChar *)"directors");
    xmlNode * directorNode = NULL;
    for (int i = 0; i < index + 1; i++)
    {
        char strBuf[100] = "\0";
        // Create root element.
        xmlDocSetRootElement(doc, rootNode);
        // Current director entity in list - directorSet[i]
        // Create director tag.
        directorNode = xmlNewChild(rootNode, NULL, (xmlChar *)"director", NULL);
        // Fill certain director info.
        xmlNewProp(directorNode, (xmlChar *)"name", (xmlChar *)director_getName(directorSet[i]));
        xmlNewProp(directorNode, (xmlChar *)"surname", (xmlChar *)director_getSurname(directorSet[i]));
        sprintf(strBuf, "%i", i + 1);
        xmlNewChild(directorNode, NULL, (xmlChar *)"id", (xmlChar *)strBuf);
        sprintf(strBuf, "%i", director_getInvestments(directorSet[i]));
        xmlNewChild(directorNode, NULL, (xmlChar *)"investments", (xmlChar *)strBuf);
        sprintf(strBuf, "%.2f", director_getYears(directorSet[i]));
        xmlNewChild(directorNode, NULL, (xmlChar *)"years", (xmlChar *)strBuf);
        xmlNewChild(directorNode, NULL, (xmlChar *)"birthdate", (xmlChar *)director_getBirthDate(directorSet[i]));
    }
    // Write info to the .xml file.
    xmlBuffer * bufferPtr = xmlBufferCreate();
    xmlNodeDump(bufferPtr, NULL, (xmlNode *)doc, 0, 1);
    FILE *f = fopen(xmlFilePath, "w");
    fprintf(f, "%s", (const char *)bufferPtr->content);

    // Free allocated memory.
    xmlBufferFree(bufferPtr);
    fclose(f);
    xmlFreeDoc(doc);
    xmlCleanupParser();
}

void xmlModule_deleteDirector(int id, const char *xmlFilePath)
{
    director_t *directorSet[100];
    for (int i = 0; i < 100; i++)
        directorSet[i] = director_new_empty();
    xmlModule_parseDirectorSet(directorSet, xmlFilePath);
    director_t *dirToDelete = director_new_empty();
    director_t *dirToPrint = director_new_empty();
    // Find director, that we want to delete.
    int flag = 0, index = 0;
    for (int i = 0; i < 100; i++)
    {
        if (director_getId(directorSet[i]) == id)
        {
            dirToPrint = directorSet[i];
            flag = 1;
            index = i;
        }
    }
    if (flag)
    {
        puts("Director was deleted! Info about deleted director:");
        director_print(dirToPrint);
        directorSet[index] = dirToDelete;
    }
    else
    {
        printf("Director wasn't deleted. \nThere is no director with id %d", id);
        return;
    }
    // Write everything to .xml file.
    xmlDoc * doc = xmlNewDoc((xmlChar *)"1.0");
    xmlNode * rootNode = xmlNewNode(NULL, (xmlChar *)"directors");
    xmlNode * directorNode = NULL;
    for (int i = 0; i < 100; i++)
    {
        if (!strcmp(director_getName(directorSet[i]), "Noname") || !strcmp(director_getName(directorSet[i]), "Nosurname"))
            continue;
        char strBuf[100] = "\0";
        // Create root element.
        xmlDocSetRootElement(doc, rootNode);
        // Current director entity in list - directorSet[i]
        // Create director tag.
        directorNode = xmlNewChild(rootNode, NULL, (xmlChar *)"director", NULL);
        // Fill certain director info.
        xmlNewProp(directorNode, (xmlChar *)"name", (xmlChar *)director_getName(directorSet[i]));
        xmlNewProp(directorNode, (xmlChar *)"surname", (xmlChar *)director_getSurname(directorSet[i]));
        sprintf(strBuf, "%i", i + 1);
        xmlNewChild(directorNode, NULL, (xmlChar *)"id", (xmlChar *)strBuf);
        sprintf(strBuf, "%i", director_getInvestments(directorSet[i]));
        xmlNewChild(directorNode, NULL, (xmlChar *)"investments", (xmlChar *)strBuf);
        sprintf(strBuf, "%.2f", director_getYears(directorSet[i]));
        xmlNewChild(directorNode, NULL, (xmlChar *)"years", (xmlChar *)strBuf);
        xmlNewChild(directorNode, NULL, (xmlChar *)"birthdate", (xmlChar *)director_getBirthDate(directorSet[i]));
    }
    // Write info to the .xml file.
    xmlBuffer * bufferPtr = xmlBufferCreate();
    xmlNodeDump(bufferPtr, NULL, (xmlNode *)doc, 0, 1);
    FILE *f = fopen(xmlFilePath, "w");
    fprintf(f, "%s", (const char *)bufferPtr->content);

    // Free allocated memory.
    xmlBufferFree(bufferPtr);
    fclose(f);
    xmlFreeDoc(doc);
    xmlCleanupParser();
    free(dirToDelete);
}
