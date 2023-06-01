#include "Room.h"
#include <cassert>
#include "ShapesFile.h"
#include "colored_canvas.hpp"
#include <iostream>
#include <sstream>

namespace experis
{

Room::Room()
	: m_nextRooms{std::nullopt, std::nullopt, std::nullopt, std::nullopt}, m_paintRoom{LoadPainting("room.txt")}
{
}

Room::Room(Room&& a_other) noexcept
	: m_nextRooms{a_other.m_nextRooms.at(0), a_other.m_nextRooms.at(1), a_other.m_nextRooms.at(2), a_other.m_nextRooms.at(3)}
	, m_paintRoom{a_other.m_paintRoom}
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
	Shape* door = this->m_paintRoom.At(this->m_paintRoom.Size() - (Diraction::SIZE_OF_DIRACTIONS - a_diraction));
	door->SetFg(Shape::Color::GREEN);
	assert(this->m_nextRooms.at(a_diraction).has_value());
	int opositeDiraction = (a_diraction + 2) % Diraction::SIZE_OF_DIRACTIONS;
	this->m_nextRooms.at(a_diraction).value().get()->m_nextRooms.at(opositeDiraction) = std::shared_ptr<Room>(this);
	door = this->m_nextRooms.at(a_diraction).value().get()
		->m_paintRoom.At(this->m_paintRoom.Size() - (Diraction::SIZE_OF_DIRACTIONS - opositeDiraction));
	door->SetFg(Shape::Color::GREEN);
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

void Room::Drow(ascii::ColoredCanvas& a_canvas, Writer& a_os) const
{
    this->m_paintRoom.Draw(a_canvas);
	std::stringstream paint{};
   /* a_canvas.Print(paint, ascii::ColoredCanvas::OutputPosition::CURRENT_LINE);
	a_os.Write(paint.str());*/
}

} // experis