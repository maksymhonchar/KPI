#pragma once

#define NO_FLAGS_SET 0
#define PORT 80
#define MAXBUFLEN 20480

int initDLL(WSADATA Data);
SOCKET socket_create();
void socket_connect(SOCKET recvSocket, SOCKADDR_IN recvSockAddr);
void socket_sendRequest(const char * host_name, SOCKET recvSocket);
void socket_receiveInfo(SOCKET recvSocket, char * maxBuff);
void getSecret(char * maxBuff, char * host_name, SOCKET recvSocket);
void longestWord(char * maxBuff, char buff[]);
void socket_sendPost(SOCKET recvSocket, char * host_name, char *avg);
