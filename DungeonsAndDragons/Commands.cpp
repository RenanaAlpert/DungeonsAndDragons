#include "Commands.h"
#include <sstream>

namespace experis
{

void Left::Do(Player& a_player, Writer& a_os) const 
{
	a_player.Left();
	std::stringstream message;
	message << "You are facing " << experis::DIRACTIONS.at(a_player.GetDiraction()) << std::endl;
	a_os.Write(message.str());
}

void Right::Do(Player& a_player, Writer& a_os) const 
{
	a_player.Right();
	std::stringstream message;
	message << "You are facing " << experis::DIRACTIONS.at(a_player.GetDiraction()) << std::endl;
	a_os.Write(message.str());
}

void Help::Do(Player& a_player, Writer& a_os) const  
{
	std::stringstream message;
	for(auto cmd : MOVE)
	{
		message << cmd.first << "\n";
	}
	a_os.Write(message.str());
}

void Walk::Do(Player& a_player, Writer& a_os) const  
{
	if(a_player.Walk())
	{
		a_os.Write("chenge roon complite\n");
	}
	else
	{
		a_os.Write("can't go this diraction. try again\n");
	}
}

} // experis