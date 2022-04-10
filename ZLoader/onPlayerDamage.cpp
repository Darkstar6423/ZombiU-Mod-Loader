#include "pch.h"
#include "OnPlayerDamage.h"
//Player Damage Function
DWORD playerDamageJMPBack;//where this jump will return to
DWORD playerDamageCallbackAddress;//the address of our callback
//parameters
DWORD playerDamageCallbackPlayer;
DWORD playerDamageCallbackDamage;
DWORD playerDamageCallbackInflictor;
DWORD* playerDamageCallbackEBP;
DWORD* playerDamageCallbackEAX;
DWORD* playerDamageCallbackESP;
DWORD* playerDamageCallbackECX;
DWORD* playerDamageCallbackEDX;
decltype(OnPlayerDamage) *PDamagefunc;


void playerDamageCallback()
{
    zombie Zombie = getZombieStruct(playerDamageCallbackInflictor);

    player Player = getPlayerStruct(playerDamageCallbackPlayer);
    float* Damage = (float*)((char*)playerDamageCallbackEBP - 0x08);
    if (PDamagefunc != NULL)
    {
        PDamagefunc(playerDamageCallbackPlayer, playerDamageCallbackInflictor, Damage);
    }
    return;
}




bool createPlayerDamageHook()
{
    // this entry point is no longer used since a better one was found
    //PlaceJMP((BYTE*)rabbidsBaseAddress + 0x00E17F8, (DWORD)playerDamageFunction, 5);
    playerDamageJMPBack = (rabbidsBaseAddress + 0x00E17F8) + 5;
    playerDamageCallbackAddress = (DWORD)&playerDamageCallback;
    PDamagefunc = hook(GetProcAddress(modDLL, "OnPlayerDamage"));
    return true;
}
