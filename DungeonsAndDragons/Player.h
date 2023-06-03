#pragma once
#include "Diraction.h"
#include "Room.h"
#include "Line.h"
#include "Observer.h"

namespace experis
{

class Player
{
	using Diractions = detail::EnumDiractions;
public:
	Player(std::shared_ptr<Room> a_startRoom, const std::string& a_name, std::shared_ptr<Writer> a_writer);
	Player(const Player& a_other) = delete;
	Player(Player&& a_other) = delete;
	Player operator=(const Player& a_other) = delete;
	Player operator=(Player&& a_other) = delete;
	~Player();

	void Left();
	void Right();
	bool Walk();
	Diractions GetDiraction() const;
	std::shared_ptr<Room> GetRoom() const;
	const std::string& GetName() const;
	void Drow(Writer& a_os) const;

private:
	std::shared_ptr<Room> m_currentRoom;
	Diractions m_diraction;
	std::string m_name;
	Line m_paint;
	PlayerObserver m_observer;
};

} // experis