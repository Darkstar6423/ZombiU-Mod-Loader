#include "pch.h"
#include "dllmain.h"
#include "DrawText.h"
#include <thread>
#include <mutex>



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
std::thread messageThread;
DWORD quickMessageText;
std::mutex Messagemtx;

void quickMessage(const char16_t* text, int time)
{
	//Messagemtx.lock();
	quickMessageText = (DWORD) & *text;

	DRAWTEXT(text, 10, 1);
	Sleep(time * 1000);
	DRAWTEXT(text, 10, 0);
	quickMessageText = 0x00000000;
	Sleep(500);
	//Messagemtx.unlock();

}

void DRAWIMESSAGE(const char16_t* text, int time)
{

	if (quickMessageText != (DWORD)&*text)
	{
	TerminateThread(messageThread.native_handle(), 0);
	std::thread messageThread(quickMessage, text, time);
	messageThread.detach();
	}
}

