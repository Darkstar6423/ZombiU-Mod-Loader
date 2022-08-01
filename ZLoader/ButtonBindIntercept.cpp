#include "pch.h"
#include "ButtonBindIntercept.h"

DWORD ButtonBindJMPBack;
DWORD ButtonBindInterceptAddr;
DWORD SEAX;
DWORD SEDX;
DWORD ButtonPressed;

decltype(interceptButtonBind)* buttonBindInterceptModFunc;


void buttonBindIntercept()
{

    if (buttonBindInterceptModFunc != NULL)
    {
        SEAX = buttonBindInterceptModFunc(SEAX, ButtonPressed);
    }

    if (isDrawingConsole)
    {
        SEAX = 0;
    }

}


bool CreateButtonBindIntercept()
{
    PlaceJMP((BYTE*)rabbidsBaseAddress + 0x1ADD, (DWORD)ButtonBindInterceptAMS, 5);
    ButtonBindJMPBack = (rabbidsBaseAddress + 0x1ADD) + 5;
    ButtonBindInterceptAddr = (DWORD)&buttonBindIntercept;
    buttonBindInterceptModFunc = hook(GetProcAddress(modDLL, "interceptButtonBind"));
    return true;
}