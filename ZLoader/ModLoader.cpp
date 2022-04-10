#include "ModLoader.h"
#include "pch.h"

HINSTANCE modDLL;

bool loadExternalDLL()
{
	modDLL = LoadLibrary("mods\\default\\mod.dll");
	
	if (!modDLL)
	{
		MessageBoxA(NULL, "Mod.dll not found in the mod's folder", "Fatal Error", MB_OK);
		return false;
	}

	decltype(init) *init = hook(GetProcAddress(modDLL, "init"));
	if (!init)
	{
		MessageBoxA(NULL, "Could not find initialization function", "Fatal Error", MB_OK);
		return false;
	}
	init();
	return true;
}


bool loadCScoreAddFunc(c_ScoreAddFunction& ScoreAddFunc)
{
	ScoreAddFunc = (c_ScoreAddFunction)GetProcAddress(modDLL, "c_ScoreGivenFunction");
	if (!ScoreAddFunc)
	{
		//MessageBoxA(NULL, "Could not find c_ScoreAddFunc function", "Fatal Error", MB_OK);
		return false;
	}
	return true;
}