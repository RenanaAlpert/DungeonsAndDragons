#pragma once
#include <array>
#include <optional>
#include <memory>
#include "Diraction.h"
#include "Group.h"
#include "Writer.h"

namespace experis
{

class Room
{
	using Diraction = detail::EnumDiractions;

public:
	Room();
	Room(const Room& a_other) = delete;
	Room(Room&& a_other) noexcept;
	Room& operator=(const Room& a_other) = delete;
	Room& operator=(Room&& a_other) noexcept;
	~Room();

	void AddRoom(Diraction a_diraction);
	bool ThereIsDoor(Diraction a_diraction) const;
	std::shared_ptr<Room> ThroughTheDoor(Diraction a_diraction) const;
	void Drow(ascii::ColoredCanvas& canvas, Writer& a_os) const;
	int GetMumber() const;

private:
	int m_numRoom;
	std::array<std::optional<std::shared_ptr<Room>>, Diraction::SIZE_OF_DIRACTIONS> m_nextRooms;
	Group m_paintRoom;
};

} // experis