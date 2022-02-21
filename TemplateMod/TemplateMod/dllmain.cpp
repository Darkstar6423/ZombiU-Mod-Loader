// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "dllmain.h"



bool mod_init()
{
	//code that runs on start goes here

	return true;
}


void OnPlayerDamage(DWORD PlayerAdr, DWORD ZombieAdr, float* Damage)
{
	*Damage = 0;

}


void OnPlayerTick(DWORD PlayerAdr)
{



}



void OnZombieDamage(DWORD ZombieAdr, DWORD Inflictor, float* Damage)
{
	if (Inflictor != NULL)
		*Damage = (float)1;
}



void OnFlashLightDrain(DWORD Player, float* small_Drain, float* large_Drain)
{

	*small_Drain = 1;
	*large_Drain = 2;

}



void OnFlashLightGain(DWORD Player, float* Amount)
{

	*Amount = 15;
}


void OnWeaponFire(DWORD Weapon, int* clip)
{

	*clip += 1;

}
