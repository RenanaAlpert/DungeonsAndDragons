#include <iostream>
#include "Player.h"
#include "InputParser.h"
#include "Reader.h"
#include "Writer.h"
#include <sstream>
#include <thread>
#include "Subject.h"

namespace experis
{

RoomsMap roomsMap{};

void Play(std::shared_ptr<experis::Room> a_startRoom, std::shared_ptr<experis::Writer> a_out, std::unique_ptr<experis::Reader> a_in)
{
	std::string prompter = ">";
	std::stringstream ss{};
	ss << "welcom to the game :) enter your name" << std::endl;
	a_out->Write(ss.str());
	std::string name = a_in->ReadLine();
	experis::Player player{a_startRoom, name, a_out};
	player.Drow(*a_out);
	ss = {};
	ss << "Welcome " << name << " :) you can start play ;)" << std::endl;
	ss << "You are facing " << experis::DIRACTIONS.at(player.GetDiraction()) << std::endl;
	a_out->Write(ss.str());
	while(true)
	{
		a_out->Write(prompter);
		std::string action = a_in->ReadLine();
		std::optional<const experis::Command*> cmd = experis::ParseAction(action, *a_out);
		if(cmd.has_value())
		{
			cmd.value()->Do(player, *a_out);
		}
		//experis::ParseAction(action, a_out)->Do(player, a_out);
	}
}

void NetworkPlay(unsigned short a_port, std::shared_ptr<experis::Room> a_startRoom)
{
	simplenet::SimpleNetMT net{a_port};
	while (true)
	{
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
				//TODO treat memory leake
				new std::jthread{&Play, a_startRoom
					, std::make_shared<experis::NetworkWriter>(c), std::make_unique<experis::NetworkReader>(c)};
				//Play(a_startRoom, out, in);
			}
		}
		catch (const simplenet::SimpleNetMT::ConnectionClosed&)
		{
			std::cout << "connection closed\n";
		}
	}
}

void ConsolePlay(std::shared_ptr<experis::Room> a_startRoom)
{
	Play(a_startRoom, std::make_unique<experis::OstreamWriter>(std::cout), std::make_unique<experis::IstreamReader>(std::cin));
}

} // experis

int main(int argc, char* argv[])
{
	std::shared_ptr<experis::Room> startRoom = std::make_shared<experis::Room>();
	startRoom.get()->AddRoom(experis::detail::NORTH);
	startRoom.get()->AddRoom(experis::detail::WEST);

	std::vector<std::thread> players;
	if(argc == 1)
	{
		players.push_back(std::thread{&experis::ConsolePlay, startRoom});
	}
	else
	{
		for(int idx = 0 ; idx < argc - 1 ; ++idx)
		{
			std::string untrust_inputPlatrorm = argv[idx + 1];
			int port = experis::ParsePlatform(untrust_inputPlatrorm);
			if(port < 0)
			{
				players.push_back(std::thread{&experis::ConsolePlay, startRoom});
			}
			else
			{
				players.push_back(std::thread{&experis::NetworkPlay, port, startRoom});
			}
		}
	}

	for(int idx = 0 ; idx < players.size() ; ++idx)
	{
		players.at(idx).join();
	}
}