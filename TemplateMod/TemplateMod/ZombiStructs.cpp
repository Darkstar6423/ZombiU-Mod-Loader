#include "pch.h"
#include "ZombiStructs.h"


player getPlayerStruct(DWORD Address)
{
	struct player Player;
	Player.baseAddress = Address;
	Player.health = (float*)((char*)Address + 0x1b4);
	Player.stamina = (float*)((char*)Address + 0xc34);
	Player.torch = (float*)((char*)Address + 0xEC0);
	DWORD* weaponAddr = (DWORD*)((char*)Address + 0xDCC);
	Player.Weapon = getWeaponStruct(*weaponAddr);

	return Player;
}


weapon getWeaponStruct(DWORD Address)
{
	struct weapon Weapon;
	Weapon.baseAddress = Address;
	Weapon.clip = (int*)((char*)Address + 0x4b4);
	Weapon.Type = (int*)((char*)Address + 0x278);
	Weapon.isEquiped = (DWORD)((char*)Address + 0x56C) != 0x0;
	return Weapon;
}



//todo: add rockstar zombie offset ??? I'm going to need 2 or more of these to find this
zombie getZombieStruct(DWORD Address)
{
	struct zombie Zombie;
	Zombie.baseAddress = Address;
	Zombie.health = (float*)((char*)Address + 0x1b4);

	//todo: change to use a "flag system" where we add up the values
	if ((int)*((char*)Address + 0x224) == 1)
	{
		Zombie.zedType = 1;//spitter
	}
	else if ((int)*((char*)Address + 0x4F8) == 15)
	{
		Zombie.zedType = 2;//swat
	}
	else if ((int)*((char*)Address + 0x478) == 1)
	{
		Zombie.zedType = 3;//ghost
	}
	else if ((int)*((char*)Address + 0x288) == 9)
	{
		Zombie.zedType = 4;//super zombie
	}
	else if ((int)*((char*)Address + 0x288) == 7)
	{
		Zombie.zedType = 0;//normal
	}



	return Zombie;
}
