#pragma once
#include "ZombiStructs.h"
#include "windows.h"
#include "utility.h"



static __declspec(naked) void zombieDamageFunction()
{

	__asm
	{
		cmp[edi + 0x3C], 01
		je endoffunction
		mov dword ptr zombieDamageCallbackZombie, edi
		mov dword ptr zombieDamageCallbackECX, ecx

		call zombieDamageCallbackAddress
		endoffunction :
		movss xmm2, [ecx + 0x0C]
		jmp[zombieDamageJMPBack]
	}


}

void zombieDamageCallback();
bool createZombieDamageHook();
extern c_zombieDamageFunction ZDamagefunc;