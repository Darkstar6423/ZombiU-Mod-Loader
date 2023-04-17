#include "config.h"


CONFIG::CONFIG()
{

	setDefaultSettings();
	std::ifstream configFileIn = std::ifstream("mods/settings.txt");
	std::string plaintext;
	size_t delim;
	while (getline(configFileIn, plaintext))
	{
		std::string setting = plaintext.substr(0, delim = plaintext.find("="));
		std::string value = plaintext.substr(delim+1);


		settings[setting] = value;
		
		
	}
	configFileIn.close();



}

CONFIG::~CONFIG()
{

	
}

int CONFIG::saveSettings()
{
	std::ofstream configFileOut("mods/settings.txt");
	for (auto const& [key, val] : settings)
	{

		configFileOut << key << '=' << val << std::endl;


	}

	configFileOut.close();
	return 0;
}


int CONFIG::setDefaultSettings()
{
	settings["selectedMod"] = "default";
	settings["devConsole"] = "0";
	return 0;
}