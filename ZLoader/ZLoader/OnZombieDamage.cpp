#include "pch.h"
#include "OnZombieDamage.h"


//Zombie Damage Function
DWORD zombieDamageCallbackAddress;
DWORD zombieDamageJMPBack;
//parameters
DWORD zombieDamageCallbackZombie;
DWORD zombieDamageCallbackECX;


void zombieDamageCallback()
{
    struct zombie Zombie = getZombieStruct(zombieDamageCallbackZombie);
    if (*Zombie.health > 0)
    {
        struct player Player = getPlayerStruct(OnPlayerTickCallbackPlayer);
        float* damage = (float*)((char*)zombieDamageCallbackECX + 0x0C);

        if (*Player.Weapon.Type == 1)
        {
            *damage = *Zombie.health;
        }

    }
    return;

}



bool createZombieDamageHook()
{
    PlaceJMP((BYTE*)rabbidsBaseAddress + 0x2533AF, (DWORD)zombieDamageFunction, 5);
    zombieDamageJMPBack = (rabbidsBaseAddress + 0x2533AF) + 5;
    zombieDamageCallbackAddress = (DWORD)&zombieDamageCallback;
    return true;
}
