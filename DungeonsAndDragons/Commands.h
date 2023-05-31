#pragma once
#include "Player.h"
#include <unordered_map>
#include <functional>
#include <iosfwd>
#include "Writer.h"

namespace experis
{

struct Command
{
	virtual void Do(Player& a_player, Writer& a_os) const = 0;
};

struct Left : public Command
{
	virtual void Do(Player& a_player, Writer& a_os) const override;
};

struct Right : public Command
{
	virtual void Do(Player& a_player, Writer& a_os) const override;
};

struct Help : public Command
{
	virtual void Do(Player& a_player, Writer& a_os) const override;
};

struct Walk : public Command
{
	virtual void Do(Player& a_player, Writer& a_os) const override;
};

namespace detail
{
	static const Left LEFT;
	static const Right RIGHT;
	static const Help HELP;
	static const Walk WALK;
}

static const std::unordered_map<std::string, const Command*> MOVE = {
	{"help", &detail::HELP},
	{"left", &detail::LEFT},
	{"right", &detail::RIGHT},
	{"walk", &detail::WALK}
};

//static const std::unordered_map<std::string, std::function<void(Player& a_player)>> MOVE = {
//	{"left",[](Player& a_player){a_player.Left();}},
//	{"right", [](Player& a_player){a_player.Right();}}
//};


}