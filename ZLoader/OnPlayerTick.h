#pragma once
#include "ZombiStructs.h"
#include "hookparameter.h"
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
void onPlayerTickCallback();
bool createPlayerTickHook();