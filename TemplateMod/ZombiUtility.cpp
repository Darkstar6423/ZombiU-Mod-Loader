#include "pch.h"
#include "ZombiUtility.h"

decltype(GETZOMBIESTRUCT)* getZombie;
decltype(GETWEAPONSTRUCT)* getWeapon;
decltype(GETPLAYERSTRUCT)* getPlayer;
decltype(DRAWTEXT)* drawtext;
decltype(DRAWIMESSAGE)* drawIMessage;


void loadUtilityFunctions()
{
	HMODULE zloader = GetModuleHandle("zloader.dll");
	getZombie = Func(GetProcAddress(zloader, "GETZOMBIESTRUCT"));
	getWeapon = Func(GetProcAddress(zloader, "GETWEAPONSTRUCT"));
	getPlayer = Func(GetProcAddress(zloader, "GETPLAYERSTRUCT"));
	drawtext = Func(GetProcAddress(zloader, "DRAWTEXT"));
	drawIMessage = Func(GetProcAddress(zloader, "DRAWIMESSAGE"));


}