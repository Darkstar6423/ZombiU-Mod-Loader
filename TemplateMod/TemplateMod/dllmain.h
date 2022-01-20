#pragma once
#include "ZombiStructs.h"

bool mod_init();
void OnPlayerDamage(player Player, zombie Zombie, float* Damage);
void OnPlayerTick(player Player);
void OnZombieDamage(zombie Zombie, player Player, float* Damage);
extern "C" {

	__declspec(dllexport) int __cdecl C_init()
	{

		mod_init();


		return true;
	}
	
	__declspec(dllexport) int __cdecl C_OnPlayerDamage(player Player, zombie Zombie, float* Damage)
	{

		OnPlayerDamage(Player, Zombie, Damage);

		return true;
	}
	
	__declspec(dllexport) int __cdecl C_OnPlayerTick(player Player)
	{

		OnPlayerTick(Player);


		return true;
	}
	
	__declspec(dllexport) int __cdecl C_OnZombieDamage(zombie Zombie, player Player, float* Damage)
	{

		
		OnZombieDamage(Zombie, Player, Damage);

		return true;
	}


}
