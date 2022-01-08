#pragma once

#include <iostream>
#include <stdio.h>
#include <d3d9.h>
#include <tlhelp32.h>
#include <windows.h>

HANDLE process_handle;

DWORD rabbidsBaseAddress;



long getZombiBaseAddress()
{
	return 0x00400000;
};

DWORD playerDamageJMPBack;
DWORD playerDamageCall;
#pragma optimize( "", off )
__declspec(naked) void playerDamageFunctions()
{
	__asm
	{
		mov ecx, eax
		call playerDamageCall
		mov float ptr [ebp+0x0C],00000000
		jmp [playerDamageJMPBack]
	}
}
#pragma optimize( "", on )