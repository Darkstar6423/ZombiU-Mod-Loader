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

struct player
{
	DWORD baseAddress;
	float* health;
	float* stamina;
	float* torch;

	struct pos
	{
		float* X;
		float* Y;
		float* Z;
	};
};

player getPlayerStruct(DWORD Address);
