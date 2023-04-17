#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <filesystem>
#include <iostream>
#include <tchar.h>
#include "Injector.h"
#include "gui.h"
#include "config.h"


namespace fs = std::filesystem;




CONFIG config;
GUI gui;

HINSTANCE hInst;

int WINAPI WinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR     lpCmdLine,
    _In_ int       nCmdShow
)
{



    // Store instance handle in our global variable
    hInst = hInstance;

    // The parameters to CreateWindowEx explained:
    // WS_EX_OVERLAPPEDWINDOW : An optional extended window style.
    // szWindowClass: the name of the application
    // szTitle: the text that appears in the title bar
    // WS_OVERLAPPEDWINDOW: the type of window to create
    // CW_USEDEFAULT, CW_USEDEFAULT: initial position (x, y)
    // 500, 100: initial size (width, length)
    // NULL: the parent of this window
    // NULL: this application does not have a menu bar
    // hInstance: the first parameter from WinMain
    // NULL: not used in this application


    config = CONFIG::CONFIG();

    gui = GUI::GUI(hInstance, hPrevInstance, lpCmdLine, nCmdShow);


    //Elements
    gui.createLaunchButton();
    gui.createListBox();


    
   
    
    
    if (!gui.window)
    {
        MessageBox(NULL,
            _T("Call to CreateWindow failed!"),
            _T("Windows Desktop Guided Tour"),
            NULL);

        return 1;
    }

    // The parameters to ShowWindow explained:
    // hWnd: the value returned from CreateWindow
    // nCmdShow: the fourth parameter from WinMain
    ShowWindow(gui.window,
        nCmdShow);
    UpdateWindow(gui.window);
    // Main message loop:
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}



LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC hdc;
    std::string modpath = "mods/";
    HWND modList;
    int pos;
    switch (message)
    {
    case WM_INITDIALOG:
        
        

        break;
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);

        TextOut(hdc, 800, 300, L"Mod Content", 11);

        EndPaint(hWnd, &ps);
        break;

    case WM_DESTROY:
        config.saveSettings();
        PostQuitMessage(0);
        break;

    case WM_COMMAND:



        if (((HWND)lParam) && (HIWORD(wParam) == BN_CLICKED)) 
        {
            int button;
            button = LOWORD(wParam);
            switch (button)
            {
            case LAUNCH_BUTTON:
                config.saveSettings();
                CloseWindow(hWnd);
                inject();
                PostQuitMessage(0);
                break;
            
            default:
                break;
            }
        }

        if (((HWND)lParam) && (HIWORD(wParam) == LBN_SELCHANGE))
        {
            int listbox;
            listbox = LOWORD(wParam);
            switch (listbox)
            {
            case MOD_LISTBOX:
                //selectedMod

                int lbItem = (int)SendMessage(gui.modSelection, LB_GETCURSEL, 0, 0);
                selectedMod = gui.mods[(int)SendMessage(gui.modSelection, LB_GETITEMDATA, lbItem, 0)];

                config.settings["selectedMod"] = selectedMod;

                
                break;
            }
        }



        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
        break;
    }

    return 0;
}