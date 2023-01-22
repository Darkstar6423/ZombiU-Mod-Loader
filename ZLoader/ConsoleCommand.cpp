#include "ConsoleCommand.h"
#include "pch.h"



void blankCommand(std::string args[])
{

	std::cout << "There was no function defined" << std::endl;
}


ConsoleCommand::ConsoleCommand(std::string name="default", std::string desc="A Command", int param = 0, void(&func)(std::string args[]) = blankCommand)
{

	this->description = desc;
	this->name = name;
	this->parameters = param;
	this->function = &func;
}

ConsoleCommand::ConsoleCommand() {}

ConsoleCommand::~ConsoleCommand(){}