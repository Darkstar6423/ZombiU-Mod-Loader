#include <windows.h>
#include <TlHelp32.h>
#include <iostream>
#include <fcntl.h>
#include <stdio.h>
#include <limits.h>
using namespace std;


HMODULE zloader;
wchar_t buffer[4096];

struct handle_data {
	unsigned long process_id;
	HWND window_handle;
};


void PressEnterToContinue()
{
	int c;
	printf("Press ENTER to continue... ");
	fflush(stdout);
	do c = getchar(); while ((c != '\n') && (c != EOF));
}

int getProcId(const wchar_t* target)
{
	DWORD pID = 0;
	PROCESSENTRY32 pe32;
	pe32.dwSize = sizeof(PROCESSENTRY32);
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	do
	{
		if (wcscmp(pe32.szExeFile, target) == 0)
		{
			CloseHandle(hSnapshot);
			pID = pe32.th32ProcessID;
			break;
		}
	} while (Process32Next(hSnapshot, &pe32));
	Sleep(100);

	return pID;
}

int assertError(int error = 0, bool critical = false)
{
	switch (error)
	{
	case 1:
		cout << "Program timed out \nZombi.exe was not launched within 10 seconds\n";
		break;
	case 2:
		cout << "Unable to inject DLL\n";
		break;
	case 3:
		cout << "Ubisoft Connect is not active. Starting\n";
		break;
	case 4:
		cout << "Cannot find Ubisoft Connect Directory. Is it installed?\n";
		break;
	}
	if (critical == true)
	{
		PressEnterToContinue();
	}


	return error;
}

BOOL is_main_window(HWND handle)
{
	return GetWindow(handle, GW_OWNER) == (HWND)0 && IsWindowVisible(handle);
}

BOOL CALLBACK enum_windows_callback(HWND handle, LPARAM lParam)
{
	handle_data& data = *(handle_data*)lParam;
	unsigned long process_id = 0;
	GetWindowThreadProcessId(handle, &process_id);
	if (data.process_id != process_id || !is_main_window(handle))
		return TRUE;
	data.window_handle = handle;
	return FALSE;
}

HWND find_main_window(unsigned long process_id)
{
	handle_data data;
	data.process_id = process_id;
	data.window_handle = 0;
	EnumWindows(enum_windows_callback, (LPARAM)&data);
	return data.window_handle;
}

int main(int argc, char* argv[])
{

	int error = 0;

	cout << "Starting Zombi.exe" << endl;
	// additional information
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	// set the size of the structures
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));
	// start the program up
	if (!CreateProcess(L"ZOMBIORG.EXE",   // the path
		NULL,        // Command line
		NULL,           // Process handle not inheritable
		NULL,           // Thread handle not inheritable
		FALSE,          // Set handle inheritance to FALSE
		0,
		NULL,           // Use parent's environment block
		NULL,           // Use parent's starting directory 
		&si,            // Pointer to STARTUPINFO structure
		&pi             // Pointer to PROCESS_INFORMATION structure (removed extra parentheses)
	))
	{
		printf("CreateProcess failed (%d).\n", GetLastError());
		return 0;
	}

	Sleep(2000);
	while (!getProcId(L"UbisoftGameLauncher.exe"))
		Sleep(1000);

	while (!getProcId(L"ZOMBIORG.exe"))
		Sleep(1000);
	
	
	int pID = getProcId(L"ZOMBIORG.exe");

	char dll[] = "ZLoader.dll";
	char dllpath[MAX_PATH] = { 0 };
	GetFullPathNameA(dll, MAX_PATH, dllpath, NULL);
	
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, pID);
	if (hProcess == NULL && error == 0)
	{
		error = assertError(2, true);
		return error;
	}
	//we need to ensure that the window appears before injecting
	cout << "Zombi.exe process found. Waiting for initialization" << endl;
	while(!find_main_window(pID))
		Sleep(100);

	cout << "Zombi.exe launched successfully. Injecting..." << endl;
	LPVOID pszLibFileRemote = VirtualAllocEx(hProcess, NULL, strlen(dllpath) + 1, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

	WriteProcessMemory(hProcess, pszLibFileRemote, dllpath, strlen(dllpath)+1, NULL);
	
	HANDLE handleThread = CreateRemoteThread(hProcess, NULL, NULL, (LPTHREAD_START_ROUTINE)LoadLibraryA, pszLibFileRemote, NULL, NULL);
	
	WaitForSingleObject(handleThread, INFINITE);



	cout << "Injected Successfully" << endl;
	std::string command = "";
	HWND console = GetConsoleWindow();
	DWORD fdwMode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
	SetConsoleMode(console, fdwMode);
	DWORD val = 0;

	//cleanup
	CloseHandle(handleThread);
	VirtualFreeEx(hProcess, dllpath, 0, MEM_RELEASE);
	CloseHandle(hProcess);
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);

	cout << "The game closed, closing the launcher" << endl;
	
	return 0;
	
}