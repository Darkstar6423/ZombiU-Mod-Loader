#pragma once

#include "ZombiStructs.h"
#include "windows.h"
#include "hookparameter.h"



extern DWORD OnFlashLightDrainEAX;
extern DWORD OnFlashLightDrainECX;
extern DWORD OnFlashLightDrainEDX;


static __declspec(naked) void FlashLightDrainFunction()
{

	__asm
	{
		mov OnFlashLightDrainEAX, EAX
		mov OnFlashLightDrainECX, ECX
		mov OnFlashLightDrainEDX, EDX
		mov FlashLightDrainPlayer, esi
		call FlashLightDrainCallbackAddress
		mov EAX, OnFlashLightDrainEAX
		mov ECX, OnFlashLightDrainECX
		mov EDX, OnFlashLightDrainEDX
		mov FlashLightDrainPlayer, esi
		cmp byte ptr[esi + 0x00000EA0], 00
		jmp FlashLightDrainJMPBack
	}


}

bool createFlashLightDrainHook();
void FlashLightDrainCallback();