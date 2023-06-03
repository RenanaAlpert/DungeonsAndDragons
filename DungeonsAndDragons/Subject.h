#pragma once
#include "Observer.h"
#include "Room.h"
#include <unordered_map>
#include <vector>

namespace experis
{
class RoomsMap
{
public:
	RoomsMap();
	RoomsMap(const RoomsMap& a_other) = delete;
	RoomsMap(RoomsMap&& a_other) = delete;
	RoomsMap& operator=(const RoomsMap& a_other) = delete;
	RoomsMap& operator=(RoomsMap&& a_other) = delete;
	~RoomsMap() = default;

	void Regisrer(PlayerObserver& a_observer);
	void Unregister(const PlayerObserver& a_observer);
	void Notify(const PlayerObserver& a_observer, const std::string& a_message);

private:
	using numRoom = int;

	std::unordered_map<numRoom, std::vector<PlayerObserver*>> m_roomsMap;
};

} // experis