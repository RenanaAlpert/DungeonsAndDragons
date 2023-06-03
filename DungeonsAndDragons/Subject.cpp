#include "Subject.h"
#include <sstream>
#include <algorithm>
#include "Player.h"

namespace experis
{

RoomsMap::RoomsMap()
	: m_roomsMap{}
{
}

void RoomsMap::Regisrer(PlayerObserver& a_observer)
{
	int room = a_observer.GetPlayer().GetRoom().get()->GetMumber();
	if(this->m_roomsMap.count(room) == 0)
	{
		this->m_roomsMap.insert({room, {}});
	}
	this->m_roomsMap[room].push_back(&a_observer);

	std::stringstream message{};
	message << a_observer.GetPlayer().GetName() << " has enter to this room\n>";
	Notify(a_observer, message.str());
	/*for(PlayerObserver* player : this->m_roomsMap[room])
	{
		std::stringstream message{};
		message << a_observer.GetPlayer().GetName() << " has enter to this room\n>";
		player->Update(message.str());
	}*/
}

void RoomsMap::Unregister(const PlayerObserver& a_observer)
{
	int room = a_observer.GetPlayer().GetRoom().get()->GetMumber();
	this->m_roomsMap[room].erase(std::remove(this->m_roomsMap[room].begin(), this->m_roomsMap[room].end(), &a_observer));

	std::stringstream message{};
	message << a_observer.GetPlayer().GetName() << " has left this room\n>";
	Notify(a_observer, message.str());
	/*for(PlayerObserver* player : this->m_roomsMap[room])
	{
		if(player != &a_observer)
		{
			std::stringstream message{};
			message << a_observer.GetPlayer().GetName() << " has left this room\n>";
			player->Update(message.str());
		}
	}*/
}

void RoomsMap::Notify(const PlayerObserver& a_observer, const std::string& a_message)
{
	int room = a_observer.GetPlayer().GetRoom().get()->GetMumber();
	for(PlayerObserver* player : this->m_roomsMap[room])
	{
		if(player != &a_observer)
		{
			player->Update(a_message);
		}
	}
}

}