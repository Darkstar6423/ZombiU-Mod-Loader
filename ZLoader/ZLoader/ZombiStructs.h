#pragma once
#include <windows.h>


struct pos
{
	float* X;
	float* Y;
	float* Z;
};

struct zombie
{
	DWORD baseAddress;
	float* health;
	int zedType;
	struct pos origin;
};

extern zombie getZombieStruct(DWORD Address);

/*to add:
current ammo:for both inbag and out of bag: 50%
*/


/*
weapon types: offset:278


*/

struct weapon
{
	DWORD baseAddress;
	int* clip; //offset 4b4
	int* Type;

	bool isEquiped;
};

extern weapon getWeaponStruct(DWORD Address);


struct player
{
	DWORD baseAddress;
	float* health;
	float* stamina;
	float* torch;
	struct weapon Weapon;//offset dcc

	struct pos origin;
};

extern player getPlayerStruct(DWORD Address);

