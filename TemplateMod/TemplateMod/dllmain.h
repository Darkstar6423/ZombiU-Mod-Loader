#pragma once
#include "ZombiStructs.h"



bool mod_init();
void OnPlayerDamage(DWORD PlayerAdr, DWORD ZombieAdr, float* Damage);
void OnPlayerTick(DWORD PlayerAdr);
void OnZombieDamage(DWORD ZombieAdr, DWORD PlayerAdr, float* Damage);

#include "ZloaderFunctions.h"