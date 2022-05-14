#include "pch.h"
#include "OnZombieDamage.h"


//Zombie Damage Function
DWORD zombieDamageCallbackAddress;
DWORD zombieDamageJMPBack;
//parameters
DWORD zombieDamageCallbackZombie;
DWORD zombieDamageCallbackInflictor;
DWORD zombieDamageCallbackIsHeadShot;
DWORD zombieDamageCallbackEDX;
DWORD *zombieDamageCallbackEBP;
float* zombieDamageCallbackHealth;
float zombieDamageCallbackXMM0;

decltype(OnZombieDamage) *ZDamagefunc;

void zombieDamageCallback()
{
    struct zombie Zombie = GETZOMBIESTRUCT(zombieDamageCallbackZombie);
    if (*Zombie.health > 0)
    {
        float* damage = (float*)((char*)zombieDamageCallbackEBP - 0x08);
        bool isHeadShot = (bool)zombieDamageCallbackIsHeadShot;
        if (ZDamagefunc != NULL)
        {
            ZDamagefunc(zombieDamageCallbackZombie, zombieDamageCallbackInflictor, damage, isHeadShot);
        }
    }
    return;

}



bool createZombieDamageHook()
{
    PlaceJMP((BYTE*)rabbidsBaseAddress + 0x25FF06, (DWORD)zombieDamageFunction, 5);
    zombieDamageJMPBack = (rabbidsBaseAddress + 0x25FF06) + 5;
    zombieDamageCallbackAddress = (DWORD)&zombieDamageCallback;
    ZDamagefunc = hook(GetProcAddress(modDLL, "OnZombieDamage"));
    return true;
}
