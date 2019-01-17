#include "winControl.h"
#include "openGLmain.h"
#include "winUI.h"

const int ID_BUTTON_1 = 101;
const int ID_INPUT_1 = 201;
const int ID_INPUT_2 = 202;
const int ID_INPUT_3 = 203;

void openGL_launch(HWND hwnd)
    {
    WINBOOL bSuccess;
    int tempA, tempB, tempC;

    tempA = GetDlgItemInt(hwnd, ID_INPUT_1, &bSuccess, FALSE);
    if (bSuccess == FALSE) {
        MessageBox(hwnd, "Could not get first number!", "Error", MB_OK | MB_ICONERROR);
        //return 0;
    }

    tempB = GetDlgItemInt(hwnd, ID_INPUT_2, &bSuccess, FALSE);
    if (bSuccess == FALSE) {
        MessageBox(hwnd, "Could not get second number!", "Error", MB_OK | MB_ICONERROR);
        //return 0;
    }
    tempC = GetDlgItemInt(hwnd, ID_INPUT_3, &bSuccess, FALSE);
        if (bSuccess == FALSE) {
            MessageBox(hwnd, "Could not get third number!", "Error", MB_OK | MB_ICONERROR);
            //return 0;
        }
        if(bSuccess == true)
        {
            int a = main_ogl(tempA,tempB,tempC);
            char buffer[0xff];
            sprintf(buffer, "Your secret code is: %d\n", a);

            MessageBoxA(NULL, buffer, "Number", MB_OK);
        }


    //return 0;
}

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    static bool online = false;
    switch(msg) {
        case WM_KEYDOWN:
            switch(wParam)
            {
                default:
                    PostQuitMessage(0);
            }
            break;
        case WM_CREATE:
            CreateUI(hwnd, ID_BUTTON_1, ID_INPUT_1, ID_INPUT_2, ID_INPUT_3);
            //main_ogl(800,600,333);
            break;
        case WM_CLOSE:
            DestroyWindow(hwnd);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        case WM_COMMAND:
            switch (wParam) {
                case ID_BUTTON_1:
                    if(!online)
                    {
                        online = true;
                        openGL_launch(hwnd);
                        DestroyWindow(hwnd);
                    }

                    //std::string s = std::to_string(multiply(hwnd));
                    //MessageBox(hwnd,s.c_str(),"XD",MB_ICONEXCLAMATION);
                    break;
            }
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }

    return 0;
}