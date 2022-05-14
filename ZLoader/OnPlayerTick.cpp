#include "pch.h"
#include "OnPlayerTick.h"


//Runs every tick on the player
DWORD OnPlayerTickCallbackAddress;
DWORD OnPlayerTickJMPBack;
//parameters
DWORD OnPlayerTickCallbackPlayer;
decltype(OnPlayerTick) *PtickFunc;

void onPlayerTickCallback()
{
    struct player Player = GETPLAYERSTRUCT(OnPlayerTickCallbackPlayer);

    if (PtickFunc != NULL)
    {
        PtickFunc(OnPlayerTickCallbackPlayer);
    }
    return;
}




bool createPlayerTickHook()
{
    PlaceJMP((BYTE*)rabbidsBaseAddress + 0xE40A8, (DWORD)onPlayerTickFunction, 8);
    OnPlayerTickJMPBack = (rabbidsBaseAddress + 0xE40A8) + 8;
    OnPlayerTickCallbackAddress = (DWORD)&onPlayerTickCallback;
    PtickFunc = hook(GetProcAddress(modDLL, "OnPlayerTick"));
    return true;
}


