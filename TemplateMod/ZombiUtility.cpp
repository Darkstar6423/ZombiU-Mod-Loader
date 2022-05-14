#include "pch.h"
#include "ZombiUtility.h"

decltype(getZombieStruct)* getZombie;
decltype(getWeaponStruct)* getWeapon;
decltype(getPlayerStruct)* getPlayer;
decltype(DRAWTEXT)* drawtext;
decltype(DRAWIMESSAGE)* drawIMessage;


void loadUtilityFunctions()
{
	HMODULE zloader = GetModuleHandle("zloader.dll");
	getZombie = Func(GetProcAddress(zloader, "getZombieStruct"));
	getWeapon = Func(GetProcAddress(zloader, "getWeaponStruct"));
	getPlayer = Func(GetProcAddress(zloader, "getPlayerStruct"));
	drawtext = Func(GetProcAddress(zloader, "DRAWTEXT"));
	drawIMessage = Func(GetProcAddress(zloader, "DRAWIMESSAGE"));


}