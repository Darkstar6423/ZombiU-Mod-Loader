#include "console.h"
#include "pch.h"
#include "Config.h"

thread consoleThread;

bool consoleCheats = false;

void ConsoleHandler()
{
	cout << "ZombiU Mod Loader v0.1" << endl;
	string Consolebuffer;
	while (true)
	{
		cout << ">>";
		getline(cin, Consolebuffer);
		for (int x = 0; x < Consolebuffer.length(); x++)
			Consolebuffer[x] = tolower(Consolebuffer[x]);
		if (Consolebuffer == "")
		{
			continue;
		}
		string test = Consolebuffer.substr(0, Consolebuffer.find(" "));
		if (console.commands[test].function == nullptr)
		{
			cout << "Invalid Command" << endl;
			continue;
		}
		int i = 0;
		string args[50];
		string temp = Consolebuffer;
		string delim = " ";
		size_t pos = 0, pos_end;
		pos_end = temp.find(delim, pos);
		pos = pos_end + delim.length();
		while (console.commands[test].parameters > 0 && (pos_end = temp.find(delim, pos)) != std::string::npos && i < 50)
		{
			args[i] = temp.substr(pos, pos_end - pos);
			pos = pos_end + delim.length();
			
			i++;
		}
		if (i > 0)
		{
			args[i] = temp.substr(pos);
		}

		console.commands[test].function(args);
		Consolebuffer = "";
	}
}

void Console::createConsoleCommand(std::string name, std::string desc, int param, void(&func)(string args[]))
{
	ConsoleCommand c = ConsoleCommand(name, desc, param, func);
	console.commands[name] = c;


}


Console::Console()
{
}

int Console::createConsole()
{
	if (stoi(config.settings["devConsole"]) == 1)
	{

		AllocConsole();
		bool result = true;
		FILE* fp;

		// Redirect STDIN if the console has an input handle
		if (GetStdHandle(STD_INPUT_HANDLE) != INVALID_HANDLE_VALUE)
			if (freopen_s(&fp, "CONIN$", "r", stdin) != 0)
				result = false;
			else
				setvbuf(stdin, NULL, _IONBF, 0);

		// Redirect STDOUT if the console has an output handle
		if (GetStdHandle(STD_OUTPUT_HANDLE) != INVALID_HANDLE_VALUE)
			if (freopen_s(&fp, "CONOUT$", "w", stdout) != 0)
				result = false;
			else
				setvbuf(stdout, NULL, _IONBF, 0);

		// Redirect STDERR if the console has an error handle
		if (GetStdHandle(STD_ERROR_HANDLE) != INVALID_HANDLE_VALUE)
			if (freopen_s(&fp, "CONOUT$", "w", stderr) != 0)
				result = false;
			else
				setvbuf(stderr, NULL, _IONBF, 0);

		// Make C++ standard streams point to console as well.
		ios::sync_with_stdio(true);

		// Clear the error state for each of the C++ standard streams.
		std::wcout.clear();
		std::cout.clear();
		std::wcerr.clear();
		std::cerr.clear();
		std::wcin.clear();
		std::cin.clear();
		console.createConsoleCommand("help", "prints a list of all commands", 0, helpFunction);
		thread consoleThread(ConsoleHandler);
		consoleThread.detach();
	}
	return 0;
}

Console::~Console()
{
}

void helpFunction(string args[])
{
	map<string, ConsoleCommand>::iterator it;
	for (it = console.commands.begin(); it != console.commands.end(); it++)
	{
		cout << console.commands[it->first].name << ": " << console.commands[it->first].description << endl;

	}


}