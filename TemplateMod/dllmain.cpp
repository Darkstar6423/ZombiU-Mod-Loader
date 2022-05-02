// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "dllmain.h"
#include "ZombiUtility.h"

//code that runs on start goes here
//note: this does not run in the game loop, this runs in a DLL thread
bool init()
{
	loadUtilityFunctions();


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
		player Player = getPlayer(Inflictor);
		if (*Player.Weapon.Type == 6 && *Damage > (float)1000)
		{
			*Damage = (float)*Player.Weapon.damage;
		}

	}


}


void OnFlashLightDrain(DWORD PlayerAdr, float* small_Drain, float* large_Drain)
{

	player Player = getPlayer(PlayerAdr);
	if(*Player.torch >= 98.7)
	{ 
		*small_Drain = 0;
	}
	else
	{
		*small_Drain = -0.1;
	}
	*large_Drain = 0.5;

}



void OnFlashLightGain(DWORD Player, float* Amount)
{

	*Amount = 0.8;
}


void OnWeaponFire(DWORD Weapon, int* clip)
{


}

void OnWeaponSwitch(DWORD Weapon, int* type)
{
	
	weapon weap = getWeapon(Weapon);
	switch (*weap.Type)
	{
	//Pistol
	case 1:
		*weap.upgradedSpread = 0.9;
		if (*weap.spreadUpgraded == 0)
		{
			*weap.spread = 1.5;
		}
		else
		{
			*weap.spread = 1.15;
		}		
		*weap.upgradedDamage = 92.0;
		if (*weap.damageUpgraded == 0)
		{
			*weap.damage = 82.0;
		}
		else
		{
			*weap.damage = 92.0;
		}

		*weap.upgradedFireRate = 0.3;
		if (*weap.fireRateUpgraded == 0)
		{
			*weap.fireRate = 0.5;
		}
		else
		{
			*weap.fireRate = 0.35;
		}

		break;
		// cricket bat
	case 6:
		*weap.damage = 45.0;
		break;
		//silenced pistol
	case 14:
		*weap.upgradedDamage = 80.0;
		if (*weap.damageUpgraded == 0)
		{
			*weap.damage = 70.0;
		}
		else
		{
			*weap.damage = 80.0;
		}
		


		
		break;
	}
	

}

void OnScoreGiven(int* ScoreEvent, int* Score, int* CurrentScore)
{
	*Score *=0.5;
}


//Overrides

bool canMinimapAutoPing(DWORD Player, bool hasAutoPingUpgrade)
{
	return false;
}

bool canMinimapManualPing(DWORD Player, bool hasAutoPingUpgrade)
{
	player player = getPlayer(Player);
	if (*player.torch <= 20)
	{
		return false;
	}

	*player.torch -= 20;
	return true;
}