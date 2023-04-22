#include "dllmain.h"
#include "pch.h"


HINSTANCE ZloaderModule;
CONFIG config;
Console console;


DWORD WINAPI MainThread(LPVOID param)
{

    process_handle = GetCurrentProcess();
    config = CONFIG::CONFIG();
    console.createConsole();
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
        CreateButtonBindIntercept();
        injectInventoryGetter();

        InitDirectX();
        DInput8Init(ZloaderModule);
    }
    

    while (true)
    {
        if (GetAsyncKeyState(VK_F6) & 0x80000)
        {
           MessageBoxA(NULL, "todo: show current mod", "chain loaded dlls", MB_OK);
        }
        Sleep(1);
    }
    return 0;
}

bool WINAPI DllMain(HINSTANCE hModule, DWORD dwReason, LPVOID lpReserved)
{
    
    if (dwReason == DLL_PROCESS_ATTACH)
    {
        ZloaderModule = hModule;
        CreateThread(0, 0, MainThread, hModule, 0, 0);
    }

    return true;
}