#include "ConsoleGUI.h"
#include <d2d1.h>
#include "pch.h"

struct CUSTOMVERTEX { FLOAT X, Y, Z, RHW; DWORD COLOR; };
#define CUSTOMFVF (D3DFVF_XYZRHW | D3DFVF_DIFFUSE)


CUSTOMVERTEX vertices[] =
{
{ 0.0f, 0.0f, 0.5f, 1.0f, D3DCOLOR_XRGB(255, 0, 0) },
{ 1024.0f, 0.0f, 0.5f, 1.0f, D3DCOLOR_XRGB(0, 0, 255) },
{ 1024.0f, 400.0f, 0.5f, 1.0f, D3DCOLOR_XRGB(255, 0, 0) },
{ 0.0f, 0.0f, 0.5f, 1.0f, D3DCOLOR_XRGB(255, 0, 0) },
{ 1024.0f, 400.0f, 0.5f, 1.0f, D3DCOLOR_XRGB(255, 0, 0) },
{ 0.0f, 400.0f, 0.5f, 1.0f, D3DCOLOR_XRGB(255, 0, 0) }
};




void DrawConsoleGUI(IDirect3DDevice9* pDevice);
LPD3DXFONT ConsoleFont;
bool drawConsole = false;
bool isDrawingConsole = false;
HWND Window = GetForegroundWindow();



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




    if (!ConsoleFont)
        D3DXCreateFont(pDevice, 16, 0, FW_BOLD, 1, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial", &ConsoleFont);
    //fonts->DrawText(NULL, "Zloader Version 0.1", -1, &textRectangle, DT_NOCLIP | DT_LEFT, D3DCOLOR_ARGB(100, 113, 113, 113));

}