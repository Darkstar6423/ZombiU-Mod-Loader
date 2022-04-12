#pragma once
#include <Windows.h>
#include "ModLoader.h"
#include "..\TemplateMod\ZLoaderFunctionOverrides.h"

//auto ping override
extern DWORD autoPingCheckJMPBack;
extern DWORD autoPingCheckEBX;
extern DWORD autoPingCheckECX;
extern DWORD autoPingCheckEAX;
extern DWORD canMinimapAutoPingOverrideAddress;

//manual ping override
extern DWORD manualPingCheckJMPBack;
extern DWORD manualPingCheckEBX;
extern DWORD manualPingCheckECX;
extern int manualPingCheckEAX;
extern DWORD canMinimapManualPingOverrideAddress;