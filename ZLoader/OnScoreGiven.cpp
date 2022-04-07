#include "pch.h"
#include "OnScoreGiven.h"

DWORD scoreGivenCallbackAddress;
DWORD scoreGivenJMPBack;
int OnScoreGivenEvent;
int OnScoreGivenScore;
int OnScoreGivenCurrentScore;

c_ScoreAddFunction ScoreGivenFunc;



void ScoreGivenCallback()
{
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
    loadCScoreAddFunc(ScoreGivenFunc);
    return true;
}

