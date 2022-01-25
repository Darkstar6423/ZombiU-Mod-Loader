#include "pch.h"
#include "OnFlashLightGain.h"


DWORD FlashLightGainCallbackAddress;
DWORD FlashLightGainJMPBack;
DWORD FlashLightGainPlayer;
c_flashLightGainFunction onFlashLightGainFunc;

void FlashLightGainCallback()
{


	if (onFlashLightGainFunc != NULL)
	{
		float* amount = (float*)((char*)FlashLightGainPlayer+0xA68);
		onFlashLightGainFunc(FlashLightGainPlayer, amount);
	}

}

bool createFlashLightGainHook()
{
	PlaceJMP((BYTE*)rabbidsBaseAddress + 0xE3EFE, (DWORD)FlashLightGainFunction, 8);
	FlashLightGainJMPBack = (rabbidsBaseAddress + 0xE3EFE) + 8;
	FlashLightGainCallbackAddress = (DWORD)&FlashLightGainCallback;
	loadCFlashLightGainFunction(onFlashLightGainFunc);
	return true;
}
