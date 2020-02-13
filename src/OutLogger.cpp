#include <c-assignment/OutLogger.hpp>
#include <sstream>
#include <regex>

namespace cassign
{	
	OutLogger::OutLogger(std::ostream* outStream)
		: DateLogger(nullptr, nullptr) //virtual public. No need for the outstream, because...
		, FunctionalLogger(nullptr, nullptr) //virtual public. No need for the outstream, because...
		, Logger(outStream, nullptr) //... super class needs to be constructed here, passing the outstream directly to it.
	{}

	void OutLogger::writeLog(const std::string& info)
	{
		Logger::writeLog(info);
	}

	void OutLogger::writeLog(const std::string& info, const std::string& cppMethod)
	{
		OutLogger::writeLog(OutLogger::getPrefix(cppMethod) + " " + info);
	}

	void OutLogger::fetchLogDataInto(std::ostream& outstream) const
	{}

	std::string OutLogger::getPrefix(const std::string& cppMethod)
	{
		std::ostringstream oss;
		oss << DateLogger::getPrefix(false) << FunctionalLogger::getPrefix(cppMethod, false);
		return oss.str();
	}
};