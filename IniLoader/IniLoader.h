#pragma once


#include <sstream>
#include <vector>
#include <unordered_map>


enum ParsingStatus
{
	KEY,
	VALUE,
	LIST,
	COMMENT
};


class __declspec(dllexport) IniLoader
{

public:
	IniLoader(const char* filename);

	std::string GetString(std::string key);
	int GetInt(std::string key);
	float GetFloat(std::string key);

	int GetListSize(std::string key);
	std::string GetListString(std::string key, int index);
	int GetListInt(std::string key, int index);
	float GetListFloat(std::string key, int index);

private:
	void Parse();

	std::stringstream m_buffer;
	std::unordered_map<std::string, std::string> m_dict;
	std::unordered_map<std::string, std::vector<std::string>> m_list;
};