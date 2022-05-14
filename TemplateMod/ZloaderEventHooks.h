#pragma once



extern "C" {

	_declspec(dllexport) bool __cdecl init();
	_declspec(dllexport) void __cdecl OnPlayerDamage(DWORD PlayerAdr, DWORD ZombieAdr, float* Damage);
	_declspec(dllexport) void __cdecl OnPlayerTick(DWORD PlayerAdr);
	_declspec(dllexport) void __cdecl OnZombieDamage(DWORD ZombieAdr, DWORD PlayerAdr, float* Damage, bool isHeadShot);
	_declspec(dllexport) void __cdecl OnWeaponFire(DWORD Weapon, int* clip);
	_declspec(dllexport) void __cdecl OnWeaponSwitch(DWORD Weapon, int* type);
	_declspec(dllexport) void __cdecl OnScoreGiven(int* ScoreEvent, int* Score, int* CurrentScore);

}