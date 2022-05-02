#pragma once

#include <windows.h>
#include <iostream>
#include <type_traits>


//modhook object
class hook {
public:
	explicit hook(FARPROC ptr) : _ptr(ptr) {}


	template <typename T, typename = std::enable_if_t<std::is_function_v<T>>>
	operator T* () const {
		return reinterpret_cast<T*>(_ptr);
	}
	

private:
	FARPROC _ptr;

};

//function definitions

extern HINSTANCE modDLL;


bool loadExternalDLL();



