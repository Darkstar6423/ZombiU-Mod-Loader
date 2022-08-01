#pragma once
#include <windows.h>
extern "C" {
	//overrides, if you don't want to use them, delete them
	_declspec(dllexport) bool __cdecl canMinimapAutoPing(DWORD Player, bool hasAutoPingUpgrade);
	_declspec(dllexport) bool __cdecl canMinimapManualPing(DWORD Player, bool hasAutoPingUpgrade);
	_declspec(dllexport) bool __cdecl interceptButtonBind(bool isPressed, DWORD ButtonPressed);

}