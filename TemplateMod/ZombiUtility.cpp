#include "pch.h"
#include "ZombiUtility.h"

decltype(GETZOMBIESTRUCT)* getZombie;
decltype(GETWEAPONSTRUCT)* getWeapon;
decltype(GETPLAYERSTRUCT)* getPlayer;
decltype(DRAWTEXT)* drawtext;
decltype(DRAWIMESSAGE)* drawIMessage;
decltype(GIVEITEM)* giveItem;
decltype(GETINVENTORYADDRESS)* getInventoryAddress;

void loadUtilityFunctions()
{
	HMODULE zloader = GetModuleHandle("zloader.dll");
	getZombie = Func(GetProcAddress(zloader, "GETZOMBIESTRUCT"));
	getWeapon = Func(GetProcAddress(zloader, "GETWEAPONSTRUCT"));
	getPlayer = Func(GetProcAddress(zloader, "GETPLAYERSTRUCT"));
	drawtext = Func(GetProcAddress(zloader, "DRAWTEXT"));
	drawIMessage = Func(GetProcAddress(zloader, "DRAWIMESSAGE"));
	giveItem = Func(GetProcAddress(zloader, "GIVEITEM"));
	getInventoryAddress = Func(GetProcAddress(zloader, "GETINVENTORYADDRESS"));


}