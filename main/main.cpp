#include <iostream>
#include "Player.h"
#include "InputParser.h"
#include "Reader.h"
#include "Writer.h"
#include <sstream>

void Play(std::shared_ptr<experis::Room> a_startRoom, experis::Writer& a_out, experis::Reader& a_in)
{
	experis::Player pleyer{a_startRoom};
	std::string prompter = ">";
	std::stringstream ss{};
	ss << "You are facing " << experis::DIRACTIONS.at(pleyer.GetDiraction()) << std::endl;
	a_out.Write(ss.str());
	while(true)
	{
		a_out.Write(prompter);
		std::string action = a_in.ReadLine();
		experis::Parse(action, a_out)->Do(pleyer, a_out);
	}
}

void NetworkPlay(unsigned short a_port, std::shared_ptr<experis::Room> a_startRoom)
{
	simplenet::SimpleNetMT net{a_port};
	std::shared_ptr<simplenet::SimpleNetMT::Connection> c = 
		std::make_shared<simplenet::SimpleNetMT::Connection>(simplenet::SimpleNetMT::Connection{net.WaitForConnection()});
	try
	{
		auto [untrust_query, isHttp] = simplenet::TryReadUrlPath(*c.get());
		if(isHttp)
		{
		}
		else
		{
			experis::NetworkReader in{c};
			experis::NetworkWriter out{c};
			Play(a_startRoom, out, in);
		}
	}
	catch (const simplenet::SimpleNetMT::ConnectionClosed&)
	{
		std::cout << "connection closed\n";
	}
}

void ConsolePlay(std::shared_ptr<experis::Room> a_startRoom)
{
	experis::OstreamWriter out{std::cout};
	experis::IstreamReader in{std::cin};
	Play(a_startRoom, out, in);
}

int main(int argc, char* argv[])
{
	std::shared_ptr<experis::Room> startRoom = std::make_shared<experis::Room>();
	startRoom.get()->AddRoom(experis::detail::NORTH);
	startRoom.get()->AddRoom(experis::detail::WEST);
	if(argc == 1)
	{
		ConsolePlay(startRoom);
	}
	else if(argc == 2)
	{
		NetworkPlay(std::stoi(argv[1]), startRoom);
	}
	
}