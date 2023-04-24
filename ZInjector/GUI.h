#pragma once
#include <windows.h>
#include <tchar.h>
#include <string>
#define LAUNCH_BUTTON 102
#define MOD_LISTBOX 103
#define SETTINGS_BUTTON 104
#define WIN_WIDTH 1600
#define WIN_HEIGHT 800



static TCHAR szWindowClass[] = _T("zLauncher");

// The string that appears in the application's title bar.
static TCHAR szTitle[] = _T("ZombiU Mod Launcher v0.1");



// Forward declarations of functions included in this code module:
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

class GUI
{
public: 
	HWND window;
	HINSTANCE hInstance;
	HWND modSelection;
	HWND launchButton;
	HWND settingsButton;
	int buttonFunctions[500];
	std::string mods[1000];

	GUI(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow);
	GUI();
	~GUI();

	int createLaunchButton();
	int createListBox();
	int createSettingsButton();

};
