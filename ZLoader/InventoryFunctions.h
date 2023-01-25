#pragma once
#include <windows.h>
#include "GameVariables.h"
#include <sstream>
#include "console.h"

extern "C" {
	_declspec(dllexport) DWORD __cdecl GETINVENTORYADDRESS();
	_declspec(dllexport) void __cdecl GIVEITEM(DWORD Item, int amount);


}

extern DWORD ASMINVJMPBACK;
extern DWORD PlayerInventory;
static __declspec(naked) void ASMGetInventoryAddress()
{
	_asm
	{
		mov PlayerInventory, edi
		cmp byte ptr[edi + 0x00000910], 00
		jmp[ASMINVJMPBACK]
	}
}

void injectInventoryGetter();


