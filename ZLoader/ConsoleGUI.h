#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include "DirectXMain.h"
#include <Windows.h>
#include <conio.h>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

struct CUSTOMVERTEX { FLOAT X, Y, Z, RHW; DWORD COLOR; };
#define CUSTOMFVF (D3DFVF_XYZRHW | D3DFVF_DIFFUSE)

extern LPD3DXFONT ConsoleFont;
extern bool drawConsole;
extern bool isDrawingConsole;
extern char consoleBuffer[256];



extern void DrawConsoleGUI(IDirect3DDevice9* pDevice);

extern void initConsole();