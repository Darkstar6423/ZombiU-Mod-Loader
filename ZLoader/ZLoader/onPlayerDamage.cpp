#include "pch.h"
#include "OnPlayerDamage.h"

//Player Damage Function
DWORD playerDamageJMPBack;//where this jump will return to
DWORD playerDamageCallbackAddress;//the address of our callback
//parameters
DWORD playerDamageCallbackPlayer;
DWORD playerDamageCallbackDamage;
DWORD* playerDamageCallbackEBP;

void playerDamageCallback()
{
    DWORD* attacker = (DWORD*)((char*)playerDamageCallbackEBP - 0x10);
    zombie Zombie = getZombieStruct(*attacker);

    player Player = getPlayerStruct(playerDamageCallbackPlayer);
    float* damage = (float*)playerDamageCallbackDamage;

    //give me god mode for testing purposes
    *damage = 0;
    return;
}




bool createPlayerDamageHook()
{
    PlaceJMP((BYTE*)rabbidsBaseAddress + 0x00E17F8, (DWORD)playerDamageFunction, 5);
    playerDamageJMPBack = (rabbidsBaseAddress + 0x00E17F8) + 5;
    playerDamageCallbackAddress = (DWORD)&playerDamageCallback;
    return true;
}
