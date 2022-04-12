#pragma once
#include "hookparameter.h"
#include "OverrideParameters.h"


static __declspec(naked) void manualPingCheckFunction()
{
	__asm
	{

		call eax
		movzx eax, al
		mov manualPingCheckEBX, EBX
		mov manualPingCheckECX, ECX
		mov manualPingCheckEAX, EAX
		call canMinimapManualPingOverrideAddress
		mov EBX, manualPingCheckEBX
		mov ECX, manualPingCheckECX
		mov EAX, manualPingCheckEAX
		jmp manualPingCheckJMPBack

	}

}


void canMinimapManualPingOverride();
bool createManualPingCheckOverride();