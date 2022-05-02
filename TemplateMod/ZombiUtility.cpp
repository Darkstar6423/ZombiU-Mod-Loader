#include "pch.h"
#include "ZombiUtility.h"

decltype(getZombieStruct)* getZombie;
decltype(getWeaponStruct)* getWeapon;
decltype(getPlayerStruct)* getPlayer;


void loadUtilityFunctions()
{
	HMODULE zloader = GetModuleHandle(L"zloader.dll");
	getZombie = Func(GetProcAddress(zloader, "getZombieStruct"));
	getWeapon = Func(GetProcAddress(zloader, "getWeaponStruct"));
	getPlayer = Func(GetProcAddress(zloader, "getPlayerStruct"));


}