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


//100064.8984
void OnZombieDamage(DWORD ZombieAdr, DWORD Inflictor, float* Damage, bool isHeadShot)
{
	//removal of random cricket bat one shots
	if (isHeadShot == true && Inflictor != NULL)
	{
		player Player = getPlayerStruct(Inflictor);
		if (*Player.Weapon.Type == 6 && *Damage > (float)1000)
		{
			*Damage = (float)*Player.Weapon.damage;
		}

	}


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


}

void OnWeaponSwitch(DWORD Weapon, int* type)
{
	
	weapon weap = getWeaponStruct(Weapon);
	switch (*weap.Type)
	{
	case 6:
		*weap.damage = 45.0;
		break;
	case 14:
		*weap.upgradedDamage = 2.0;
		*weap.damage = 1.0;
		break;
	}
	
}
