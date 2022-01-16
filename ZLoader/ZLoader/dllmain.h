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




//Player Damage Function
DWORD playerDamageJMPBack;//where this jump will return to
DWORD playerDamageCallbackAddress;//the address of our callback
//parameters
DWORD playerDamageCallbackPlayer;
DWORD playerDamageCallbackDamage;
DWORD *playerDamageCallbackEBP;
__declspec(naked) void playerDamageFunctions()
{
	__asm
	{
		//Original Code
		movss[esp], xmm0
		//new code
		mov dword ptr playerDamageCallbackPlayer, ecx
		mov dword ptr playerDamageCallbackDamage, esp
		mov dword ptr playerDamageCallbackEBP, ebp
		call playerDamageCallbackAddress
		//Jump Back
		jmp [playerDamageJMPBack]
	}
}