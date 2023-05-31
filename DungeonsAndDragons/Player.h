#pragma once
#include "Diraction.h"
#include "Room.h"

namespace experis
{

class Player
{
	using Diractions = detail::EnumDiractions;
public:
	Player(std::shared_ptr<Room> a_startRoom);
	Player(const Player& a_other) = delete;
	Player(Player&& a_other) = delete;
	Player operator=(const Player& a_other) = delete;
	Player operator=(Player&& a_other) = delete;
	~Player();

	void Left();
	void Right();
	bool Walk();
	Diractions GetDiraction() const;

private:
	std::shared_ptr<Room> m_currentRoom;
	Diractions m_diraction;
};

} // experis