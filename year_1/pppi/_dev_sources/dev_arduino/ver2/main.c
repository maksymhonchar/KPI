#include <stdlib.h>
#include <windows.h>
#include <stdio.h>
#include <strings.h>
#include <conio.h>

int main(void)
{
    HANDLE hComm;
    char lpBuffer[10], ch;
    DWORD dNoOfBytesWritten = 0;
    hComm = CreateFile("\\\\.\\COM3", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
    if(hComm == INVALID_HANDLE_VALUE)
    {
        printf("Error opening serial port");
        CloseHandle(hComm);
        exit(1);
    }
    else
    {
        printf("Opening serial port successful\n");
    }
    while(ch != 'x')
    {
       ch = _getch();
       lpBuffer[0] = ch;
       WriteFile(hComm, lpBuffer, sizeof(lpBuffer), &dNoOfBytesWritten, NULL);
    }
    lpBuffer[0] = '1';
    WriteFile(hComm, lpBuffer, sizeof(lpBuffer), &dNoOfBytesWritten, NULL);
    CloseHandle(hComm);
    return (0);
}
