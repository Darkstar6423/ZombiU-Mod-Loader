// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "dllmain.h"
#include "ZombiUtility.h"
#include <string>
//code that runs on start goes here
//note: this does not run in the game loop, this runs in a DLL thread started in zloader.dll
bool init()
{
	loadUtilityFunctions();
	

	DWORD rabbidsadr = (DWORD)GetModuleHandle("rabbids.win32.f.dll");
	DWORD ZOMBIAdr = (DWORD)GetModuleHandle("ZOMBI.EXE");
	while (true)
	{
		Sleep(100);
	}
	return true;
}

void OnPlayerDamage(DWORD PlayerAdr, DWORD ZombieAdr, float* Damage)
{

}


void OnPlayerTick(DWORD PlayerAdr)
{


}


void OnZombieDamage(DWORD ZombieAdr, DWORD Inflictor, float* Damage, bool isHeadShot)
{


}



void OnWeaponFire(DWORD Weapon, int* clip)
{


}

void OnWeaponSwitch(DWORD Weapon, int* type)
{
}

void OnScoreGiven(int* ScoreEvent, int* Score, int* CurrentScore)
{
}


//Overrides

bool canMinimapAutoPing(DWORD Player, bool hasAutoPingUpgrade)
{
	return hasAutoPingUpgrade;
}

bool canMinimapManualPing(DWORD Player, bool hasAutoPingUpgrade)
{
	return hasAutoPingUpgrade;
}

bool interceptButtonBind(bool isPressed, DWORD ButtonPressed)
{
	return isPressed;
}