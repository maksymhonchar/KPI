#include <windows.h>
#include <stdlib.h>
#include <strings.h>
#include <CommCtrl.h>

const char g_szClassName[] = "myWindowClass";
static char buf[1000];
static char bufReversed[1000];

enum
{
    EDIT_ID = 1,
    BUTTON_ID_QUIT = 2,
    BUTTON_ID_SET = 3,
    BUTTON_ID_REVERSE = 4,
    LABEL_ID = 5,
    BUTTON_ID_CLEAR = 6
};

// Main window procedure
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK ButtonProc (HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);
LRESULT CALLBACK ButtonProc_reverse (HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);

HINSTANCE hInst;
WNDPROC OldButtonProc;
WNDPROC OldButtonProc_reverse;

void ReverseString(char * str)
{
    char temp;
    size_t len = strlen(str) - 1;
    size_t i;
    size_t k = len;
    for(i = 0; i < len; i++)
    {
        temp = str[k];
        str[k] = str[i];
        str[i] = temp;
        k--;
        if(k == (len / 2))
        {
            break;
        }
    }
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    WNDCLASSEX wc;
    HWND hwnd;
    MSG Msg;
    hInst = hInstance;
    // Set settings for window class & register it.
    wc.cbSize        = sizeof(WNDCLASSEX);
    wc.style         = 0;
    wc.lpfnWndProc   = WndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = hInstance;
    wc.hIcon         = LoadIcon(NULL, IDI_ASTERISK);
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wc.lpszMenuName  = NULL;
    wc.lpszClassName = g_szClassName;
    wc.hIconSm       = LoadIcon(NULL, IDI_ASTERISK);
    if(!RegisterClassEx(&wc))
    {
        MessageBox(NULL, "Window Registration Failed", "Error",
                   MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }
    // Create the window.
    hwnd = CreateWindowEx(
               WS_EX_CLIENTEDGE,
               g_szClassName,
               "OP hometask - Max Gonchar",
               WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX,
               CW_USEDEFAULT,
               CW_USEDEFAULT,
               340,
               220,
               NULL,
               NULL,
               hInstance,
               NULL);
    // Disable minimize button and maximize button.
    SetWindowLong(hwnd, GWL_STYLE, GetWindowLong(hwnd, GWL_STYLE) & ~WS_MINIMIZEBOX);
    SetWindowLong(hwnd, GWL_STYLE, GetWindowLong(hwnd, GWL_STYLE) & ~WS_MAXIMIZEBOX);
    if(hwnd == NULL)
    {
        MessageBox(NULL, "Window Creation Failed!", "Error!",
                   MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }
    // Show & update main window.
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);
    // Translating & dispatching messages loop.
    while(GetMessage(&Msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }
    // End of the program.
    return (int) Msg.wParam;
}

// Main window procedure.
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    static HWND hEdit, hLabel, hButton_Set, hButton_Reverse;

    switch(msg)
    {
    case WM_CREATE:
        //TODO: label - enable WS_VSCROLL parameter + ES_AUTOVSCROLL WS_VSCROLL
        hLabel = CreateWindowEx(0, WC_STATIC, "Label", WS_CHILD | WS_VISIBLE | SS_CENTER, 200, 10, 110, 115, hwnd, (HMENU)LABEL_ID, hInst, NULL);
        SetWindowText(hLabel, "Your text will appear here!");
        hEdit = CreateWindowEx(0, WC_EDIT, "", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | ES_WANTRETURN, 20, 10, 160, 115, hwnd, (HMENU)EDIT_ID, hInst, NULL);
        hButton_Set = CreateWindowEx(0, WC_BUTTON, "Set", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 20, 140, 80, 30, hwnd, (HMENU)BUTTON_ID_SET, hInst, NULL);
        OldButtonProc = (WNDPROC) SetWindowLong (hButton_Set, GWL_WNDPROC, (LONG) ButtonProc);
        CreateWindowEx(0, WC_BUTTON, "Exit", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,  200, 140, 110, 30, hwnd, (HMENU)BUTTON_ID_QUIT, hInst, NULL);
        hButton_Reverse = CreateWindowEx(0, WC_BUTTON, "Reverse", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 110, 140, 80, 30, hwnd, (HMENU)BUTTON_ID_REVERSE, hInst, NULL);
        OldButtonProc_reverse = (WNDPROC) SetWindowLong (hButton_Reverse, GWL_WNDPROC, (LONG) ButtonProc_reverse);
        CreateWindowEx(0, WC_BUTTON, "X", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,  180, 10, 20, 115, hwnd, (HMENU)BUTTON_ID_CLEAR, hInst, NULL);
        break;
    case WM_COMMAND:
        if((HIWORD(wParam) == EN_CHANGE) && (LOWORD(wParam) == EDIT_ID))
        {
            GetWindowText(hEdit, buf, sizeof(buf));
        }
        if(LOWORD(wParam) == BUTTON_ID_QUIT)
        {
            PostQuitMessage(WM_QUIT);
        }
        if(LOWORD(wParam) == BUTTON_ID_CLEAR)
        {
           SetWindowText(hEdit, TEXT(""));
        }

        break;
    case WM_CLOSE:
        DestroyWindow(hwnd);
        break;
    case WM_DESTROY:
        PostQuitMessage(WM_QUIT);
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

LRESULT CALLBACK ButtonProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
    HWND parent = GetParent(hwnd);
    HWND hLabel = GetDlgItem(parent, LABEL_ID);
    switch(msg)
    {
    case WM_LBUTTONDOWN:
        SetWindowText(hLabel, TEXT(buf));
        break;
    }
    return CallWindowProc(OldButtonProc, hwnd, msg, wp, lp);
}

LRESULT CALLBACK ButtonProc_reverse (HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
    HWND parent = GetParent(hwnd);
    HWND hLabel = GetDlgItem(parent, LABEL_ID);
    switch(msg)
    {
    case WM_LBUTTONDOWN:
        strcpy(bufReversed, buf);
        ReverseString(bufReversed);
        SetWindowText(hLabel, TEXT(bufReversed));
        break;
    }
    return CallWindowProc(OldButtonProc, hwnd, msg, wp, lp);
}
