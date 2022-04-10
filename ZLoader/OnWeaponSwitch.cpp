#include "pch.h"
#include "OnWeaponSwitch.h"


DWORD weaponSwitchCallbackAddress;
DWORD weaponSwitchJMPBack;
DWORD weaponSwitchECX;


DWORD OnWeaponSwitchWeaponAddress;
int* OnWeaponSwitchWeaponType;
decltype(OnWeaponSwitch) *WeaponSwitchFunc;


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
    WeaponSwitchFunc = hook(GetProcAddress(modDLL,"OnWeaponSwitch"));
    return true;
}
