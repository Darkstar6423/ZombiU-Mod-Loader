#include "pch.h"
#include "dllmain.h"
#include "DrawText.h"


void DRAWTEXT(const char16_t* text, int textType, bool visible)
{
	_asm
	{
		mov esi, rabbidsBaseAddress
		push textType
		push [text]
		push visible
		lea eax, [esi + 0x241F0]
		call eax
		mov ecx, eax
		lea eax, [esi + 0x12E530]
		call eax
	}
}


void DRAWIMESSAGE(const char16_t* text, int time)
{
	DRAWTEXT(text, 10, 1);
	Sleep(time * 1000);
	DRAWTEXT(text, 10, 0);
}
