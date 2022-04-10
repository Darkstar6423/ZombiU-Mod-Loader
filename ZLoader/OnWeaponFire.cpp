#include "pch.h"
#include "OnWeaponFire.h"


DWORD OnWeaponFireCallbackAddress;
DWORD OnWeaponFireJMPBack;


DWORD OnWeaponFireWeapon;
DWORD OnWeaponFireEDX;
DWORD OnWeaponFireECX;

decltype(OnWeaponFire) *WeapFireFunc;

void OnWeaponFireCallback()
{

    if (WeapFireFunc != NULL)
    {
        int* clip = (int*)((char*)OnWeaponFireEDX+0x148);
        WeapFireFunc(OnWeaponFireWeapon, clip);
        int* RealAmmo = (int*)((char*)OnWeaponFireWeapon+0x4b4);
        *RealAmmo = *clip;//put this in so that the Real ammo matches the Clip ammo
    }


}


bool createWeaponFireHook()
{
    PlaceJMP((BYTE*)rabbidsBaseAddress + 0x1F4405, (DWORD)weaponFireFunction, 6);
    OnWeaponFireJMPBack = (rabbidsBaseAddress + 0x1F4405) + 6;
    OnWeaponFireCallbackAddress = (DWORD)&OnWeaponFireCallback;
    WeapFireFunc = hook(GetProcAddress(modDLL, "OnWeaponFire"));
    return true;
}
