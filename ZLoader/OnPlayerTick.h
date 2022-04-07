#pragma once
#include "ZombiStructs.h"
#include "utility.h"
#include "windows.h"


static __declspec(naked) void onPlayerTickFunction()
{

	__asm
	{
		movss xmm0, [esi + 0x00000EC0]
		mov dword ptr OnPlayerTickCallbackPlayer, esi
		call OnPlayerTickCallbackAddress
		jmp[OnPlayerTickJMPBack]
	}


}

extern c_playerTickFunction PtickFunc;
void onPlayerTickCallback();
bool createPlayerTickHook();