#include "Writer.h"
#include <ostream>

namespace experis
{

OstreamWriter::OstreamWriter(std::ostream& a_out)
	: m_out(a_out)
{
}

void OstreamWriter::Write(const std::string& a_text)
{
	this->m_out << a_text;
}

NetworkWriter::NetworkWriter(std::shared_ptr<simplenet::SimpleNetMT::Connection> a_connection)
	: m_connection{a_connection}
{
}

NetworkWriter::NetworkWriter(NetworkWriter&& a_other) noexcept
	:m_connection{a_other.m_connection}
{
}

void NetworkWriter::Write(const std::string& a_text)
{
	this->m_connection.get()->Write(a_text);
}

} // experis