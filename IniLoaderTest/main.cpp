#include "IniLoader.h"
#include <iostream>
#include <string>

int main()
{
	IniLoader il("config.txt");
	std::string key = "test";
	std::cout << il.GetString(key) << " " << il.GetFloat(key) << " " << il.GetInt(key) << std::endl;

	system("PAUSE");
}