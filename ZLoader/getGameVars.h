#pragma once
#include "GameVariables.h"
#include "dllmain.h"

extern DWORD ASMINVJMPBACK;

static __declspec(naked) void ASMGetInventoryAddress()
{
	_asm
	{
		mov PlayerInventory, edi
		cmp byte ptr[edi + 0x00000910], 00
		jmp [ASMINVJMPBACK]
	}
}

void injectInventoryGetter();