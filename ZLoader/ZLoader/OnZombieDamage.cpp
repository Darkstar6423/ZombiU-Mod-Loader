#include "pch.h"
#include "OnZombieDamage.h"


//Zombie Damage Function
DWORD zombieDamageCallbackAddress;
DWORD zombieDamageJMPBack;
//parameters
DWORD zombieDamageCallbackZombie;
DWORD zombieDamageCallbackECX;
c_zombieDamageFunction ZDamagefunc;

void zombieDamageCallback()
{
    struct zombie Zombie = getZombieStruct(zombieDamageCallbackZombie);
    if (*Zombie.health > 0)
    {
        struct player Player = getPlayerStruct(OnPlayerTickCallbackPlayer);
        float* Damage = (float*)((char*)zombieDamageCallbackECX + 0x0C);
        ZDamagefunc(zombieDamageCallbackZombie, OnPlayerTickCallbackPlayer, Damage);
    }
    return;

}



bool createZombieDamageHook()
{
    PlaceJMP((BYTE*)rabbidsBaseAddress + 0x2533AF, (DWORD)zombieDamageFunction, 5);
    zombieDamageJMPBack = (rabbidsBaseAddress + 0x2533AF) + 5;
    zombieDamageCallbackAddress = (DWORD)&zombieDamageCallback;
    loadCZombieDamageFunction(ZDamagefunc);
    return true;
}
