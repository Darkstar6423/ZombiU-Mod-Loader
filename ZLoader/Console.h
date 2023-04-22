#pragma once
#include "ConsoleCommand.h"
#include <windows.h>
#include <map>
#include <iostream>
#include <thread>

using namespace std;

void helpFunction(string args[]);
extern bool consoleCheats;
class Console
{
public:
	Console();
	~Console();
	int createConsole();
	map <string, ConsoleCommand> commands;
	void createConsoleCommand(std::string name, std::string desc, int param, void(&func)(string args[]));


private:
	


};

extern Console console;