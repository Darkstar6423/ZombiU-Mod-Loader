#pragma once
#include <windows.h>
#include <string>
#include <iostream>


class ConsoleCommand
{
public:

	ConsoleCommand(std::string name, std::string desc, int param, void(&func)(std::string args[]));
	ConsoleCommand();
	~ConsoleCommand();

	std::string name;
	std::string description;
	int parameters;
	void(*function)(std::string args[]);

private: 


};