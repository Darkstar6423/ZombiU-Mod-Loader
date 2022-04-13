#include "pch.h"
#include "canMinimapManualPing.h"

DWORD manualPingCheckJMPBack;
DWORD manualPingCheckEBX;
DWORD manualPingCheckECX;
int manualPingCheckEAX;
DWORD canMinimapManualPingOverrideAddress;

decltype(canMinimapManualPing)* CanMinimapManualPingFunc;

void canMinimapManualPingOverride()
{
    bool canPing = manualPingCheckEAX;
    if (CanMinimapManualPingFunc != NULL)
    {
        canPing =  CanMinimapManualPingFunc(OnPlayerTickCallbackPlayer, manualPingCheckEAX);
    }
    manualPingCheckEAX = canPing;
}




bool createManualPingCheckOverride()
{
    PlaceJMP((BYTE*)rabbidsBaseAddress + 0x1ED843, (DWORD)manualPingCheckFunction, 5);
    manualPingCheckJMPBack = (rabbidsBaseAddress + 0x1ED843) + 5;
    canMinimapManualPingOverrideAddress = (DWORD)&canMinimapManualPingOverride;
    CanMinimapManualPingFunc = hook(GetProcAddress(modDLL, "canMinimapManualPing"));
    return true;
}