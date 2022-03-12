// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "dllmain.h"



bool mod_init()
{
	//code that runs on start goes here
	//note: this does not run in the game loop, this runs in the DLL thread

	return true;
}


void OnPlayerDamage(DWORD PlayerAdr, DWORD ZombieAdr, float* Damage)
{
	*Damage = 0;

}


void OnPlayerTick(DWORD PlayerAdr)
{



}



void OnZombieDamage(DWORD ZombieAdr, DWORD Inflictor, float* Damage, bool isHeadShot)
{

}


void OnFlashLightDrain(DWORD Player, float* small_Drain, float* large_Drain)
{

	*small_Drain = 0;
	*large_Drain = 0;

}



void OnFlashLightGain(DWORD Player, float* Amount)
{

	*Amount = 0;
}


void OnWeaponFire(DWORD Weapon, int* clip)
{

	*clip += 1;

}

void OnWeaponSwitch(DWORD Weapon, int* type)
{
	weapon weap = getWeaponStruct(Weapon);
	if (*weap.Type == 14)
	{
		*weap.damage *= 1.2;
		*weap.upgradedDamage *= 1.2;
	}
}
