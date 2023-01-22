#include "DirectXMain.h"
#include "pch.h"




void InitDirectX();

typedef HRESULT(__stdcall* endScene)(IDirect3DDevice9* pDevice);
endScene pEndScene = NULL;
LPD3DXFONT Verfont;
HWND gameWindow;
IDirect3DDevice9* gDevice;

void CleanD3D()
{


    if (gameWindow != NULL && IsIconic(gameWindow))
    {
        Verfont->OnLostDevice();
        if (ConsoleFont != NULL) { ConsoleFont->OnLostDevice(); }
    }
}




void DrawVersionText(IDirect3DDevice9* pDevice)
{
    RECT WinRect;
    HWND window = GetForegroundWindow();
    GetClientRect(window, &WinRect);
    //version Graphic
    int padding = 2;
    int rectx1 = 10, rectx2 = 10, recty1 = WinRect.bottom - 30, recty2 = 10;
    
    if (!Verfont)
        D3DXCreateFont(pDevice, 16, 0, FW_BOLD, 1, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial", &Verfont);
    RECT textRectangle;
    SetRect(&textRectangle, rectx1 + padding, recty1 + padding, rectx2 - padding, recty2 - padding);
    int VersionOpacity = 255;
    if (!drawConsole)
    {
        VersionOpacity = 80;
    }

    Verfont->DrawText(NULL, "Zloader Version 0.1", -1, &textRectangle, DT_NOCLIP | DT_LEFT, D3DCOLOR_ARGB(VersionOpacity, 113, 113, 113)); //draw text;
}




long __stdcall hookedendScene(IDirect3DDevice9* pDevice)
{
    gDevice = pDevice;

    HWND activeWindow = GetForegroundWindow();
    if (IsIconic(gameWindow)) //prevent the device from drawing when the game is minimized
    {
        return pEndScene(pDevice);
    }

    DrawVersionText(pDevice);
    DrawConsoleGUI(pDevice);
    return pEndScene(pDevice);
}



void InitDirectX()
{
    
    while (GetModuleHandle("d3d9.dll") == NULL)
        Sleep(1000);


    
    if (kiero::init(kiero::RenderType::D3D9) == kiero::Status::Success)
    {
        gameWindow = GetForegroundWindow();
        kiero::bind(42, (void**)&pEndScene, hookedendScene);
    }
    initConsole();
}

