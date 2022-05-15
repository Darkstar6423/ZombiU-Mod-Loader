#pragma once
#include <windows.h>
#include "GameVariables.h"

extern "C" {
	_declspec(dllexport) DWORD __cdecl GETINVENTORYADDRESS();
	_declspec(dllexport) void __cdecl GIVEITEM(DWORD Item, int amount);


}