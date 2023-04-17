#include "ModLoader.h"
#include "pch.h"
#include "..\templatemod\ZloaderEventHooks.h"
#include "config.h"
HINSTANCE modDLL;

bool loadExternalDLL()
{
	std::string modPath = "mods//" + config.settings["selectedMod"] + "//mod.dll";
	char *mod = (char*)modPath.c_str();
	modDLL = LoadLibrary(mod);
	
	if (!modDLL)
	{
		MessageBoxA(NULL, "Mod.dll not found in the mod's folder", "Fatal Error", MB_OK);
		return false;
	}

	decltype(init) *init = hook(GetProcAddress(modDLL, "init"));
	if (*init == NULL)
	{
		MessageBoxA(NULL, "Could not find initialization function", "Fatal Error", MB_OK);
		return false;
	}
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)*init, 0, 0, NULL);

	return true;
}
