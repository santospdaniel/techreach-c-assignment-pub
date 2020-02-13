#include <c-assignment/FunctionalLogger.hpp>
#include <sstream>
#include <regex>

namespace cassign 
{	
	FunctionalLogger::FunctionalLogger(std::ostream* outStream, std::istream* inStream)
		: Logger(outStream, inStream)
		, m_lineCount(1)
	{}

	void FunctionalLogger::writeLog(const std::string& info, const std::string& cppMethod)
	{
		Logger::writeLog(getPrefix(cppMethod, true) + " " + info);
	}

	void FunctionalLogger::fetchLogDataInto(std::ostream& outStream) const
	{
		m_inStream->clear();
		m_inStream->seekg(0, std::ios::beg);
		int lineCount = 0;
		for (std::string line; std::getline(*m_inStream, line);)
		{
			if (!(++lineCount % 2))
			{
				outStream << line << "\n";
			}
		}
		if (lineCount < 2)
		{
			outStream << "(no even lines found)\n";
		}
	}

	std::string FunctionalLogger::getPrefix(const std::string& cppMethod, const bool withLineCount)
	{
		std::ostringstream oss;
		if (withLineCount)
		{
			oss << "[" << FunctionalLogger::m_lineCount++ << "]";
		}
		oss << "[" << replaceStr(cppMethod, "cassign::", "") << "]";
		return oss.str();
	}
}