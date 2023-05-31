#include "InputParser.h"

namespace experis
{
	
bool IsValid(const std::string& a_text)
{
	return experis::MOVE.count(a_text) > 0;
}

const Command* Parse(std::string& a_text, Writer& a_out)
{
	while (true)
	{
		if(IsValid(a_text))
		{
			return experis::MOVE.at(a_text);
		}
		else
		{
			a_out.Write("invalid input. try again\n> ");
		}
	}
}

} // experis