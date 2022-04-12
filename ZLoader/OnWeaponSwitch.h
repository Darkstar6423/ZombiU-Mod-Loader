#pragma once
#include "ZombiStructs.h"
#include "windows.h"
#include "hookparameter.h"


static __declspec(naked) void WeaponSwitchASMFunction()
{
	__asm
	{
		mov[edi + 0x00000DD8], ebx
		mov OnWeaponSwitchWeaponAddress, EBX
		mov OnWeaponSwitchWeaponType, EAX
		mov weaponSwitchECX, ECX
		call weaponSwitchCallbackAddress
		mov EAX, OnWeaponSwitchWeaponType
		mov EBX, OnWeaponSwitchWeaponAddress
		mov ECX, weaponSwitchECX
		jmp [weaponSwitchJMPBack]

	}

}


void WeaponSwitchCallback();
bool createWeaponSwitchHook();