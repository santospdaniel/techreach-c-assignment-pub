#include <c-assignment/FileStreamsProvider.hpp>
#include <sstream>

namespace cassign
{
	FileStreamsProvider::FileStreamsProvider(const char* logFilePath)
		:m_logFilePath(logFilePath)
	{}

	void FileStreamsProvider::initialize()
	{
		m_logFileOut.open(m_logFilePath);
		m_logFileIn.open(m_logFilePath);
	}

	std::ostream* FileStreamsProvider::getOutStream()
	{
		if (!m_logFileOut.is_open())
		{
			std::ostringstream message;
			message << "Couldn't open '" << m_logFilePath << "' for writing.";
			throw std::exception(message.str().c_str());
		}
		return &m_logFileOut;
	}

	std::istream* FileStreamsProvider::getInStream()
	{
		if (!m_logFileIn.is_open())
		{
			std::ostringstream message;
			message << "Couldn't open '" << m_logFilePath << "' for reading.";
			throw std::exception(message.str().c_str());
		}
		return &m_logFileIn;
	}
}

