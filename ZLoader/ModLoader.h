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
typedef __declspec(dllimport) int(__cdecl* c_ScoreAddFunction)(int *ScoreEvent, int *Score, int *CurrentScore);

extern HINSTANCE modDLL;


bool loadExternalDLL();



