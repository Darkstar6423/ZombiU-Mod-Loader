#pragma once
#include "hookparameter.h"
#include "OverrideParameters.h"
static __declspec(naked) void autoPingCheckFunction()
{
	__asm
	{
		
		mov autoPingCheckEBX, EBX
		mov autoPingCheckECX, ECX
		mov autoPingCheckEAX, EAX
		call canMinimapAutoPingOverrideAddress
		mov EBX, autoPingCheckEBX
		mov ECX, autoPingCheckECX
		mov EAX, autoPingCheckEAX
		cmp byte ptr[ebx + 0x0000015C], 00
		jmp autoPingCheckJMPBack

	}
}




void canMinimapAutoPingOverride();
bool createAutoPingCheckOverride();