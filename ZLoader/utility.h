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
extern DWORD playerDamageCallbackInflictor;
extern DWORD* playerDamageCallbackEBP;
extern DWORD* playerDamageCallbackEAX;
extern DWORD* playerDamageCallbackESP;
extern DWORD* playerDamageCallbackECX;

//Zombie Damage Function
extern DWORD zombieDamageCallbackAddress;
extern DWORD zombieDamageJMPBack;
//parameters
extern DWORD zombieDamageCallbackZombie;
extern DWORD zombieDamageCallbackInflictor;
extern DWORD zombieDamageCallbackIsHeadShot;
extern DWORD* zombieDamageCallbackEBP;
extern DWORD zombieDamageCallbackEDX;
extern float zombieDamageCallbackXMM0;
extern float* zombieDamageCallbackHealth;

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
//onWeaponSwitch
extern DWORD weaponSwitchCallbackAddress;
extern DWORD weaponSwitchJMPBack;
extern DWORD OnWeaponSwitchWeaponAddress;
extern DWORD weaponSwitchECX;
extern int* OnWeaponSwitchWeaponType;

//OnScoreGiven
extern DWORD scoreGivenCallbackAddress;
extern DWORD scoreGivenJMPBack;
extern int OnScoreGivenEvent;
extern int OnScoreGivenScore;
extern int OnScoreGivenCurrentScore;

void PlaceJMP(BYTE* Address, DWORD jumpTo, DWORD length = 5);
