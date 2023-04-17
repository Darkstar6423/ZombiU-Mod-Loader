#pragma once
#include <map>
#include <string>
#include <windows.h>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <any>

class CONFIG
{
public:


	std::map <std::string, std::string> settings;
	int setDefaultSettings();
	CONFIG();
	~CONFIG();



};

extern CONFIG config;