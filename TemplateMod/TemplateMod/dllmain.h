#pragma once
#include "ZombiStructs.h"



bool mod_init();
void OnPlayerDamage(DWORD PlayerAdr, DWORD ZombieAdr, float* Damage);
void OnPlayerTick(DWORD PlayerAdr);
void OnZombieDamage(DWORD ZombieAdr, DWORD PlayerAdr, float* Damage, bool isHeadShot);
void OnFlashLightDrain(DWORD Player, float* small_Drain, float* large_Drain);
void OnFlashLightGain(DWORD Player, float* Amount);
void OnWeaponFire(DWORD Weapon, int* clip);
void OnWeaponSwitch(DWORD Weapon, int* type);
void OnScoreGiven(int* ScoreEvent, int* Score, int* CurrentScore);

#include "ZloaderEventHooks.h"