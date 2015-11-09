#pragma once

#include <sstream>
#include <unordered_map>

enum ParsingStatus
{
	KEY,
	VALUE,
	COMMENT
};

class IniLoader
{

public:
	IniLoader(const char* filename);

	std::string GetString(std::string key);
	int GetInt(std::string key);
	float GetFloat(std::string key);

private:
	void Parse();

	std::stringstream m_buffer;
	std::unordered_map<std::string, std::string> m_dict;
};