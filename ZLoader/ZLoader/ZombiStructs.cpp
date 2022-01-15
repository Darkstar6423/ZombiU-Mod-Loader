#include "ZombiStructs.h"
#include "pch.h"

player getPlayerStruct(DWORD Address)
{
	struct player Player;
	Player.baseAddress = Address;
	Player.health = (float*)((char*)Address+0x1b4);
	Player.stamina = (float*)((char*)Address+0xc34);
	Player.torch = (float*)((char*)Address+0xEC0);

	return Player;
}




zombie getZombieStruct(DWORD Address)
{
	struct zombie Zombie;
	Zombie.baseAddress = Address;
	Zombie.health = (float*)((char*)Address + 0x1b4);

	return Zombie;
}