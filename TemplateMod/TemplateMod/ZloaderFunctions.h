#pragma once
#include "ZombiStructs.h"
#include "dllmain.h"

extern "C" {

	__declspec(dllexport) int __cdecl C_init()
	{

		mod_init();


		return true;
	}

	__declspec(dllexport) int __cdecl C_OnPlayerDamage(DWORD PlayerAdr, DWORD ZombieAdr, float* Damage)
	{

		OnPlayerDamage(PlayerAdr, ZombieAdr, Damage);

		return true;
	}

	__declspec(dllexport) int __cdecl C_OnPlayerTick(DWORD PlayerAdr)
	{

		OnPlayerTick(PlayerAdr);


		return true;
	}

	__declspec(dllexport) int __cdecl C_OnZombieDamage(DWORD ZombieAdr, DWORD PlayerAdr, float* Damage)
	{


		OnZombieDamage(ZombieAdr, PlayerAdr, Damage);

		return true;
	}


}
