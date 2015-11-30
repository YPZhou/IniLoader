#include "IniLoader.h"

#include <iostream>
#include <fstream>


IniLoader::IniLoader(const char* filename, bool debug)
{
	std::ifstream ini(filename);
	m_buffer << ini.rdbuf();

	m_debug = debug;

	Parse();
}


void IniLoader::Parse()
{
	std::string str = m_buffer.str();
	std::string key(""), value(""), listItem("");
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
			else if (str.at(i) == ':')
			{
				ps = LIST;
				m_list.insert(std::make_pair(key, std::vector<std::string>()));
			}
			else if (str.at(i) == ';')
			{
				ps = COMMENT;
			}
			else if (str.at(i) != '\r' && str.at(i) != '\n' && str.at(i) != ' ' && str.at(i) != '\t')
			{
				key.push_back(str.at(i));
			}
			else if (i == str.length() - 1)
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
				m_dict.insert(std::make_pair(key, value));
				key = "";
				value = "";
			}
			else if (i == str.length() - 1)
			{
				value.push_back(str.at(i));
				m_dict.insert(std::make_pair(key, value));
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
		case LIST:
			if (str.at(i) == '\r' || str.at(i) == '\n')
			{
				ps = KEY;
				m_list[key].push_back(listItem);
				key = "";
				listItem = "";
			}
			else if (i == str.length() - 1)
			{
				listItem.push_back(str.at(i));
				m_list[key].push_back(listItem);
			}
			else if (str.at(i) == ',')
			{
				m_list[key].push_back(listItem);
				listItem = "";
			}
			else if (str.at(i) == ';')
			{
				ps = COMMENT;
			}
			else if (str.at(i) != ' ' && str.at(i) != '\t')
			{
				listItem.push_back(str.at(i));
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

	if (m_debug)
	{
		std::unordered_map<std::string, std::string>::iterator it = m_dict.begin();
		for (; it != m_dict.end(); it++)
		{
			std::cout << "Key " << (*it).first << " Value " << (*it).second << std::endl;
		}

		std::unordered_map<std::string, std::vector<std::string>>::iterator it_list = m_list.begin();
		for (; it_list != m_list.end(); it_list++)
		{
			std::cout << "Key " << (*it_list).first << " : ";
			std::vector<std::string>::iterator it_vec = it_list->second.begin();
			for (; it_vec != it_list->second.end(); it_vec++)
			{
				std::cout << *it_vec << ' ';
			}
			std::cout << std::endl;
		}
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


int IniLoader::GetListSize(std::string key)
{
	return m_list[key].size();
}


std::string IniLoader::GetListString(std::string key, int index)
{
	return m_list[key][index];
}


int IniLoader::GetListInt(std::string key, int index)
{
	return std::stoi(m_list[key][index]);
}


float IniLoader::GetListFloat(std::string key, int index)
{
	return std::stof(m_list[key][index]);
}