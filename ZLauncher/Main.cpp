#include "Main.h"


CONFIG config;

using namespace System;
using namespace System::Windows::Forms;


//HKEY_LOCAL_MACHINE\SOFTWARE\WOW6432Node\Valve\Steam\Apps\339230\install_path

[STAThread]
void Main(array<String^>^ args)
{
    //Find the ZombiU install directory from the steam registry key.
    HKEY hKey;
    LONG lRes = RegOpenKeyExA(HKEY_LOCAL_MACHINE, "SOFTWARE\\WOW6432Node\\Valve\\Steam\\Apps\\339230", 2, KEY_READ, &hKey);
    if (lRes != ERROR_SUCCESS)
    {
        MessageBoxA(0, "Could not find ZOMBI path", "ZLaucher Error", MB_OK);
        return;
    }
    WCHAR pBuffer[520];
    DWORD pBufferLength = 520;
    if (RegQueryValueExW(hKey, L"install_path", 0, NULL, (LPBYTE)pBuffer, &pBufferLength) != ERROR_SUCCESS)
    {
        MessageBoxA(0, "Could not find ZOMBI path", "ZLaucher Error", MB_OK);
    }
    std::wstring zombiPath = pBuffer;


	config = CONFIG::CONFIG();
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	ZLauncher::Main form;
    auto temp = gcnew String(zombiPath.c_str());
    form.ZombiDirectory = temp;
	Application::Run(% form);

}



