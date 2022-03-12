#include "pch.h"
#include "OnWeaponSwitch.h"


DWORD weaponSwitchCallbackAddress;
DWORD weaponSwitchJMPBack;

c_WeaponSwitchFunction WeaponSwitchFunc;

DWORD OnWeaponSwitchWeaponAddress;
int* OnWeaponSwitchWeaponType;

void WeaponSwitchCallback()
{
    if (WeaponSwitchFunc != NULL)
    {
        WeaponSwitchFunc(OnWeaponSwitchWeaponAddress, OnWeaponSwitchWeaponType);
    }
}


bool createWeaponSwitchHook()
{
    PlaceJMP((BYTE*)rabbidsBaseAddress + 0xE6D0E, (DWORD)WeaponSwitchASMFunction, 6);
    weaponSwitchJMPBack = (rabbidsBaseAddress + 0xE6D0E) + 6;
    weaponSwitchCallbackAddress = (DWORD)&WeaponSwitchCallback;
    loadCWeaponSwitchFunction(WeaponSwitchFunc);
    return true;
}
