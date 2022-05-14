#pragma once

extern "C" {
	_declspec(dllexport) void __cdecl DRAWTEXT(const char16_t *text, int type, bool visible);
	_declspec(dllexport) void __cdecl DRAWIMESSAGE(const char16_t* text, int time);
}