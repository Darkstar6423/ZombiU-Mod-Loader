#include "GUI.h"
#include <filesystem>
namespace fs = std::filesystem;




GUI::GUI(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR     lpCmdLine,
    _In_ int       nCmdShow)
{

    GUI::hInstance = hInstance;
    WNDCLASSEX wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(wcex.hInstance, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);


    if (!RegisterClassEx(&wcex))
    {
        MessageBox(NULL,
            _T("Call to RegisterClassEx failed!"),
            _T("Windows Desktop Guided Tour"),
            NULL);

        return;
    }


    GUI::window = CreateWindowEx(
        WS_EX_OVERLAPPEDWINDOW,
        szWindowClass,
        szTitle,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        WIN_WIDTH, WIN_HEIGHT,
        NULL,
        NULL,
        hInstance,
        NULL
    );

}


GUI::~GUI()
{


}

GUI::GUI()
{
}


int GUI::createLaunchButton()
{
    
     GUI::launchButton = CreateWindow(
        L"Button",  // Predefined class; Unicode assumed 
        L"Launch ZombiU",      // Button text 
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
        2,         // x position 
        650,         // y position 
        370,        // Button width
        72,        // Button height
        GUI::window,     // Parent window
        (HMENU)LAUNCH_BUTTON,       // No menu.
        (HINSTANCE)GetWindowLongPtr(GUI::window, GWLP_HINSTANCE),
        NULL);      // Pointer not needed.


     SetFocus(GUI::launchButton);
     return 0;
}


int GUI::createListBox()
{

    GUI::modSelection = CreateWindow(
        L"listbox",  // Predefined class; Unicode assumed 
        L"Launch ZombiU",      // Button text 
        WS_CHILD | WS_VISIBLE | WS_VSCROLL | LBS_DISABLENOSCROLL | LBS_NOTIFY,  // Styles 
        2,         // x position 
        2,         // y position 
        370,        // Button width
        600,        // Button height
        GUI::window,     // Parent window
        (HMENU)MOD_LISTBOX,       // No menu.
        (HINSTANCE)GetWindowLongPtr(GUI::window, GWLP_HINSTANCE),
        NULL);      // Pointer not needed.

    int pos = (int)SendMessage(GUI::modSelection, LB_ADDSTRING, 0, (LPARAM)TEXT("(No Mods)"));
    SendMessage(GUI::modSelection, LB_SETITEMDATA, pos, (LPARAM)0);
    GUI::mods[0] = "default";
    std::string path = "mods";
    int i = 1;
    for (const auto& entry : fs::directory_iterator(path))
    {
        std::string filename = entry.path().filename().string();
        std::size_t found = filename.find(".", 0);
        if (entry.is_directory() && filename.compare("default") != 0 && i<100) 
        {
            pos = (int)SendMessage(GUI::modSelection, LB_ADDSTRING, 0, (LPARAM)entry.path().filename().c_str());
            SendMessage(GUI::modSelection, LB_SETITEMDATA, pos, (LPARAM)i);
            GUI::mods[i] = filename;
            i++;
        }
    }

    return 0;
}