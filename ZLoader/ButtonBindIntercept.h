#pragma once
#include <Windows.h>
#include "hookparameter.h"
#include "OverrideParameters.h"
#include "ConsoleGUI.h"

extern DWORD ButtonBindJMPBack;
extern DWORD ButtonBindInterceptAddr;
extern DWORD SEAX;
extern DWORD SEDX;
extern DWORD ButtonPressed;

extern decltype(interceptButtonBind)* buttonBindInterceptModFunc;

static __declspec(naked) void ButtonBindInterceptAMS()
{
	_asm
	{
		add esp, 0x08
		mov	SEAX, EAX
		mov SEDX, EDX
		mov ButtonPressed, ECX
		call ButtonBindInterceptAddr
		mov ECX, ButtonPressed
		mov EAX, SEAX
		or eax, edx
		jmp ButtonBindJMPBack

	}
}

bool CreateButtonBindIntercept();