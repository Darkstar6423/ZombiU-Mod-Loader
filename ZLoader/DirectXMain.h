#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include <Windows.h>
#include <thread>
#include "MinHook.h"
#include "ConsoleGUI.h"

#include "kiero.h"
#pragma comment(lib, "libMinHook.x86.lib")

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")


extern IDirect3DDevice9* gDevice;
extern void InitDirectX();