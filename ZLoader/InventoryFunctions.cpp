#include "InventoryFunctions.h"
#include "dllmain.h"
#include "pch.h"


DWORD GETINVENTORYADDRESS()
{
	if (PlayerInventory != NULL)
	{
		return PlayerInventory;
	}
	return 0x0;
}

void GIVEITEM(DWORD item, int amount)
{
	if (PlayerInventory == NULL) { return; }

	_asm
	{
		mov ecx, PlayerInventory
		mov eax, rabbidsBaseAddress
		add eax, 0x1F3720
		push amount
		push amount
		push item
		call eax
	}


}