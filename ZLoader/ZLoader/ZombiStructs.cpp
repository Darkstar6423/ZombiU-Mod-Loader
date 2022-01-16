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

//224 spitter
//288 zombie type super zed = 9; normal = 7
//4f8 armor? 15 = swat
//478 ghost zombie?

zombie getZombieStruct(DWORD Address)
{
	struct zombie Zombie;
	Zombie.baseAddress = Address;
	Zombie.health = (float*)((char*)Address + 0x1b4);
	if ((int)*((char*)Address+0x224) == 1)
	{
		Zombie.zedType = 1;
	}
	else if ((int)*((char*)Address+0x4F8) == 15)
	{
		Zombie.zedType = 2;
	}
	else if ((int)*((char*)Address+0x478) == 1)
	{
		Zombie.zedType = 3;
	}
	else if ((int)*((char*)Address+0x288) == 9)
	{
		Zombie.zedType = 4;
	}
	else if ((int)*((char*)Address+0x288) == 7)
	{
		Zombie.zedType = 0;
	}



	return Zombie;
}

