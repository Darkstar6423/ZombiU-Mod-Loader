#include "pch.h"
#include "OnFlashLightDrain.h"


DWORD FlashLightDrainCallbackAddress;
DWORD FlashLightDrainJMPBack;
DWORD FlashLightDrainPlayer;
c_flashLightDrainFunction onFlashLightDrainFunc;

void FlashLightDrainCallback()
{



	if (onFlashLightDrainFunc != NULL)
	{
		float* smallDrain = (float*)((char*)FlashLightDrainPlayer + 0xA60);
		float* largeDrain = (float*)((char*)FlashLightDrainPlayer + 0xA5C);
		onFlashLightDrainFunc(FlashLightDrainPlayer, smallDrain, largeDrain);
	}

}

bool createFlashLightDrainHook()
{
	PlaceJMP((BYTE*)rabbidsBaseAddress + 0xE3C54, (DWORD)FlashLightDrainFunction, 7);
	FlashLightDrainJMPBack = (rabbidsBaseAddress + 0xE3C54) + 7;
	FlashLightDrainCallbackAddress = (DWORD)&FlashLightDrainCallback;
	loadCFlashLightDrainFunction(onFlashLightDrainFunc);
	return true;
}

