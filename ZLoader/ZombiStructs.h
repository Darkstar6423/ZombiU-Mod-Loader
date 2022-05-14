#pragma once
#include <windows.h>

extern "C" {
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

	_declspec(dllexport) zombie __cdecl GETZOMBIESTRUCT(DWORD Address);

	/*to add:
	current ammo:for both inbag and out of bag: 50%
	*/


	/*
	weapon types: offset:278; read only
	weapon spread upgrade: 434; read only
	weapon clip: 4b4; write-read
	is weapon damage upgraded: ; read only;
	weapon damage: ; write-read
	weapon upgraded damage: write-read
	weapon spread: 5D0; write-read
	upgraded weapon spread: 294; write-read
	is weapon spread upgraded: 434; read only

	*/

	struct weapon
	{
		DWORD baseAddress;
		int* clip; //offset 4b4
		bool isEquiped;
		int* Type;
		//stats
		bool* damageUpgraded;
		float* damage;
		float* upgradedDamage;
		bool* spreadUpgraded;
		float* spread;
		float* upgradedSpread;
		bool* fireRateUpgraded;
		float* fireRate;
		float* upgradedFireRate;

	};

	_declspec(dllexport) weapon __cdecl GETWEAPONSTRUCT(DWORD Address);


	struct player
	{
		DWORD baseAddress;
		float* health;
		float* stamina;
		float* torch;
		float* torchRegeAmount;
		float* torchDrainSmallAmount;
		float* torchDrainLargeAmount;
		struct weapon Weapon;//offset dcc

		struct pos origin;
	};

	_declspec(dllexport) player __cdecl  GETPLAYERSTRUCT(DWORD Address);

}