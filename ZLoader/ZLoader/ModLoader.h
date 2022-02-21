#pragma once

#include "windows.h"
#include <iostream>
#include "ZombiStructs.h"

//function definitions
typedef __declspec(dllimport) int(__cdecl* c_initFunction)();
typedef __declspec(dllimport) int(__cdecl* c_playerDamageFunction)(DWORD Player, DWORD Zombie, float* Damage);
typedef __declspec(dllimport) int(__cdecl* c_playerTickFunction)(DWORD Player);
typedef __declspec(dllimport) int(__cdecl* c_zombieDamageFunction)(DWORD Zombie, DWORD inflictor, float* Damage);
typedef __declspec(dllimport) int(__cdecl* c_flashLightDrainFunction)(DWORD Player, float* small_Drain, float* large_Drain);
typedef __declspec(dllimport) int(__cdecl* c_flashLightGainFunction)(DWORD Player, float* Amount);
typedef __declspec(dllimport) int(__cdecl* c_WeaponFireFunction)(DWORD Weapon, int* clip);

extern HINSTANCE modDLL;


bool loadExternalDLL(c_initFunction& Initfunc);

bool loadCPlayerDamageFunction(c_playerDamageFunction& PDamagefunc);
bool loadCPlayerTickFunction(c_playerTickFunction& PTickfunc);
bool loadCZombieDamageFunction(c_zombieDamageFunction& ZDamagefunc);
bool loadCFlashLightDrainFunction(c_flashLightDrainFunction& FlashLightDrainfunc);
bool loadCFlashLightGainFunction(c_flashLightGainFunction& FlashLightGainfunc);
bool loadCWeaponFireFunction(c_WeaponFireFunction& WeaponFireFunc);

