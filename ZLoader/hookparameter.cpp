#include "pch.h"
#include "hookparameter.h"


HANDLE process_handle;
DWORD rabbidsBaseAddress;


void PlaceJMP(BYTE* Address, DWORD jumpTo, DWORD length)
{
    DWORD dwOldProtect, dwBkup, dwRelAddr;

    //give that address read and write permissions and store the old permissions at oldProtection
    VirtualProtect(Address, length, PAGE_EXECUTE_READWRITE, &dwOldProtect);

    // Calculate the "distance" we're gonna have to jump - the size of the JMP instruction
    dwRelAddr = (DWORD)(jumpTo - (DWORD)Address) - 5;

    // Write the JMP opcode @ our jump position...
    *Address = 0xE9;

    // Write the offset to where we're gonna jump
   //The instruction will then become JMP ff002123 for example
    *((DWORD*)(Address + 0x1)) = dwRelAddr;

    // Overwrite the rest of the bytes with NOPs
    //ensuring no instruction is Half overwritten(To prevent any crashes)
    for (DWORD x = 0x5; x < length; x++)
        *(Address + x) = 0x90;

    VirtualProtect(Address, length, dwOldProtect, &dwBkup);
}

long getZombiBaseAddress()
{
    return 0x00400000;
}
