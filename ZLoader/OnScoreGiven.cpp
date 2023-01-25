#include "pch.h"
#include "OnScoreGiven.h"

DWORD scoreGivenCallbackAddress;
DWORD scoreGivenJMPBack;
int OnScoreGivenEvent;
int OnScoreGivenScore;
int OnScoreGivenCurrentScore;

decltype(OnScoreGiven) *ScoreGivenFunc;



void ScoreGivenCallback()
{
    if (consoleCheats == true)
    {
        OnScoreGivenScore = 0;
    }

    if (ScoreGivenFunc != NULL)
    {
        ScoreGivenFunc(&OnScoreGivenEvent, &OnScoreGivenScore, &OnScoreGivenCurrentScore);
    }
}


bool createScoreGivenHook()
{
    PlaceJMP((BYTE*)rabbidsBaseAddress + 0x2A8121, (DWORD)ScoreGivenASMFunction, 5);
    scoreGivenJMPBack = (rabbidsBaseAddress + 0x2A8121) + 5;
    scoreGivenCallbackAddress = (DWORD)&ScoreGivenCallback;
    ScoreGivenFunc = hook(GetProcAddress(modDLL, "OnScoreGiven"));
    return true;
}

