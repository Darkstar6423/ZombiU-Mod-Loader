#include "pch.h"
#include "dllmain.h"
#include "DrawText.h"
#include <thread>


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
struct quckMessageArgs {
	const char16_t *text;
	int time;
};

void quickMessage(const char16_t* text, int time)
{
	DRAWTEXT(text, 10, 1);
	Sleep(time * 1000);
	DRAWTEXT(text, 10, 0);
}

void DRAWIMESSAGE(const char16_t* text, int time)
{
	std::thread t(quickMessage, text, time);
	t.detach();
}

