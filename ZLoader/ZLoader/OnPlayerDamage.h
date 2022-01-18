#pragma once
#include "ZombiStructs.h"
#include "windows.h"
#include "utility.h"


static __declspec(naked) void playerDamageFunction()
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
		jmp[playerDamageJMPBack]
	}
}


void playerDamageCallback();
bool createPlayerDamageHook();
