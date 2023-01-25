#pragma once
#include "ZombiStructs.h"
#include "windows.h"
#include "hookparameter.h"
#include "console.h"


static __declspec(naked) void ScoreGivenASMFunction()
{
	__asm
	{
		push esi
		mov edi, [ebx + ecx * 4 + 0x00000030]
		mov OnScoreGivenEvent, ECX
		mov OnScoreGivenScore, EDI 
		mov OnScoreGivenCurrentScore, EAX
		call scoreGivenCallbackAddress
		mov EAX, OnScoreGivenCurrentScore
		mov EDI, OnScoreGivenScore
		mov ECX, OnScoreGivenEvent
		jmp [scoreGivenJMPBack]

	}
}


void ScoreGivenCallback();
bool createScoreGivenHook();