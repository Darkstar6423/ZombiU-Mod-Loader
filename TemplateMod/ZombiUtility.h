#pragma once
#include "..\ZLoader\ZombiStructs.h"
#include <type_traits>
#include <windows.h>


class Func {
public:
	explicit Func(FARPROC ptr) : _ptr(ptr) {}


	template <typename T, typename = std::enable_if_t<std::is_function_v<T>>>
	operator T* () const {
		return reinterpret_cast<T*>(_ptr);
	}


private:
	FARPROC _ptr;

};


extern decltype(getZombieStruct)* getZombie;
extern decltype(getWeaponStruct)* getWeapon;
extern decltype(getPlayerStruct)* getPlayer;

void loadUtilityFunctions();