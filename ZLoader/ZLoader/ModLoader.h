#pragma once

#include "windows.h"
#include <iostream>
#include "ZombiStructs.h"

//function definitions
typedef __declspec(dllimport) int(__cdecl* c_initFunction)();
typedef __declspec(dllimport) int(__cdecl* c_playerDamageFunction)(player Player, zombie Zombie, float* Damage);
typedef __declspec(dllimport) int(__cdecl* c_playerTickFunction)(player Player);
typedef __declspec(dllimport) int(__cdecl* c_zombieDamageFunction)(zombie Zombie, player Player, float* Damage);

extern HINSTANCE modDLL;


bool loadExternalDLL(c_initFunction& Initfunc);

bool loadCPlayerDamageFunction(c_playerDamageFunction& PDamagefunc);
bool loadCPlayerTickFunction(c_playerTickFunction& PTickfunc);
bool loadCZombieDamageFunction(c_zombieDamageFunction& ZDamagefunc);

