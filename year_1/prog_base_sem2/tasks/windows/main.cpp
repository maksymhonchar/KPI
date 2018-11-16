#include <tchar.h>
#include <windows.h>
#include <stdlib.h>
#include <CommCtrl.h>

enum
{
    STATIC1_ID = 1,
    STATIC2_ID,
    STATIC3_ID,
    EDIT1_ID,
    EDIT2_ID,
    EDIT3_ID
};

TCHAR szClassName[ ] = _T("WindowsApp");

// Object to handle all window procedures.
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

HINSTANCE hInst;

// Main function.
int WINAPI WinMain (HINSTANCE hThisInstance, HINSTANCE hPrevInstance, LPSTR lpszArgument, int nCmdShow)
{
    HWND hwnd;
    MSG messages;
    WNDCLASSEX wincl;

    // Set window structure attributes.
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;
    wincl.style = CS_DBLCLKS;
    wincl.cbSize = sizeof (WNDCLASSEX);
    wincl.hIcon = LoadIcon (NULL, IDI_EXCLAMATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_EXCLAMATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;
    wincl.cbClsExtra = 0;
    wincl.cbWndExtra = 0;
    wincl.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);

    // Register the window class.
    if(!RegisterClassEx(&wincl))
    {
        MessageBox(NULL, "Window Registration Failed", "Error", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    // Set window handler settings.
    DWORD windowStyle = (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX);
    hwnd = CreateWindowEx(0, szClassName, _T("Gonchar Maxim - 'windows' task"), windowStyle, CW_USEDEFAULT,CW_USEDEFAULT, 470, 190, HWND_DESKTOP, NULL, hThisInstance, NULL );
    SetWindowLong(hwnd, GWL_STYLE, GetWindowLong(hwnd, GWL_STYLE) & ~WS_MINIMIZEBOX);
    SetWindowLong(hwnd, GWL_STYLE, GetWindowLong(hwnd, GWL_STYLE) & ~WS_MAXIMIZEBOX);
    if(hwnd == NULL)
    {
        MessageBox(NULL, "Window Creation Failed!", "Error!",
                   MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }
    // Show and update a window.
    ShowWindow (hwnd, nCmdShow);
    UpdateWindow(hwnd);

    // Translating and dispatching messages loop.
    while (GetMessage (&messages, NULL, 0, 0))
    {
        TranslateMessage(&messages);
        DispatchMessage(&messages);
    }

    // When PostQuitMessage is executed, exit the program.
    return messages.wParam;
}

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    // Handlers for labels and edit controls.
    static HWND hStatic1, hStatic2, hStatic3, descrStatic;
    static HWND hEdit1, hEdit2, hEdit3;

    // Buffer to handle with edit text.
    char buff[512] = "";

    switch (message)
    {
    case WM_CREATE:
        // Create 3 static and set their text.
        hStatic1 = CreateWindowEx(0, WC_STATIC, "Name", WS_CHILD | WS_VISIBLE | SS_CENTER | SS_SUNKEN, 20, 20, 200, 20, hwnd, (HMENU)STATIC1_ID, hInst, NULL);
        hStatic2 = CreateWindowEx(0, WC_STATIC, "Budget", WS_CHILD | WS_VISIBLE | SS_CENTER | SS_SUNKEN, 20, 50, 200, 20, hwnd, (HMENU)STATIC2_ID, hInst, NULL);
        hStatic3 = CreateWindowEx(0, WC_STATIC, "Description:", WS_CHILD | WS_VISIBLE | SS_CENTER | SS_SUNKEN, 20, 80, 200, 20, hwnd, (HMENU)STATIC3_ID, hInst, NULL);
        // Create 3 edit controls.
        hEdit1 = CreateWindowEx(0, WC_EDIT, "Startup:", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | ES_WANTRETURN | SS_CENTER, 240, 20, 200, 20, hwnd, (HMENU)EDIT1_ID, hInst, NULL);
        hEdit2 = CreateWindowEx(0, WC_EDIT, "Budget:", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | ES_WANTRETURN | SS_CENTER, 240, 50, 200, 20, hwnd, (HMENU)EDIT2_ID, hInst, NULL);
        hEdit3 = CreateWindowEx(0, WC_EDIT, "Short description:", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | ES_WANTRETURN | SS_CENTER, 240, 80, 200, 20, hwnd, (HMENU)EDIT3_ID, hInst, NULL);
        // Description static - just for fun.
        descrStatic = CreateWindowEx(0, WC_STATIC, "Startup level 2016", WS_CHILD | WS_VISIBLE | SS_CENTER, 150, 130, 130, 20, hwnd, NULL, hInst, NULL);
        break;
    case WM_COMMAND:
        // If edit1 text was changed.
        if((HIWORD(wParam) == EN_CHANGE) && (LOWORD(wParam) == EDIT1_ID))
        {
            GetWindowText(hEdit1, buff, sizeof(buff));
            SetWindowText(hStatic1, TEXT(buff));
        }
        // If edit2 text was changed.
        else if((HIWORD(wParam) == EN_CHANGE) && (LOWORD(wParam) == EDIT2_ID))
        {
            GetWindowText(hEdit2, buff, sizeof(buff));
            SetWindowText(hStatic2, TEXT(buff));
        }
        // If edit3 text was changed.
        else if((HIWORD(wParam) == EN_CHANGE) && (LOWORD(wParam) == EDIT3_ID))
        {
            GetWindowText(hEdit3, buff, sizeof(buff));
            SetWindowText(hStatic3, TEXT(buff));
        }
        break;
    case WM_CLOSE:
        DestroyWindow(hwnd);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return (0);
}
