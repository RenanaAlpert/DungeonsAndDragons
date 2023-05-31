#pragma once
#include <string>
#include <vector>

namespace experis
{

static const std::vector<std::string> DIRACTIONS = { "north", "east", "south", "west" };

namespace detail
{
enum EnumDiractions
{
	NORTH,
	EAST,
	SOUTH,
	WEST,
	SIZE_OF_DIRACTIONS
};
}

}