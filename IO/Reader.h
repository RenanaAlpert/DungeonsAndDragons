#pragma once
#include <string>
#include <iosfwd>
#include "SimpleNetMT.h"
#include "UrlPathReader.h"

namespace experis
{

class Reader
{
public:
	virtual std::string ReadLine() = 0;
};

class IstreamReader : public Reader
{
public:
	IstreamReader() = delete;
	IstreamReader(std::istream& a_in);
	IstreamReader(const IstreamReader& a_other) = delete;
	IstreamReader operator=(const IstreamReader& a_other) = delete;
	virtual ~IstreamReader() = default;

	virtual std::string ReadLine() override;

private:
	std::istream& m_in;
};

class NetworkReader : public Reader
{
public:
	NetworkReader() = delete;
	NetworkReader(std::shared_ptr<simplenet::SimpleNetMT::Connection> a_connection);
	NetworkReader(const NetworkReader& a_other) = delete;
	NetworkReader operator=(const NetworkReader& a_other) = delete;
	virtual ~NetworkReader() = default;

	virtual std::string ReadLine() override;
private:
	std::shared_ptr<simplenet::SimpleNetMT::Connection> m_connection;
};

} // experis