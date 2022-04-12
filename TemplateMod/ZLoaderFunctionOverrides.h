#pragma once
#include <windows.h>
extern "C" {
	//overrides, if you don't want to use them, delete them
	_declspec(dllexport) bool __cdecl canMinimapAutoPing(DWORD Player);
	_declspec(dllexport) bool __cdecl canMinimapManualPing(DWORD Player);

}