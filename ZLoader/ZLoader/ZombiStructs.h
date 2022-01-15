#pragma once
#include <windows.h>

struct zombie
{
	DWORD baseAddress;
	float* health;

};

zombie getZombieStruct(DWORD Address);

struct player
{
	DWORD baseAddress;
	float* health;
	float* stamina;
	float* torch;
};

player getPlayerStruct(DWORD Address);