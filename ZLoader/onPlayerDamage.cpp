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
bool godmode = false;

void playerDamageCallback()
{
    zombie Zombie = GETZOMBIESTRUCT(playerDamageCallbackInflictor);

    player Player = GETPLAYERSTRUCT(playerDamageCallbackPlayer);
    float* Damage = (float*)((char*)playerDamageCallbackEBP - 0x08);
    if (godmode == true)
    {
        *Damage = 0;
    }

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


    console.createConsoleCommand("godmode", "Prevents the player from taking damage. Cheat Command", 0, cheatGodmodeCommand);
    playerDamageJMPBack = (rabbidsBaseAddress + 0x00E17F8) + 5;
    playerDamageCallbackAddress = (DWORD)&playerDamageCallback;
    PDamagefunc = hook(GetProcAddress(modDLL, "OnPlayerDamage"));
    return true;
}


void cheatGodmodeCommand(string args[])
{
    if (godmode == true)
    {
        godmode = false;
        std::cout << "Godmode Disabled" << endl;
    }
    else
    {
        godmode = true;
        std::cout << "Godmode Enabled" << endl;

    }
    consoleCheats = true;
}