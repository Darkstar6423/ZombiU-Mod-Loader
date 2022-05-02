#include "canMinimapAutoPing.h"
#include "pch.h"

DWORD autoPingCheckJMPBack;
DWORD autoPingCheckEBX;
DWORD autoPingCheckECX;
DWORD autoPingCheckEAX;
DWORD canMinimapAutoPingOverrideAddress;

decltype(canMinimapAutoPing) *CanMinimapAutoPingFunc;

void canMinimapAutoPingOverride()
{
    bool *mayAutoPing = (bool*)((char*)autoPingCheckEBX + 0x015C);
    if (CanMinimapAutoPingFunc != NULL)
    {
        *mayAutoPing = CanMinimapAutoPingFunc(OnPlayerTickCallbackPlayer, *mayAutoPing);
    }
    

}




bool createAutoPingCheckOverride()
{
    PlaceJMP((BYTE*)rabbidsBaseAddress + 0x1ED5ED, (DWORD)autoPingCheckFunction, 7);
    autoPingCheckJMPBack = (rabbidsBaseAddress + 0x1ED5ED) + 7;
    canMinimapAutoPingOverrideAddress = (DWORD)&canMinimapAutoPingOverride;
    CanMinimapAutoPingFunc = hook(GetProcAddress(modDLL, "canMinimapAutoPing"));
    return true;
}

