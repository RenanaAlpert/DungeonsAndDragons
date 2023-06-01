#pragma once
#include "Commands.h"
#include "Writer.h"
#include <optional>

namespace experis
{

std::optional<const Command*> ParseAction(std::string& a_text, Writer& a_out);
int ParsePlatform(std::string& a_text);

} // experis