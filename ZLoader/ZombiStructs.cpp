#include "pch.h"
#include "ZombiStructs.h"


player GETPLAYERSTRUCT(DWORD Address)
{
	struct player Player;
	Player.baseAddress = Address;
	Player.health = (float*)((char*)Address+0x1b4);
	Player.stamina = (float*)((char*)Address+0xc34);
	Player.torch = (float*)((char*)Address+0xEC0);
	Player.torchRegeAmount = (float*)((char*)Address+ 0xA68);
	Player.torchDrainSmallAmount = (float*)((char*)Address+ 0xA60);
	Player.torchDrainLargeAmount = (float*)((char*)Address+ 0xA5C);
	DWORD* weaponAddr = (DWORD*)((char*)Address + 0xDCC);
	Player.Weapon = GETWEAPONSTRUCT(*weaponAddr);

	return Player;
}


weapon GETWEAPONSTRUCT(DWORD Address)
{
	struct weapon Weapon;
	Weapon.baseAddress = Address;
	Weapon.clip = (int*)((char*)Address+0x4b4);
	Weapon.Type = (int*)((char*)Address+0x278);
	Weapon.isEquiped = (DWORD)((char*)Address+0x56C) != 0x0;
	//stats
	//damage
	Weapon.damageUpgraded = (bool*)((char*)Address + 0x3E0);
	Weapon.upgradedDamage = (float*)((char*)Address + 0x1D8);
	Weapon.damage = (float*)((char*)Address + 0x1D4);
	//spread
	Weapon.spreadUpgraded = (bool*)((char*)Address + 0x434);
	Weapon.spread = (float*)((char*)Address + 0x5D0);
	Weapon.upgradedSpread = (float*)((char*)Address + 0x294);
	//fireRate
	Weapon.fireRateUpgraded = (bool*)((char*)Address + 0x3FC);
	Weapon.fireRate = (float*)((char*)Address + 0x1B0);
	Weapon.upgradedFireRate = (float*)((char*)Address + 0x1B4);
	return Weapon;
}



//todo: add rockstar zombie offset ??? I'm going to need 2 or more of these to find this
zombie GETZOMBIESTRUCT(DWORD Address)
{
	struct zombie Zombie;
	Zombie.baseAddress = Address;
	Zombie.health = (float*)((char*)Address + 0x1b4);

	//todo: change to use a "flag system" where we add up the values
	if ((int)*((char*)Address+0x224) == 1)
	{
		Zombie.zedType = 1;//spitter
	}
	else if ((int)*((char*)Address+0x4F8) == 15)
	{
		Zombie.zedType = 2;//swat
	}
	else if ((int)*((char*)Address+0x478) == 1)
	{
		Zombie.zedType = 3;//ghost
	}
	else if ((int)*((char*)Address+0x288) == 9)
	{
		Zombie.zedType = 4;//super zombie
	}
	else if ((int)*((char*)Address+0x288) == 7)
	{
		Zombie.zedType = 0;//normal
	}



	return Zombie;
}

