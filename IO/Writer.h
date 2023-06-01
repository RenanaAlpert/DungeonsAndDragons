#pragma once
#include <string>
#include <iosfwd>
#include "SimpleNetMT.h"
#include "UrlPathReader.h"

namespace experis
{

class Writer
{
public:
	virtual void Write(const std::string& a_text) = 0;
};

class OstreamWriter : public Writer
{
public:
	OstreamWriter() = delete;
	OstreamWriter(std::ostream& a_out);
	OstreamWriter(const OstreamWriter& a_other) = delete;
	OstreamWriter operator=(const OstreamWriter& a_other) = delete;
	virtual ~OstreamWriter() = default;

	virtual void Write(const std::string& a_text) override;

private:
	std::ostream& m_out;
};

class NetworkWriter : public Writer
{
public:
	NetworkWriter() = delete;
	NetworkWriter(std::shared_ptr<simplenet::SimpleNetMT::Connection> a_connection);
	NetworkWriter(const NetworkWriter& a_other) = delete;
	NetworkWriter(NetworkWriter&& a_other) noexcept;
	NetworkWriter operator=(const NetworkWriter& a_other) = delete;
	virtual ~NetworkWriter() = default;

	virtual void Write(const std::string& a_text) override;

private:
	std::shared_ptr<simplenet::SimpleNetMT::Connection> m_connection;
};

} // experis