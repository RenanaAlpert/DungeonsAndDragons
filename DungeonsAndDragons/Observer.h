#pragma once
#include <string>
#include "Writer.h"

namespace experis
{

class Player;

class PlayerObserver
{

public:
	PlayerObserver() = delete;
	PlayerObserver(Player& a_player, std::shared_ptr<experis::Writer> a_out);
	PlayerObserver(const PlayerObserver& a_other) = delete;
	PlayerObserver(PlayerObserver&& a_other) = delete;
	PlayerObserver& operator=(const PlayerObserver& a_other) = delete;
	PlayerObserver& operator=(PlayerObserver&& a_other) = delete;
	~PlayerObserver() = default;

	void Update(const std::string& a_message) const;
	Player& GetPlayer() const;

private:
	Player& m_player;
	std::shared_ptr<experis::Writer> m_out;
};

} // experis