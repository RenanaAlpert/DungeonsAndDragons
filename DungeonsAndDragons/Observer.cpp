#include "Observer.h"

namespace experis
{

PlayerObserver::PlayerObserver(Player& a_player, std::shared_ptr<experis::Writer> a_out)
	: m_player{a_player}, m_out{a_out}
{
}

void PlayerObserver::Update(const std::string& a_message) const
{
	this->m_out.get()->Write(a_message);
}

Player& PlayerObserver::GetPlayer() const
{
	return this->m_player;
}

}