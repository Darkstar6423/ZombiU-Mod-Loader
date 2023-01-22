#include "ConsoleGUI.h"
#include "pch.h"
#include <iostream>



LPDIRECT3DVERTEXBUFFER9 v_buffer = NULL;

bool drawConsole = false;
bool isDrawingConsole = false;
char consoleBuffer[256];


void initConsole();
void DrawConsoleGUI(IDirect3DDevice9* pDevice);

LPD3DXFONT ConsoleFont;

HWND Window = NULL;



void DrawConsoleGUI(IDirect3DDevice9* pDevice)
{
    if (drawConsole)
    {
        isDrawingConsole = true;
    }
    else
    {
        isDrawingConsole = false;
    }

    if (!isDrawingConsole)
        return;


    RECT WinRect;
    GetClientRect(Window, &WinRect);
    //Console Log Box
    

    
    //Console Text Box
    D3DRECT ConsoleTextBox = { 0, 0, WinRect.right, WinRect.bottom - (WinRect.bottom-20) };
    pDevice->Clear(1, &ConsoleTextBox, D3DCLEAR_TARGET, D3DCOLOR_ARGB(255, 82, 79, 79), 0.0f, 0);

    if (!ConsoleFont)
        D3DXCreateFont(pDevice, 20, 0, FW_BOLD, 1, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial", &ConsoleFont);

    RECT ConsoleTextRectangle;
    SetRect(&ConsoleTextRectangle, 5, ConsoleTextBox.y1/2, 0, 0);

    ConsoleFont->DrawText(NULL, consoleBuffer, -1, &ConsoleTextRectangle, DT_NOCLIP | DT_LEFT, D3DCOLOR_ARGB(255, 255, 255, 255));



}


void initConsole()
{
    Window = GetForegroundWindow();
    consoleBuffer[0] = '>';
    consoleBuffer[1] = ' ';

    while (gDevice == NULL)
        Sleep(1);

    



}