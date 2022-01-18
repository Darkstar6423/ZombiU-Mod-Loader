#pragma once
#include "windows.h"
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

//Zombie Damage Function
extern DWORD zombieDamageCallbackAddress;
extern DWORD zombieDamageJMPBack;
//parameters
extern DWORD zombieDamageCallbackZombie;
extern DWORD zombieDamageCallbackECX;

//Runs every tick on the player
extern DWORD OnPlayerTickCallbackAddress;
extern DWORD OnPlayerTickJMPBack;
//parameters
extern DWORD OnPlayerTickCallbackPlayer;


void PlaceJMP(BYTE* Address, DWORD jumpTo, DWORD length = 5);
