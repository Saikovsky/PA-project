#include <windows.h>
#include <sstream>
#include <iostream>
#include <string>
#include "winControl.h"

const char *WindowsClassName = "Class";
const char *WindowsApplicationName = "Project";

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR szCmdLine, int nCmdShow) {

    WNDCLASSEX WindowsClass;
    WindowsClass.cbSize = sizeof(WNDCLASSEX);
    WindowsClass.style = 0;
    WindowsClass.lpfnWndProc = WindowProcedure;
    WindowsClass.cbClsExtra = 0;
    WindowsClass.cbWndExtra = 0;
    WindowsClass.hInstance = hInstance;
    WindowsClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    WindowsClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    WindowsClass.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);
    WindowsClass.lpszMenuName = NULL;
    WindowsClass.lpszClassName = WindowsClassName;
    WindowsClass.hIconSm = LoadIcon(NULL,IDI_APPLICATION);

    if(!RegisterClassEx(&WindowsClass)) {
        MessageBox(NULL, "Error", "Error", 0);
    }

    HWND hwnd;
    hwnd = CreateWindowEx(WS_EX_WINDOWEDGE, WindowsClassName, WindowsApplicationName, WS_OVERLAPPEDWINDOW, 0 , 0, 400, 200, NULL, NULL, hInstance, NULL);

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    MSG Message;
    while(GetMessage(&Message, NULL, 0, 0)){
        if(IsDialogMessage(hwnd,&Message))
        {
            //
        }
        else
        {
            TranslateMessage(&Message);
            DispatchMessage(&Message);
        }
    }

    return 0;
}