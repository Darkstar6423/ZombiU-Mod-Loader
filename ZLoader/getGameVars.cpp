#include "getGameVars.h"
#include "GameVariables.h"
#include "pch.h"

DWORD PlayerInventory; // invnetory variable
DWORD ASMINVJMPBACK; //jump back
void injectInventoryGetter()
{
    PlaceJMP((BYTE*)rabbidsBaseAddress + 0x1FFB36, (DWORD)ASMGetInventoryAddress, 7);
    ASMINVJMPBACK = (rabbidsBaseAddress + 0x1FFB36)+7;
}
