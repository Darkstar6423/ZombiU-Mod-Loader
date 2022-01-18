#pragma once

#include <iostream>
#include <stdio.h>
#include <d3d9.h>
#include <tlhelp32.h>
#include <windows.h>

HANDLE process_handle;

DWORD rabbidsBaseAddress;



long getZombiBaseAddress()
{
	return 0x00400000;
};


/*TODO: event Hooks
OnZombieSpawned
OnWeaponFired
OnZombieTick
*/


//Player Damage Function
DWORD playerDamageJMPBack;//where this jump will return to
DWORD playerDamageCallbackAddress;//the address of our callback
//parameters
DWORD playerDamageCallbackPlayer;
DWORD playerDamageCallbackDamage;
DWORD *playerDamageCallbackEBP;
__declspec(naked) void playerDamageFunction()
{
	__asm
	{
		//Original Code
		movss[esp], xmm0
		//new code
		mov dword ptr playerDamageCallbackPlayer, ecx
		mov dword ptr playerDamageCallbackDamage, esp
		mov dword ptr playerDamageCallbackEBP, ebp
		call playerDamageCallbackAddress
		//Jump Back
		jmp [playerDamageJMPBack]
	}
}

//Zombie Damage Function
DWORD zombieDamageCallbackAddress;
DWORD zombieDamageJMPBack;
//parameters
DWORD zombieDamageCallbackZombie;
DWORD zombieDamageCallbackECX;

__declspec(naked) void zombieDamageFunction()
{

	__asm
	{
		cmp [edi+0x3C],01
		je endoffunction
		mov dword ptr zombieDamageCallbackZombie, edi
		mov dword ptr zombieDamageCallbackECX, ecx

		call zombieDamageCallbackAddress
		endoffunction:
		movss xmm2, [ecx + 0x0C]
		jmp [zombieDamageJMPBack]
	}


}

//Runs every tick on the player
DWORD OnPlayerTickCallbackAddress;
DWORD OnPlayerTickJMPBack;
//parameters
DWORD OnPlayerTickCallbackPlayer;
__declspec(naked) void onPlayerTickFunction()
{

	__asm
	{
		movss xmm0, [esi + 0x00000EC0]
		mov dword ptr OnPlayerTickCallbackPlayer, esi
		call OnPlayerTickCallbackAddress
		jmp [OnPlayerTickJMPBack]
	}


}