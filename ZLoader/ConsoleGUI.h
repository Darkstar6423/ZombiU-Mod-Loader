#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include <Windows.h>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

extern LPD3DXFONT ConsoleFont;
extern bool drawConsole;
extern bool isDrawingConsole;

extern void DrawConsoleGUI(IDirect3DDevice9* pDevice);