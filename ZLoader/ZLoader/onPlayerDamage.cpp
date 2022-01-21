#include "pch.h"
#include "OnPlayerDamage.h"

//Player Damage Function
DWORD playerDamageJMPBack;//where this jump will return to
DWORD playerDamageCallbackAddress;//the address of our callback
//parameters
DWORD playerDamageCallbackPlayer;
DWORD playerDamageCallbackDamage;
DWORD* playerDamageCallbackEBP;
DWORD* playerDamageCallbackEAX;
DWORD* playerDamageCallbackESP;
DWORD* playerDamageCallbackECX;
c_playerDamageFunction PDamagefunc;


void playerDamageCallback()
{
    DWORD* attacker = (DWORD*)((char*)playerDamageCallbackEBP - 0x10);
    zombie Zombie = getZombieStruct(*attacker);

    player Player = getPlayerStruct(playerDamageCallbackPlayer);
    float* Damage = (float*)playerDamageCallbackDamage;
    if (PDamagefunc != NULL)
    {
        PDamagefunc(playerDamageCallbackPlayer, *attacker, Damage);
    }
    return;
}




bool createPlayerDamageHook()
{
    PlaceJMP((BYTE*)rabbidsBaseAddress + 0x00E17F8, (DWORD)playerDamageFunction, 5);
    playerDamageJMPBack = (rabbidsBaseAddress + 0x00E17F8) + 5;
    playerDamageCallbackAddress = (DWORD)&playerDamageCallback;
    loadCPlayerDamageFunction(PDamagefunc);
    return true;
}
