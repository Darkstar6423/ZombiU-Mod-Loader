#pragma once

#include "ZombiStructs.h"
#include "windows.h"
#include "utility.h"




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

extern c_flashLightDrainFunction onFlashLightDrainFunc;
bool createFlashLightGainHook();
