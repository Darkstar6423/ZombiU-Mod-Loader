#include <windows.h>
#include <TlHelp32.h>
#include <iostream>
#include <fcntl.h>
#include <stdio.h>
#include <limits.h>
using namespace std;


HMODULE zloader;
wchar_t buffer[4096];


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

bool isUConnectRunning()
{
	HKEY key;
	if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, "SOFTWARE\\WOW6432Node\\UBISOFT\\LAUNCHER", 0, KEY_READ, &key) != ERROR_SUCCESS)
	{
		assertError(4, true);
		return false;
	}
	char buffer[512];
	DWORD UConnectPathLength = 512;
	if (RegQueryValueExA(key, "installDir", 0, 0, (LPBYTE)&buffer, &UConnectPathLength) != ERROR_SUCCESS)
	{
		assertError(4, true);
		return false;


	}
	char upcname[] = "upc.exe";

	strncat_s(buffer, upcname, strlen(buffer) - sizeof(upcname));
	cout << endl << buffer << endl;


	// additional information
	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	// set the size of the structures
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));
	si.cb = sizeof(STARTUPINFO);
	si.dwFlags = STARTF_USESHOWWINDOW;
	si.wShowWindow = SW_MINIMIZE;
	CreateProcessA(buffer,   // the path
		NULL,        // Command line
		NULL,           // Process handle not inheritable
		NULL,           // Thread handle not inheritable
		FALSE,          // Set handle inheritance to FALSE
		CREATE_DEFAULT_ERROR_MODE | CREATE_NEW_PROCESS_GROUP,
		NULL,           // Use parent's environment block
		NULL,           // Use parent's starting directory 
		(LPSTARTUPINFOA)&si,            // Pointer to STARTUPINFO structure
		&pi             // Pointer to PROCESS_INFORMATION structure (removed extra parentheses)
	);


	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);

	while (!getProcId(L"UplayWebCore.exe"))
		Sleep(200);
	
	cout << "UConnect successfully launched" << endl;

	return true;
}




int main(int argc, char* argv[])
{



	int error = 0;


	int UConnectPID = getProcId(L"upc.exe");
	if (UConnectPID == 0)
	{
		assertError(3, false);
		if (!isUConnectRunning())
		{
			return false;
		}
	}
	cout << "Starting Zombi.exe" << endl;
	// additional information
	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	// set the size of the structures
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	si.wShowWindow = SW_MINIMIZE;

	// start the program up
	CreateProcess(L"ZOMBI.EXE",   // the path
		NULL,        // Command line
		NULL,           // Process handle not inheritable
		NULL,           // Thread handle not inheritable
		FALSE,          // Set handle inheritance to FALSE
		CREATE_DEFAULT_ERROR_MODE | CREATE_NEW_PROCESS_GROUP,
		NULL,           // Use parent's environment block
		NULL,           // Use parent's starting directory 
		&si,            // Pointer to STARTUPINFO structure
		&pi             // Pointer to PROCESS_INFORMATION structure (removed extra parentheses)
	);

	Sleep(2000);

	while (!getProcId(L"ZOMBI.exe"))
		Sleep(1000);
	
	int pID = getProcId(L"ZOMBI.exe");
	cout << "Zombi.exe launched successfully. Injecting..." << endl;
	char dll[] = "ZLoader.dll";
	char dllpath[MAX_PATH] = { 0 };
	GetFullPathNameA(dll, MAX_PATH, dllpath, NULL);
	
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, pID);
	if (hProcess == NULL && error == 0)
	{
		error = assertError(2, true);
		return error;
	}
	

	LPVOID pszLibFileRemote = VirtualAllocEx(hProcess, NULL, strlen(dllpath)+1, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

	WriteProcessMemory(hProcess, pszLibFileRemote, dllpath, strlen(dllpath)+1, NULL);
	HANDLE handleThread = CreateRemoteThread(hProcess, NULL, NULL, (LPTHREAD_START_ROUTINE)LoadLibraryA, pszLibFileRemote, NULL, NULL);
	
	WaitForSingleObject(handleThread, INFINITE);
	CloseHandle(handleThread);

	VirtualFreeEx(hProcess, dllpath, 0, MEM_RELEASE);


	CloseHandle(hProcess);

	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);

	while (getProcId(L"ZOMBI.exe"))
	{
		Sleep(200);
	}
	cout << "The game closed, closing the launcher" << endl;
	return 0;

}