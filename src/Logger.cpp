#include <c-assignment/Logger.hpp>
#include <sstream>

namespace cassign {

	Logger::Logger(std::ostream* outStream, std::istream* inStream)
		: m_outStream(outStream)
		, m_inStream(inStream)
	{}

	void Logger::writeLog(const std::string& info)
	{
		m_writeMutex.lock();
		*m_outStream << info << "\n";
		m_outStream->flush();
		m_writeMutex.unlock();
	}
}
