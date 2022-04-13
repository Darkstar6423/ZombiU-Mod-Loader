#pragma once
#include "ZombiStructs.h"
#include "hookparameter.h"
#include "windows.h"


static __declspec(naked) void onPlayerTickFunction()
{

	__asm
	{
		mov OnPlayerTickCallbackPlayer, esi
		call OnPlayerTickCallbackAddress
		mov esi, OnPlayerTickCallbackPlayer
		movss xmm0, [esi + 0x00000EC0]
		jmp[OnPlayerTickJMPBack]
	}


}
void onPlayerTickCallback();
bool createPlayerTickHook();