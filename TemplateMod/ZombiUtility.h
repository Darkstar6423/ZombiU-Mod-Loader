#pragma once
#include "..\ZLoader\modFunctions.h"
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


extern decltype(GETZOMBIESTRUCT)* getZombie;
extern decltype(GETWEAPONSTRUCT)* getWeapon;
extern decltype(GETPLAYERSTRUCT)* getPlayer;
extern decltype(DRAWTEXT)* drawtext;
extern decltype(DRAWIMESSAGE)* drawIMessage;
extern decltype(GIVEITEM)* giveItem;
extern decltype(GETINVENTORYADDRESS)* getInventoryAddress;
void loadUtilityFunctions();