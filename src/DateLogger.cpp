#include <c-assignment/DateLogger.hpp>
#include <ctime>
#include <iostream>

namespace cassign
{
	const char* DateLogger::m_dateTimeFormat = "[%D-%T]";
	const char* DateLogger::m_timeFormat = "[%T]";

	DateLogger::DateLogger(std::ostream* outStream, std::istream* inStream)
		: Logger::Logger(outStream, inStream)
	{}

	void DateLogger::writeLog(const std::string& info)
	{
		Logger::writeLog(getPrefix() + " " + info);
	}

	void DateLogger::fetchLogDataInto(std::ostream& outStream) const
	{
		m_inStream->clear();
		m_inStream->seekg(0, std::ios::beg);
		int lineCount = 0;
		for (std::string line; std::getline(*m_inStream, line);)
		{
			++lineCount;
		}
		outStream << lineCount << "\n";
	}

	std::string DateLogger::getPrefix(bool withDate) const
	{
		char buffer[30];
		std::string prefix = this->formatTime(buffer, sizeof(buffer), this->getCurrentLocalTime(), withDate);
		return prefix;
	}

	tm DateLogger::getCurrentLocalTime() const
	{
		time_t currentTime = std::time(0);
		tm currentLocalTime = *std::localtime(&currentTime);
		return currentLocalTime;
	}

	char* DateLogger::formatTime(char* buffer, size_t buffSize, const tm& time, bool withDate) const
	{
		std::strftime(buffer, buffSize, withDate ? m_dateTimeFormat : m_timeFormat, &time);
		return buffer;
	}
}
