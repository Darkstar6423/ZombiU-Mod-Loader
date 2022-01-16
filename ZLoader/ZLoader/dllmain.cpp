#include <Windows.h>
#include <vector>
#include "dllmain.h"
#include "pch.h"
#include "ZombiStructs.h"

//Todo: make it call a list of functions in a vector

void playerDamageCallback()
{
    DWORD* attacker = (DWORD*)((char*)playerDamageCallbackEBP-0x10);
    zombie Zombie = getZombieStruct(*attacker);

    player Player = getPlayerStruct(playerDamageCallbackPlayer);
    float* damage = (float*)playerDamageCallbackDamage;


    *damage = 0;
}


void PlaceJMP(BYTE* Address, DWORD jumpTo, DWORD length = 5)
{
    DWORD dwOldProtect, dwBkup, dwRelAddr;

    //give that address read and write permissions and store the old permissions at oldProtection
    VirtualProtect(Address, length, PAGE_EXECUTE_READWRITE, &dwOldProtect);

    // Calculate the "distance" we're gonna have to jump - the size of the JMP instruction
    dwRelAddr = (DWORD)(jumpTo - (DWORD)Address) - 5;

    // Write the JMP opcode @ our jump position...
    *Address = 0xE9;

    // Write the offset to where we're gonna jump
   //The instruction will then become JMP ff002123 for example
    *((DWORD*)(Address + 0x1)) = dwRelAddr;

    // Overwrite the rest of the bytes with NOPs
    //ensuring no instruction is Half overwritten(To prevent any crashes)
    for (DWORD x = 0x5; x < length; x++)
        *(Address + x) = 0x90;

    VirtualProtect(Address, length, dwOldProtect, &dwBkup);
}

bool createPlayerDamageHook()
{
    PlaceJMP((BYTE*)rabbidsBaseAddress + 0x00E17F8, (DWORD)playerDamageFunctions, 5);
    playerDamageJMPBack = (rabbidsBaseAddress + 0x00E17F8) + 5;
    playerDamageCallbackAddress = (DWORD)&playerDamageCallback;
    return true;
}




DWORD WINAPI MainThread(LPVOID param)
{
    Sleep(2000);

    process_handle = GetCurrentProcess();
    rabbidsBaseAddress = (DWORD)GetModuleHandle("rabbids.win32.f.dll");
    createPlayerDamageHook();


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