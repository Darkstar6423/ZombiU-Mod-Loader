#include "dllmain.h"
#include "pch.h"






DWORD WINAPI MainThread(LPVOID param)
{
    process_handle = GetCurrentProcess();
     
    //load the mod dll
    bool loaded = loadExternalDLL();
    //if the dll does not load, do not insert opcode
    if (loaded)
    {
        

        while (GetModuleHandle("rabbids.win32.f.dll") == NULL)
            Sleep(100);
        rabbidsBaseAddress = (DWORD)GetModuleHandle("rabbids.win32.f.dll"); // get the rabbids base address
        //run function insertions
        createPlayerDamageHook();
        createZombieDamageHook();
        createPlayerTickHook();
        createWeaponFireHook();
        createWeaponSwitchHook();
        createScoreGivenHook();
        //Overrides
        createAutoPingCheckOverride();
        createManualPingCheckOverride();
        injectInventoryGetter();

        InitDirectX();
        

    }
    while (true)
    {
        if (GetAsyncKeyState(VK_F6) & 0x80000)
        {
           MessageBoxA(NULL, "todo: show chain current mod", "chain loaded dlls", MB_OK);
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