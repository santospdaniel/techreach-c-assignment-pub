#include <c-assignment/Processor.hpp>
#include <c-assignment/Loader.hpp>
#include <time.h>

namespace cassign
{
	Processor::Processor(cassign::DateLogger* dateLogger, cassign::FunctionalLogger* functionalLogger, cassign::OutLogger* outLogger)
		:m_dateLogger(dateLogger)
		, m_functionalLogger(functionalLogger)
		, m_outLogger(outLogger)
		, m_processorAvailability(ProcessorAvailability::PROCESSOR_READY_TO_PROCESS)
	{}

	Logger* Processor::getDateLogger() const
	{
		return m_dateLogger;
	}

	Logger* Processor::getFunctionalLogger() const
	{
		return m_functionalLogger;
	}

	Logger* Processor::getOutLogger() const
	{
		return (OutLogger*) m_outLogger;
	}

	float Processor::getRandomSeconds(const size_t minSeconds, const size_t maxSeconds)
	{
		std::uniform_real_distribution<float> distrib(static_cast<float>(minSeconds), static_cast<float>(maxSeconds));
		float random = distrib(m_dre);
		return random;
	}

	void Processor::sleepForSeconds(const float seconds) const
	{
		const size_t milliseconds = static_cast<size_t>(seconds * 1000);
		std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
	}

	void Processor::addAllowedCommand(Command* command)
	{
		m_allowedCommands[command->getName()] = command;
	}

	ProcResult Processor::process(const std::string& command)
	{
		auto commandIterator = m_allowedCommands.find(command);
		if (commandIterator != m_allowedCommands.end())
		{
			Command* command = commandIterator->second;
			switch (m_processorAvailability)
			{
			case ProcessorAvailability::PROCESSOR_READY_TO_PROCESS:
			{
				m_processorAvailability = ProcessorAvailability::PROCESSOR_BUSY;
				std::thread processCommandThread(
					[=]() {
						float procTime = command->process();
						if (m_processedCallback)
						{
							m_processedCallback(ProcResult(ProcStatus::PROCRESULT_PROCESSED, procTime));
						}
						m_processorAvailability = ProcessorAvailability::PROCESSOR_READY_TO_PROCESS;
					}
				);
				processCommandThread.detach();
				return ProcResult(ProcStatus::PROCRESULT_PROCESSING, 0);
			}
			case ProcessorAvailability::PROCESSOR_BUSY:
				return ProcResult(ProcStatus::PROCRESULT_BUSY, 0);
			default:
				throw std::exception("Unknow processor availability state.");
			}
		}
		else
		{
			return ProcResult(ProcStatus::PROCRESULT_UNKNOWN_CMD, 0);
		}
	}

	void Processor::setProcessedCallback(std::function<void(ProcResult)> processedCallback)
	{
		if (!m_processedCallback)
		{
			m_processedCallback = processedCallback;
		}
		else
		{
			throw std::exception("The processor already has a callback defined.");
		}
	}

}

