#pragma once

#include "MinHook.h"
#pragma comment(lib, "libMinHook.x86")

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#pragma comment(lib, "Dinput8.lib")
#pragma comment(lib, "Dxguid.lib")

#include "ConsoleGUI.h"

extern IDirectInput8* pDirectInput;
extern LPDIRECTINPUTDEVICE8 lpdiMouse;
extern LPDIRECTINPUTDEVICE8 lpdiKeyboard;

extern bool DInput8Init(HINSTANCE hmodule);
