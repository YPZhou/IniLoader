#include "IniLoader.h"

#include <iostream>
#include <fstream>

IniLoader::IniLoader(const char* filename)
{
	std::ifstream ini(filename);
	m_buffer << ini.rdbuf();
	Parse();
}

void IniLoader::Parse()
{
	std::string str = m_buffer.str();
	std::string key(""), value("");
	ParsingStatus ps = KEY;
	for (int i = 0; i < str.length(); i++)
	{
		switch (ps)
		{
		case KEY:
			if (str.at(i) == '=')
			{
				ps = VALUE;
			}
			else if (str.at(i) == ';')
			{
				ps = COMMENT;
			}
			else if (str.at(i) != '\r' && str.at(i) != '\n' && str.at(i) != ' ' && str.at(i) != '\t')
			{
				key.push_back(str.at(i));
			}
			else
			{
				continue;
			}
			break;
		case VALUE:
			if (str.at(i) == '\r' || str.at(i) == '\n')
			{
				ps = KEY;
				m_dict.insert({key, value});
				key = "";
				value = "";
			}
			else if (i == str.length() - 1)
			{
				value.push_back(str.at(i));
				m_dict.insert({ key, value });
			}
			else if (str.at(i) == ';')
			{
				ps = COMMENT;
			}
			else if (str.at(i) != ' ' && str.at(i) != '\t')
			{
				value.push_back(str.at(i));
			}
			else
			{
				continue;
			}
			break;
		case COMMENT:
			if (str.at(i) == '\r' || str.at(i) == '\n')
			{
				ps = KEY;
			}
			else
			{
				continue;
			}
			break;
		default:
			break;
		}
	}

	std::unordered_map<std::string, std::string>::iterator it = m_dict.begin();
	for (; it != m_dict.end(); it++)
	{
		std::cout << "Key " << (*it).first << " Value " << (*it).second << std::endl;
	}
}

std::string IniLoader::GetString(std::string key)
{
	return m_dict[key];
}

int IniLoader::GetInt(std::string key)
{
	return std::stoi(m_dict[key]);
}

float IniLoader::GetFloat(std::string key)
{
	return std::stof(m_dict[key]);
}