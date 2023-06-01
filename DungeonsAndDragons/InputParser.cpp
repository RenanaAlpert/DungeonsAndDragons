#include "InputParser.h"
#include <exception>

namespace experis
{
	
bool IsValid(const std::string& a_text)
{
	return experis::MOVE.count(a_text) > 0;
}

std::optional<const Command*> ParseAction(std::string& a_text, Writer& a_out)
{
	if(IsValid(a_text))
	{
		return experis::MOVE.at(a_text);
	}
	else
	{
		a_out.Write("invalid input. try again\n");
		return std::nullopt;
	}
}

bool IsDigit(std::string& a_text)
{
	for(char c : a_text)
	{
		if(!isdigit(c))
		{
			return false;
		}
	}
	return true;
}

struct InvalidPlatformExeption : public std::exception
{
	InvalidPlatformExeption(const std::string a_platform, const char* a_mes) : m_platform{a_platform}, m_mes{a_mes} {}

private:
	const std::string m_platform;
	const char* m_mes;
};

int ParsePlatform(std::string& a_text)
{
	if(a_text == "console")
	{
		return -1;
	}
	else if(IsDigit(a_text))
	{
		return std::stoi(a_text);
	}
	else
	{
		throw InvalidPlatformExeption{a_text, "This system not Support this platform"};
	}
}

} // experis