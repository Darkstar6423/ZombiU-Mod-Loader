#pragma once
#include "ZombiStructs.h"
#include "windows.h"
#include "utility.h"



static __declspec(naked) void zombieDamageFunction()
{

	__asm
	{
		cmp[ECX + 0x3C],01
		je endoffunction
		mov dword ptr zombieDamageCallbackZombie, ECX
		mov dword ptr zombieDamageCallbackInflictor, EDI
		mov dword ptr zombieDamageCallbackEBP, ebp
		mov dword ptr zombieDamageCallbackEDX, EDX
		call zombieDamageCallbackAddress
		//set variables back
		mov ebp, zombieDamageCallbackEBP
		mov edx, zombieDamageCallbackEDX
		endoffunction:
		subss xmm0, [ebp-0x08]
		jmp [zombieDamageJMPBack]
	}


}



void zombieDamageCallback();
bool createZombieDamageHook();
extern c_zombieDamageFunction ZDamagefunc;