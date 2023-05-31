#pragma once
#include "Commands.h"
#include "Writer.h"

namespace experis
{

const Command* Parse(std::string& a_text, Writer& a_out);

} // experis