#include "Reader.h"
#include <istream>

namespace experis
{

IstreamReader::IstreamReader(std::istream& a_in)
	: m_in(a_in)
{
}

std::string IstreamReader::ReadLine()
{
	std::string line{};
	std::getline(this->m_in, line);
	return line;
}

NetworkReader::NetworkReader(std::shared_ptr<simplenet::SimpleNetMT::Connection> a_connection)
	: m_connection{a_connection}
{
}

std::string NetworkReader::ReadLine()
{
	return this->m_connection.get()->ReadLine();
	//auto [untrust_query, isHttp] = simplenet::TryReadUrlPath(*this->m_connection.get());
	//return untrust_query;
}

} // experis