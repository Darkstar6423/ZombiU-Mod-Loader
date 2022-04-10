#pragma once

#include "ZombiStructs.h"
#include "windows.h"
#include "utility.h"




static __declspec(naked) void FlashLightDrainFunction()
{

	__asm
	{
		mov FlashLightDrainPlayer, esi
		call FlashLightDrainCallbackAddress
		cmp byte ptr[esi + 0x00000EA0], 00
		jmp FlashLightDrainJMPBack
	}


}

bool createFlashLightDrainHook();
void FlashLightDrainCallback();