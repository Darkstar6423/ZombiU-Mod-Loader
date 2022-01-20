// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "dllmain.h"



bool mod_init()
{
	//code that runs on start goes here

	return false;
}


void OnPlayerDamage(DWORD PlayerAdr, DWORD ZombieAdr, float* Damage)
{
	*Damage = 50;

}


void OnPlayerTick(DWORD PlayerAdr)
{



}



void OnZombieDamage(DWORD ZombieAdr, DWORD PlayerAdr, float* Damage)
{
	zombie Zombie = getZombieStruct(ZombieAdr);

	*Damage = *Zombie.health;
}



