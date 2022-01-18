#include "pch.h"
#include "OnPlayerTick.h"


//Runs every tick on the player
DWORD OnPlayerTickCallbackAddress;
DWORD OnPlayerTickJMPBack;
//parameters
DWORD OnPlayerTickCallbackPlayer;



void onPlayerTickCallback()
{
    struct player Player = getPlayerStruct(OnPlayerTickCallbackPlayer);
    return;
}




bool createPlayerTickHook()
{
    PlaceJMP((BYTE*)rabbidsBaseAddress + 0xE40A8, (DWORD)onPlayerTickFunction, 8);
    OnPlayerTickJMPBack = (rabbidsBaseAddress + 0xE40A8) + 8;
    OnPlayerTickCallbackAddress = (DWORD)&onPlayerTickCallback;
    return true;
}


