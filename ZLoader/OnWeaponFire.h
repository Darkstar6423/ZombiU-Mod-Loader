#pragma once
#include "ZombiStructs.h"
#include "windows.h"
#include "hookparameter.h"
#include "Console.h"

void cheatInfiniteAmmo(string args[]);



static __declspec(naked) void weaponFireFunction()
{

	__asm
	{
		mov[edx + 0x00000148], eax
		mov OnWeaponFireEDX, edx
		mov OnWeaponFireECX, ecx
		mov OnWeaponFireWeapon, esi
		call OnWeaponFireCallbackAddress
		mov ecx, OnWeaponFireECX
		jmp OnWeaponFireJMPBack
	}
}



void OnWeaponFireCallback();
bool createWeaponFireHook();