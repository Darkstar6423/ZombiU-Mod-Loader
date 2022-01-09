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

DWORD playerDamageJMPBack;//where this jump will return to
DWORD playerDamageCall; //exists to maintain the original code
DWORD playerDamageCallback;//the address of our callback
DWORD playerDamageCallbackPlayer;
#pragma optimize( "", off )
__declspec(naked) void playerDamageFunctions()
{
	__asm
	{
		mov ecx, eax
		call playerDamageCall
		mov dword ptr playerDamageCallbackPlayer, ebp
		call playerDamageCallback
		jmp [playerDamageJMPBack]
	}
}
#pragma optimize( "", on )