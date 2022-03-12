#pragma once
#include "ZombiStructs.h"
#include "windows.h"
#include "utility.h"


static __declspec(naked) void WeaponSwitchASMFunction()
{
	__asm
	{
		mov[edi + 0x00000DD8], ebx
		mov OnWeaponSwitchWeaponAddress, EBX
		mov OnWeaponSwitchWeaponType, EAX
		call weaponSwitchCallbackAddress
		jmp [weaponSwitchJMPBack]

	}

}


void WeaponSwitchCallback();
bool createWeaponSwitchHook();
extern c_WeaponSwitchFunction WeaponSwitchFunc;