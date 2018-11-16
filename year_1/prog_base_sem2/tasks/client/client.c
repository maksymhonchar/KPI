#include <stdio.h>
#include <stdlib.h>
#include <WinSock2.h>
#include <windows.h>
#include <string.h>

#include "client.h"

int initDLL(WSADATA Data)
{
    int status = WSAStartup(MAKEWORD(2, 2), &Data);
    if (status != 0)
    {
        return (1);
    }
    return (status);
}

SOCKET socket_create()
{
    SOCKET recvSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (recvSocket == INVALID_SOCKET)
    {
        fprintf(stderr, "Socket creation failed.");
        WSACleanup();
        return (0);
    }
    return (recvSocket);
}

void socket_connect(SOCKET recvSocket, SOCKADDR_IN recvSockAddr)
{
    if (connect(recvSocket, (SOCKADDR*)&recvSockAddr, sizeof(SOCKADDR_IN)) == SOCKET_ERROR)
    {
        fprintf(stderr, "Socket connection failed.");
        closesocket(recvSocket);
        WSACleanup();
    }
}

void socket_sendRequest(const char * host_name, SOCKET recvSocket)
{
    char request[200];
    sprintf(request, "GET /var/4 HTTP/1.1\r\nHost:%s\r\n\r\n", host_name);
    send(recvSocket, request, strlen(request), 0);
}

void socket_receiveInfo(SOCKET recvSocket, char * maxBuff)
{
    int status;
    int numrcv = recv(recvSocket, maxBuff, MAXBUFLEN, NO_FLAGS_SET);
    if (numrcv == SOCKET_ERROR)
    {
        fprintf(stderr, "Socket failed receiving info.");
        status = closesocket(recvSocket);
        if (status == SOCKET_ERROR)
        {
            fprintf(stderr, "Socket closing failed.");
        }
        status = WSACleanup();
        if (status == SOCKET_ERROR)
        {
            fprintf(stderr, "WSACleanup failed.");
        }
    }
}

void getSecret(char * maxBuff, char * host_name, SOCKET recvSocket)
{
    char request[200];
    char * secret;
    secret = strstr(maxBuff, "secret");
    sprintf(request, "GET /var/4?%s HTTP/1.1\r\nHost:%s\r\n\r\n", secret, host_name);
    send(recvSocket, request, strlen(request), 0);
}

void longestWord(char * maxBuff, char buff[])
{
    char * smallBuff;
    char * token;
    smallBuff = strstr(maxBuff, "Content-Length:");
    token = strtok(smallBuff, "\n");
    token = strtok(NULL, "\n");
    token = strtok(NULL, "\n");
    token = strtok(token, " ");
    strcpy(buff, token);
    while(token != NULL)
    {
        token = strtok(NULL, " ");
        if(NULL == token)
            break;
        if(strlen(buff) < strlen(token))
        {
            strcpy(buff, token);
        }
    }
}

void socket_sendPost(SOCKET recvSocket, char * host_name, char *avg)
{
    char result[30];
    char request[200];
    sprintf(result, "result=%s", avg);
    sprintf(request, "POST /var/4 HTTP/1.1\r\nHost: %s\r\nContent-length: %d\r\n\r\n%s\r\n", host_name, strlen(result), result);
    send(recvSocket, request, strlen(request), 0);
}
