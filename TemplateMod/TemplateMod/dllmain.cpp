// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "dllmain.h"



bool mod_init()
{
	//code that runs on start goes here

	return false;
}


void OnPlayerDamage(player Player, zombie Zombie, float* Damage)
{
	*Damage = 50;

}


void OnPlayerTick(player Player)
{



}



void OnZombieDamage(zombie Zombie, player Player, float* Damage)
{

	*Damage = *Zombie.health;
}



