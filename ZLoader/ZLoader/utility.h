#pragma once
#include "windows.h"
#include "ModLoader.h"

extern HANDLE process_handle;

extern DWORD rabbidsBaseAddress;

static long getZombiBaseAddress();

//Player Damage Function
extern DWORD playerDamageJMPBack;//where this jump will return to
extern DWORD playerDamageCallbackAddress;//the address of our callback
//parameters
extern DWORD playerDamageCallbackPlayer;
extern DWORD playerDamageCallbackDamage;
extern DWORD* playerDamageCallbackEBP;
extern DWORD* playerDamageCallbackEAX;
extern DWORD* playerDamageCallbackESP;
extern DWORD* playerDamageCallbackECX;

//Zombie Damage Function
extern DWORD zombieDamageCallbackAddress;
extern DWORD zombieDamageJMPBack;
//parameters
extern DWORD zombieDamageCallbackZombie;
extern DWORD zombieDamageCallbackECX;
extern DWORD zombieDamageCallbackEBP;

//Runs every tick on the player
extern DWORD OnPlayerTickCallbackAddress;
extern DWORD OnPlayerTickJMPBack;
//parameters
extern DWORD OnPlayerTickCallbackPlayer;

//Runs every time the flash light battery drains
extern DWORD FlashLightDrainCallbackAddress;
extern DWORD FlashLightDrainJMPBack;
extern DWORD FlashLightDrainPlayer;
//Runs Every time the flash light regens battery
extern DWORD FlashLightGainCallbackAddress;
extern DWORD FlashLightGainJMPBack;
extern DWORD FlashLightGainPlayer;
//onWeaponFire
extern DWORD OnWeaponFireCallbackAddress;
extern DWORD OnWeaponFireJMPBack;
extern DWORD OnWeaponFireWeapon;
extern DWORD OnWeaponFireEDX;
extern DWORD OnWeaponFireECX;


void PlaceJMP(BYTE* Address, DWORD jumpTo, DWORD length = 5);
