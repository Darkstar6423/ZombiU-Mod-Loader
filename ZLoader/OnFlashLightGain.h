#pragma once

#include "ZombiStructs.h"
#include "windows.h"
#include "hookparameter.h"




static __declspec(naked) void FlashLightGainFunction()
{

	__asm
	{
		mov FlashLightGainPlayer, esi
		call FlashLightGainCallbackAddress
		movss xmm3, [esi + 0x00000A68]
		jmp FlashLightGainJMPBack
	}


}

bool createFlashLightGainHook();
