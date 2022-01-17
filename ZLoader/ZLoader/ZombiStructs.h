#pragma once
#include <windows.h>


struct zombie
{
	DWORD baseAddress;
	float* health;
	int zedType;
	struct pos
	{
		float* X;
		float* Y;
		float* Z;
	};
};

zombie getZombieStruct(DWORD Address);

/*to add:
current ammo:for both inbag and out of bag: 50%
*/


/*
weapon types: offset:480
Pistol:0ACFC350
AK47:0ADD0C50
Carbine:0AD01CB0

*/

struct weapon
{
	DWORD baseAddress;
	float* clip; //offset 4b4
	DWORD Type;

	bool isEquiped;
};

weapon getWeaponStruct(DWORD Address);


struct player
{
	DWORD baseAddress;
	float* health;
	float* stamina;
	float* torch;
	struct weapon Weapon;//offset dcc

	struct pos
	{
		float* X;
		float* Y;
		float* Z;
	};
};

player getPlayerStruct(DWORD Address);

