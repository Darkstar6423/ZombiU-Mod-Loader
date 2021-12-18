#include <windows.h>
#include <TlHelp32.h>
#include <iostream>
#include <fcntl.h>
#include <stdio.h>
#include <limits.h>
using namespace std;


void PressEnterToContinue()
{
	int c;
	printf("Press ENTER to continue... ");
	fflush(stdout);
	do c = getchar(); while ((c != '\n') && (c != EOF));
}

int getProcId(const wchar_t* target, time_t startTime)
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
	Sleep(1000);
	time_t currentTime = time(0);
	if (pID == 0 && currentTime <= startTime+10)
	{
		pID = getProcId(target, startTime);
	}
	return pID;
}

int assertError(int error=0)
{
	switch (error)
	{
	case 1:
		cout << "Program timed out \nZombi.exe was not launched within 10 seconds\n";
		break;
	case 2:
		cout << "Unable to inject DLL\n";
		break;
	}
	PressEnterToContinue();
	return error;
}


int main(int argc, char* argv[])
{

	// additional information
	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	int error = 0;
	// set the size of the structures
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	// start the program up
	CreateProcess(L"ZOMBI.EXE",   // the path
		NULL,        // Command line
		NULL,           // Process handle not inheritable
		NULL,           // Thread handle not inheritable
		FALSE,          // Set handle inheritance to FALSE
		0,              // No creation flags
		NULL,           // Use parent's environment block
		NULL,           // Use parent's starting directory 
		&si,            // Pointer to STARTUPINFO structure
		&pi             // Pointer to PROCESS_INFORMATION structure (removed extra parentheses)
	);

	Sleep(500);
	time_t start_time = time(0);
	cout << "the current time is " << start_time << "\n";
	const wchar_t* process = L"ZOMBI.exe";
	int pID = getProcId(process, start_time);
	if (pID == 0 && error ==0)
	{
		error = assertError(1);
		return error;
	}


	char dll[] = "ZLoader.dll";
	char dllpath[MAX_PATH] = { 0 };
	GetFullPathNameA(dll, MAX_PATH, dllpath, NULL);
	
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, pID);
	if (hProcess == NULL && error == 0)
	{
		cout << "could not inject dll into process \n";
		error = assertError(2);
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
	
	return 0;

}