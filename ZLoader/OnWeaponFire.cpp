#include "pch.h"
#include "OnWeaponFire.h"


DWORD OnWeaponFireCallbackAddress;
DWORD OnWeaponFireJMPBack;


DWORD OnWeaponFireWeapon;
DWORD OnWeaponFireEDX;
DWORD OnWeaponFireECX;

decltype(OnWeaponFire) *WeapFireFunc;
bool infiniteAmmo = false;

void OnWeaponFireCallback()
{
    int* clip = (int*)((char*)OnWeaponFireEDX + 0x148);
    int* RealAmmo = (int*)((char*)OnWeaponFireWeapon + 0x4b4);
    if (WeapFireFunc != NULL)
    {
      
        WeapFireFunc(OnWeaponFireWeapon, clip);
        
   
       
    }

    if (infiniteAmmo == true)
    {
        *clip += 1;
    }
    *RealAmmo = *clip;//put this in so that the Real ammo matches the Clip ammo

}


bool createWeaponFireHook()
{
    console.createConsoleCommand("bottomlessclip", "Ammo is not consumed when firing the weapon. Cheat Command", 0, cheatInfiniteAmmo);
    PlaceJMP((BYTE*)rabbidsBaseAddress + 0x1F4405, (DWORD)weaponFireFunction, 6);
    OnWeaponFireJMPBack = (rabbidsBaseAddress + 0x1F4405) + 6;
    OnWeaponFireCallbackAddress = (DWORD)&OnWeaponFireCallback;
    WeapFireFunc = hook(GetProcAddress(modDLL, "OnWeaponFire"));
    return true;
}

void cheatInfiniteAmmo(string args[])
{
    if (infiniteAmmo == true)
    {
        infiniteAmmo = false;
        cout << "Bottomless Clip Disabled" << endl;
    }
    else
    {
        infiniteAmmo = true;
        cout << "Bottomless Clip Enabled" << endl;

    }
    consoleCheats = true;

}