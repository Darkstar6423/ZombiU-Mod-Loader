#include "dllmain.h"
#include "pch.h"






DWORD WINAPI MainThread(LPVOID param)
{
    Sleep(2000); // wait for the game to finish loading

    process_handle = GetCurrentProcess();
    rabbidsBaseAddress = (DWORD)GetModuleHandle("rabbids.win32.f.dll"); // get the rabbids base address
    //load the mods dll
    c_initFunction function;
    bool loaded = loadExternalDLL(function);
    function();
    //if the dll does not load, do not insert opcode
    if (loaded)
    {
        //run function insertions
        createPlayerDamageHook();
        createZombieDamageHook();
        createPlayerTickHook();
        createFlashLightDrainHook();
        createFlashLightGainHook();
        createWeaponFireHook();
    }
    while (true)
    {
        if (GetAsyncKeyState(VK_F6) & 0x80000)
        {
           MessageBoxA(NULL, "todo: show chain loaded dlls", "chain loaded dlls", MB_OK);
        }
        
        Sleep(1);
    }
    return 0;
}

bool WINAPI DllMain(HINSTANCE hModule, DWORD dwReason, LPVOID lpReserved)
{
    if (dwReason == DLL_PROCESS_ATTACH)
    {
        CreateThread(0, 0, MainThread, hModule, 0, 0);
    }

    return true;
}