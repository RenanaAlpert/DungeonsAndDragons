#include "Player.h"

namespace experis
{

static constexpr int MOVE = 1;

Player::Player(std::shared_ptr<Room> a_startRoom)
	: m_diraction{Diractions::NORTH}, m_currentRoom{a_startRoom}
{
}

Player::~Player()
{
}

void Player::Left()
{
	int newDiraction = this->m_diraction == 0 ? Diractions::SIZE_OF_DIRACTIONS - MOVE : (this->m_diraction - MOVE) % Diractions::SIZE_OF_DIRACTIONS;
	this->m_diraction = static_cast<Diractions>(newDiraction);
}

void Player::Right()
{
	int newDiraction = (this->m_diraction + MOVE) % Diractions::SIZE_OF_DIRACTIONS;
	this->m_diraction = static_cast<Diractions>(newDiraction);
}

bool Player::Walk()
{
	if(this->m_currentRoom.get()->ThereIsDoor(this->m_diraction))
	{
		//Room& r = const_cast<Room&>(this->m_currentRoom.ThroughTheDoor(this->m_diraction));
		//this->m_currentRoom = const_cast<Room&>(this->m_currentRoom.get()->ThroughTheDoor(this->m_diraction));
		return true;
	}
	else
	{
		return false;
	}
}

Player::Diractions Player::GetDiraction() const
{
	return this->m_diraction;
}

} // experis