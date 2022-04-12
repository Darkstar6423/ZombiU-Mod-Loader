#pragma once
#include "ZombiStructs.h"
#include "windows.h"
#include "hookparameter.h"



static __declspec(naked) void zombieDamageFunction()
{

	__asm
	{
		movss zombieDamageCallbackXMM0, xmm0
		cmp[ECX + 0x3C],01
		je playerDamage
		mov dword ptr zombieDamageCallbackZombie, ECX
		mov dword ptr zombieDamageCallbackInflictor, EDI
		mov dword ptr zombieDamageCallbackIsHeadShot, EAX
		mov dword ptr zombieDamageCallbackEBP, ebp
		mov dword ptr zombieDamageCallbackEDX, EDX
		call zombieDamageCallbackAddress
		//set variables back
		mov ebp, zombieDamageCallbackEBP
		mov edx, zombieDamageCallbackEDX
		movss xmm0, zombieDamageCallbackXMM0
		endoffunction:
		subss xmm0, [ebp-0x08]
		jmp [zombieDamageJMPBack]
		playerDamage:
		mov dword ptr playerDamageCallbackPlayer, ECX
		mov dword ptr playerDamageCallbackInflictor, EDI
		mov dword ptr playerDamageCallbackEBP, ebp
		mov dword ptr zombieDamageCallbackEDX, EDX
		call playerDamageCallbackAddress
		mov ebp, playerDamageCallbackEBP
		mov edx, zombieDamageCallbackEDX
		movss xmm0, zombieDamageCallbackXMM0
		subss xmm0, [ebp - 0x08]
		jmp[zombieDamageJMPBack]

	}


}



void zombieDamageCallback();
bool createZombieDamageHook();