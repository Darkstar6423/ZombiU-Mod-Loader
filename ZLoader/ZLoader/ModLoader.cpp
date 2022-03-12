#include "ModLoader.h"
#include "pch.h"

HINSTANCE modDLL;

bool loadExternalDLL(c_initFunction&Initfunc)
{
	modDLL = LoadLibrary("mods\\default\\mod.dll");
	
	if (!modDLL)
	{
		MessageBoxA(NULL, "Mod.dll not found in the mod's folder", "Fatal Error", MB_OK);
		return false;
	}

	Initfunc = (c_initFunction)GetProcAddress(modDLL, "C_init");
	if (!Initfunc)
	{
		MessageBoxA(NULL, "Could not find initialization function", "Fatal Error", MB_OK);
		return false;
	}

	return true;
}

bool loadCPlayerDamageFunction(c_playerDamageFunction &PDamagefunc)
{
	PDamagefunc = (c_playerDamageFunction)GetProcAddress(modDLL, "C_OnPlayerDamage");

	if (!PDamagefunc)
	{
		//MessageBoxA(NULL, "Could not find C_OnPlayerDamage function", "Fatal Error", MB_OK);
		return false;
	}
	return true;
}

bool loadCPlayerTickFunction(c_playerTickFunction& PTickfunc)
{
	PTickfunc = (c_playerTickFunction)GetProcAddress(modDLL, "C_OnPlayerTick");
	if (!PTickfunc)
	{
		//MessageBoxA(NULL, "Could not find C_OnPlayerTick function", "Fatal Error", MB_OK);
		return false;
	}
	return true;
}

bool loadCZombieDamageFunction(c_zombieDamageFunction& ZDamagefunc)
{
	ZDamagefunc = (c_zombieDamageFunction)GetProcAddress(modDLL, "C_OnZombieDamage");
	if (!ZDamagefunc)
	{
		//MessageBoxA(NULL, "Could not find C_OnZombieDamage function", "Fatal Error", MB_OK);
		return false;
	}
	return true;
	
}

bool loadCFlashLightDrainFunction(c_flashLightDrainFunction& FlashLightDrainfunc)
{
	FlashLightDrainfunc = (c_flashLightDrainFunction)GetProcAddress(modDLL, "c_OnflashLightDrain");
	if (!FlashLightDrainfunc)
	{
		//MessageBoxA(NULL, "Could not find c_flashLightDrainFunction function", "Fatal Error", MB_OK);
		return false;
	}
	return true;
}
bool loadCFlashLightGainFunction(c_flashLightGainFunction& FlashLightGainfunc)
{
	FlashLightGainfunc = (c_flashLightGainFunction)GetProcAddress(modDLL, "c_OnflashLightGain");
	if (!FlashLightGainfunc)
	{
		//MessageBoxA(NULL, "Could not find c_flashLightDrainFunction function", "Fatal Error", MB_OK);
		return false;
	}
	return true;
}

bool loadCWeaponFireFunction(c_WeaponFireFunction& WeaponFireFunc)
{
	WeaponFireFunc = (c_WeaponFireFunction)GetProcAddress(modDLL, "c_WeaponFireFunction");
	if (!WeaponFireFunc)
	{
		//MessageBoxA(NULL, "Could not find c_WeaponFireFunction function", "Fatal Error", MB_OK);
		return false;
	}
	return true;
}
bool loadCWeaponSwitchFunction(c_WeaponSwitchFunction& WeaponSwitchFunc)
{
	WeaponSwitchFunc = (c_WeaponSwitchFunction)GetProcAddress(modDLL, "c_WeaponSwitchFunction");
	if (!WeaponSwitchFunc)
	{
		//MessageBoxA(NULL, "Could not find c_WeaponSwitchFunction function", "Fatal Error", MB_OK);
		return false;
	}
	return true;
}