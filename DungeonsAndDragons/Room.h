#pragma once
#include <array>
#include <optional>
#include <memory>
#include "Diraction.h"

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

private:
	std::array<std::optional<std::shared_ptr<Room>>, Diraction::SIZE_OF_DIRACTIONS> m_nextRooms;
};

} // experis