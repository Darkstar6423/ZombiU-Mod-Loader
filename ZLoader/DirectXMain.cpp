#include "DirectXMain.h"
#include "pch.h"




void InitDirectX();

typedef HRESULT(__stdcall* endScene)(IDirect3DDevice9* pDevice);
endScene pEndScene = NULL;
LPD3DXFONT font;
HWND gameWindow;


void CleanD3D()
{


    if (gameWindow != NULL && IsIconic(gameWindow))
    {
        font->OnLostDevice();
        if (isDrawingConsole == true)
        {
            ConsoleFont->OnLostDevice();
        }
    }
}

void D3DThread()
{
    while (true)
    {
        if (GetKeyState(VK_OEM_3) & 0x80000)
        {
            if (drawConsole)
            {
                drawConsole = false;
                while (GetAsyncKeyState(VK_OEM_3) & 0x80000) {}
            }
            else
            {
                drawConsole = true;
                while (GetAsyncKeyState(VK_OEM_3) & 0x80000) {}
            }
        }

        CleanD3D();
        Sleep(1);
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
    
    if (!font)
        D3DXCreateFont(pDevice, 16, 0, FW_BOLD, 1, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial", &font);
    RECT textRectangle;
    SetRect(&textRectangle, rectx1 + padding, recty1 + padding, rectx2 - padding, recty2 - padding);
    font->DrawText(NULL, "Zloader Version 0.1", -1, &textRectangle, DT_NOCLIP | DT_LEFT, D3DCOLOR_ARGB(100, 113, 113, 113)); //draw text;
}




long __stdcall hookedendScene(IDirect3DDevice9* pDevice)
{
    

    HWND activeWindow = GetForegroundWindow();
    if (IsIconic(gameWindow)) //prevent the device from drawing when the game is minimized
    {
        return pEndScene(pDevice);
    }

    
    DrawVersionText(pDevice);
    //DrawConsoleGUI(pDevice);

    return pEndScene(pDevice);
}



void InitDirectX()
{
    
    while (GetModuleHandle("d3d9.dll") == NULL)
        Sleep(1000);


    
    if (kiero::init(kiero::RenderType::Auto) == kiero::Status::Success)
    {
        gameWindow = GetForegroundWindow();
        kiero::bind(42, (void**)&pEndScene, hookedendScene);
        std::thread messageThread(D3DThread);
        messageThread.detach();
    }

}

