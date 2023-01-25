#include "InventoryFunctions.h"
#include "dllmain.h"
#include "pch.h"

DWORD PlayerInventory; // invnetory variable
DWORD ASMINVJMPBACK; //jump back
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

void cheatGiveItemCommand(string args[])
{


	if (args[1].empty())
	{
		args[1] = "1";
	}
	if (args[0].empty())
	{

		cout << "Invalid input detected" << endl;
		return;
	}
	if (PlayerInventory == NULL)
	{
		cout << "The players inventory cannot be found!" << endl;
		return;
	}
	std::istringstream stream(args[0]);
	DWORD item;
	stream >> std::hex >> item;
	GIVEITEM(item, stoi(args[1]));
	cout << "0x" << args[0] << " given to player" << endl;
	consoleCheats = true;
}



void injectInventoryGetter()
{
	console.createConsoleCommand("give", "(DWORD)itemhex (int)amount .Gives an item and sends it to the players inventory. Cheat Command", 2, cheatGiveItemCommand);
	PlaceJMP((BYTE*)rabbidsBaseAddress + 0x1FFB36, (DWORD)ASMGetInventoryAddress, 7);
	ASMINVJMPBACK = (rabbidsBaseAddress + 0x1FFB36) + 7;
}
