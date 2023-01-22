#include "DInput8Main.h"
#include <iostream>
#include <io.h>
#include "pch.h"

bool DInput8Init(HINSTANCE hmodule);

IDirectInput8* pDirectInput = nullptr;
LPDIRECTINPUTDEVICE8 lpdiMouse;
LPDIRECTINPUTDEVICE8 lpdiKeyboard;

typedef HRESULT (__stdcall* GetDeviceStateT)(IDirectInputDevice8* pThis, DWORD cbData, LPVOID lpvData);
GetDeviceStateT pGetDeviceState = nullptr;

HRESULT __stdcall hookGetDeviceState(IDirectInputDevice8* pThis, DWORD cbData, LPVOID lpvData)
{
	HRESULT result = pGetDeviceState(pThis, cbData, lpvData);

	if (result == DI_OK)
	{
		if (cbData == sizeof(DIMOUSESTATE))
		{
			if (((LPDIMOUSESTATE)lpvData)->rgbButtons[0] != 0)
			{


			}
			if (((LPDIMOUSESTATE)lpvData)->rgbButtons[1] != 0)
			{


			}
		}		
		if (cbData == sizeof(DIMOUSESTATE2))
		{
			if (((LPDIMOUSESTATE2)lpvData)->rgbButtons[0] != 0)
			{


			}
			if (((LPDIMOUSESTATE2)lpvData)->rgbButtons[1] != 0)
			{


			}
		}
	
	}
	

	return result;
}


typedef HRESULT(__stdcall* GetDeviceDataT)(IDirectInputDevice8*, DWORD, LPDIDEVICEOBJECTDATA, LPDWORD, DWORD);
GetDeviceDataT pGetDeviceData = nullptr;

HRESULT __stdcall hookGetDeviceData(IDirectInputDevice8* pThis, DWORD cbObjectData, LPDIDEVICEOBJECTDATA rgdod, LPDWORD pdwInOut, DWORD dwFlags) {
	HRESULT result = pGetDeviceData(pThis, cbObjectData, rgdod, pdwInOut, dwFlags);

	if (result == DI_OK) {
		for (int i = 0; i < *pdwInOut; ++i) {
			if (LOBYTE(rgdod[i].dwData) > 0) 
			{ 
				if (rgdod[i].dwOfs == DIK_W) 
				{
					MessageBoxA(NULL, "DInput Failed to load", "DInput Error", 1);
				}
			}
			if (LOBYTE(rgdod[i].dwData) == 0) 
			{ 
				if (rgdod[i].dwOfs == DIK_W) 
				{

				}
			}
		}
	}
	return result;
}

static const WORD MAX_CONSOLE_LINES = 500;



bool DInput8Init(HINSTANCE hmodule)
{
	while (GetModuleHandle("Dinput8.dll") == NULL)
		Sleep(1);


	if (DirectInput8Create((HMODULE)hmodule, DIRECTINPUT_VERSION, IID_IDirectInput8, (LPVOID*)&pDirectInput, NULL) != DI_OK)
	{
		MessageBoxA(NULL,"DInput Failed to load","DInput Error", 1);
		return false;
	}
	if (pDirectInput->CreateDevice(GUID_SysMouse, &lpdiMouse, NULL) != DI_OK)
	{
		pDirectInput->Release();
		MessageBoxA(NULL, "DInput mouse device failed to load", "DInput Error", 1);
		return false;
	}

	
	DWORD Vtable = *(DWORD*)lpdiMouse;
	DWORD* getDeviceStateAddress = (DWORD*)((char*)Vtable+(0x9*0x4));//6393D3A0
	if (MH_CreateHook((DWORD*)*getDeviceStateAddress, &hookGetDeviceState, reinterpret_cast<LPVOID*>(&pGetDeviceState)) != MH_OK)
	{
		MessageBoxA(NULL, "Could not create getDeviceState hook", "DInput Error", 1);
	    return false;
	}

	if (MH_EnableHook((DWORD*)*getDeviceStateAddress) != MH_OK)
	{
		MessageBoxA(NULL, "Coult not enable getDeviceState hook", "DInput Error", 1);
		return false;
	}



	//Keyboard
	DWORD* getDeviceDataAddress = (DWORD*)((char*)Vtable+(0xA*0x4));//6393D3A0
	if (MH_CreateHook((DWORD*)*getDeviceDataAddress, &hookGetDeviceData, reinterpret_cast<LPVOID*>(&pGetDeviceData)) != MH_OK)
	{
		MessageBoxA(NULL, "Could not create getDeviceData hook", "DInput Error", 1);
	    return false;
	}

	if (MH_EnableHook((DWORD*)*getDeviceDataAddress) != MH_OK)
	{
		MessageBoxA(NULL, "Coult not enable getDeviceData hook", "DInput Error", 1);
		return false;
	}







	return true;
}



