#include "Room.h"
#include <cassert>

namespace experis
{

Room::Room()
	: m_nextRooms{std::nullopt, std::nullopt, std::nullopt, std::nullopt}
{
}

Room::Room(Room&& a_other) noexcept
	: m_nextRooms{std::nullopt, std::nullopt, std::nullopt, std::nullopt}
{
}

Room& Room::operator=(Room&& a_other) noexcept
{
	for(int idx = 0; idx < this->m_nextRooms.size() ; ++idx)
	{
		std::swap(this->m_nextRooms.at(idx), a_other.m_nextRooms.at(idx));
	}
	return *this;
}

Room::~Room()
{
}

void Room::AddRoom(Diraction a_diraction)
{
	this->m_nextRooms.at(a_diraction) = std::make_shared<Room>();
}

bool Room::ThereIsDoor(Diraction a_diraction) const
{
	return this->m_nextRooms.at(a_diraction).has_value();
}

std::shared_ptr<Room> Room::ThroughTheDoor(Diraction a_diraction) const
{
	assert(ThereIsDoor(a_diraction));
	return this->m_nextRooms.at(a_diraction).value();
}

}