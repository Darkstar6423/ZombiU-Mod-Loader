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
DWORD playerDamageCallbackAddress;//the address of our callback
//parameters
DWORD playerDamageCallbackPlayer;
DWORD playerDamageCallbackDamage;
#pragma optimize( "", off )
__declspec(naked) void playerDamageFunctions()
{
	__asm
	{
		//Original Code
		movss[esp], xmm0
		//new code
		mov dword ptr playerDamageCallbackPlayer, ecx
		mov dword ptr playerDamageCallbackDamage, esp
		call playerDamageCallbackAddress
		//Jump Back
		jmp [playerDamageJMPBack]
	}
}
#pragma optimize( "", on )