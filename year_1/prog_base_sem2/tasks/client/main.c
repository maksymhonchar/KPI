#include <stdio.h>
#include <stdlib.h>
#include <WinSock2.h>
#include <windows.h>
#include <conio.h>

#include "client.h"

int main(void)
{
    WSADATA Data;
    SOCKADDR_IN recvSockAddr;
    SOCKET recvSocket;
    struct hostent * remoteHost;
    char * ip;
    const char * host_name = "pb-homework.appspot.com";
    char maxBuff[MAXBUFLEN] = "\0";

    int status = initDLL(Data);
    if(status == 1)
    {
        fprintf(stderr, "Cannot initialize dll - WSAStartup failed.");
        exit(1);
    }
    remoteHost = gethostbyname(host_name);
    ip = inet_ntoa(*(struct in_addr *)*remoteHost->h_addr_list);
    memset(&recvSockAddr, 0, sizeof(recvSockAddr));
    recvSockAddr.sin_port=htons(PORT);
    recvSockAddr.sin_family=AF_INET;
    recvSockAddr.sin_addr.s_addr= inet_addr(ip);

    recvSocket = socket_create();
    socket_connect(recvSocket, recvSockAddr);
    socket_sendRequest(host_name, recvSocket);
    socket_receiveInfo(recvSocket, maxBuff);

    getSecret(maxBuff, host_name, recvSocket);
    socket_receiveInfo(recvSocket, maxBuff);

    printf("******************************************\n"
           "Answer to request from R.A. server\n"
           "%s\n"
           "******************************************\n",
           maxBuff);

    // Find the longest word here!
    char longest[80] = "\0";
    longestWord(maxBuff, longest);
    printf("\n\n******************************************\n"
           "Longest word was: [%s]\n"
           "******************************************\n",
           longest);
    socket_sendPost(recvSocket, host_name, longest);

    socket_receiveInfo(recvSocket, maxBuff);
    printf("\n\n******************************************\n"
           "Answer from R.A. server to my POST:\n"
           "%s\n"
           "******************************************\n",
           maxBuff);

    // Close all sockets.
    closesocket(recvSocket);
    // Free memory associated with sockets.
    WSACleanup();
    return 0;
}
