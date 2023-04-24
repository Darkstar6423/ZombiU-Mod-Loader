#include <Windows.h>
#include "pch.h"
DWORD WINAPI MainThread(LPVOID param)
{
    while (true)
    {
        
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