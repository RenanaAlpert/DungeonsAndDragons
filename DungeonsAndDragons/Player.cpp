#include "Player.h"
#include "Subject.h"
#include <array>
#include <sstream>

namespace experis
{

extern RoomsMap roomsMap;

static constexpr int MOVE = 1;
static constexpr std::array<char, 4> BRASH_PLAYER = {'^', '>', 'v', '<'};

Player::Player(std::shared_ptr<Room> a_startRoom, const std::string& a_name, std::shared_ptr<Writer> a_writer)
	: m_diraction{Diractions::NORTH}, m_currentRoom{a_startRoom}, m_name{a_name}
	, m_paint{BRASH_PLAYER.at(m_diraction), 8, 5, 8, 5}, m_observer{*this, a_writer}
{
	m_paint.SetBg(Shape::Color::TERMINAL_COLOR);
	m_paint.SetFg(Shape::Color::MAGENTA);
	roomsMap.Regisrer(this->m_observer);
}

Player::~Player()
{
}

void Player::Left()
{
	int newDiraction = this->m_diraction == 0 ? Diractions::SIZE_OF_DIRACTIONS - MOVE : (this->m_diraction - MOVE) % Diractions::SIZE_OF_DIRACTIONS;
	this->m_diraction = static_cast<Diractions>(newDiraction);
	this->m_paint.SetBrush(BRASH_PLAYER.at(newDiraction));
}

void Player::Right()
{
	int newDiraction = (this->m_diraction + MOVE) % Diractions::SIZE_OF_DIRACTIONS;
	this->m_diraction = static_cast<Diractions>(newDiraction);
	this->m_paint.SetBrush(BRASH_PLAYER.at(newDiraction));
}

bool Player::Walk()
{
	if(this->m_currentRoom.get()->ThereIsDoor(this->m_diraction))
	{
		//Room& r = const_cast<Room&>(this->m_currentRoom.ThroughTheDoor(this->m_diraction));
		roomsMap.Unregister(this->m_observer);
		this->m_currentRoom = this->m_currentRoom.get()->ThroughTheDoor(this->m_diraction);
		roomsMap.Regisrer(this->m_observer);
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

std::shared_ptr<Room> Player::GetRoom() const
{
	return this->m_currentRoom;
}

const std::string& Player::GetName() const
{
	return this->m_name;
}

void Player::Drow(Writer& a_os) const
{
	ascii::ColoredCanvas canvas{20, 13};
	this->m_currentRoom.get()->Drow(canvas, a_os);
	this->m_paint.Draw(canvas);
	std::stringstream paint{};
    canvas.Print(paint, ascii::ColoredCanvas::OutputPosition::CURRENT_LINE);
	a_os.Write(paint.str());
}

} // experis