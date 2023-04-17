#include "Config.h"
#include "pch.h"


CONFIG::CONFIG()
{

	setDefaultSettings();
	std::ifstream configFileIn = std::ifstream("mods/settings.txt");
	std::string plaintext;
	size_t delim;
	while (getline(configFileIn, plaintext))
	{
		std::string setting = plaintext.substr(0, delim = plaintext.find("="));
		std::string value = plaintext.substr(delim + 1);


		settings[setting] = value;


	}
	configFileIn.close();



}

CONFIG::~CONFIG()
{

}


int CONFIG::setDefaultSettings()
{
	settings["selectedMod"] = "default";
	settings["devConsole"] = "0";
	return 0;
}