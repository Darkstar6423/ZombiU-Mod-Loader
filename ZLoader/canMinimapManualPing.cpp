#include "canMinimapManualPing.h"
#include "pch.h"

DWORD manualPingCheckJMPBack;
DWORD manualPingCheckEBX;
DWORD manualPingCheckECX;
int manualPingCheckEAX;
DWORD canMinimapManualPingOverrideAddress;

decltype(canMinimapManualPing)* CanMinimapManualPingFunc;

void canMinimapManualPingOverride()
{
    if (CanMinimapManualPingFunc != NULL)
    {
        manualPingCheckEAX = CanMinimapManualPingFunc(OnPlayerTickCallbackPlayer);
    }
}




bool createManualPingCheckOverride()
{
    PlaceJMP((BYTE*)rabbidsBaseAddress + 0x1ED843, (DWORD)manualPingCheckFunction, 5);
    manualPingCheckJMPBack = (rabbidsBaseAddress + 0x1ED843) + 5;
    canMinimapManualPingOverrideAddress = (DWORD)&canMinimapManualPingOverride;
    CanMinimapManualPingFunc = hook(GetProcAddress(modDLL, "canMinimapManualPing"));
    return true;
}