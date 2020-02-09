#include <c-assignment/Loader.hpp>
#include <c-assignment/LoadersProcessor.hpp>
#include <c-assignment/Processor.hpp>
#include <c-assignment/FcCommand.hpp>
#include <c-assignment/OutCommand.hpp>
#include <c-assignment/RdtCommand.hpp>
#include <c-assignment/RfcCommand.hpp>
#include <sstream>

namespace cassign
{
	const std::string Loader::MESSAGE_COMMAND_PROCESSED = "Command processing took: ";
	const std::string Loader::MESSAGE_PROCESSING_UNITS = " seconds.";
	const std::string Loader::MESSAGE_UNKNOWN_COMMAND = "Unknown command!";
	const std::string Loader::MESSAGE_PROCESSOR_BUSY = "Processor is currently busy.";

	Loader::Loader(cassign::LoadersProcessor* loadersProcessor)
		: m_loadersProcessor(loadersProcessor)
	{
		m_commands.push_back(std::make_shared<FcCommand>(FcCommand(dynamic_cast<CommandResources*>(m_loadersProcessor))));
		m_commands.push_back(std::make_shared<OutCommand>(OutCommand(dynamic_cast<CommandResources*>(m_loadersProcessor))));
		m_commands.push_back(std::make_shared<RdtCommand>(RdtCommand(dynamic_cast<CommandResources*>(m_loadersProcessor))));
		m_commands.push_back(std::make_shared<RfcCommand>(RfcCommand(dynamic_cast<CommandResources*>(m_loadersProcessor))));
	}

	void Loader::initialize()
	{
		for each(std::shared_ptr<Command> command in m_commands)
		{
			command->initialize();
		}
	}

	void Loader::promptUser(std::istream* istream)
	{
		std::string userInput;
		*istream >> userInput;
		if (!userInput.empty()) //improve local CPU cache as probably the user input something.
		{
			cassign::ProcResult procResult = m_loadersProcessor->process(userInput);
			switch (procResult.procStatus)
			{
			case ProcStatus::PROCRESULT_UNKNOWN_CMD:
				dynamic_cast<DateLogger*>(m_loadersProcessor->getDateLogger())->writeLog(MESSAGE_UNKNOWN_COMMAND);
				dynamic_cast<OutLogger*>(m_loadersProcessor->getOutLogger())->writeLogFunc(MESSAGE_UNKNOWN_COMMAND);
				break;
			case ProcStatus::PROCRESULT_BUSY:
				dynamic_cast<OutLogger*>(m_loadersProcessor->getOutLogger())->writeLogFunc(MESSAGE_PROCESSOR_BUSY);
				break;
			case ProcStatus::PROCRESULT_PROCESSING:
				break;
			default:
				throw std::exception("Requesting to process a command resulted in an unknown processor result!");
			}
		}
	}

	void Loader::processCallback(ProcResult procResult) const
	{
		if (procResult.procStatus == ProcStatus::PROCRESULT_PROCESSED)
		{
			if (procResult.procTime > 0)
			{
				std::ostringstream oss;
				oss.precision(2);
				oss << MESSAGE_COMMAND_PROCESSED << std::fixed << procResult.procTime << MESSAGE_PROCESSING_UNITS;
				dynamic_cast<FunctionalLogger*>(m_loadersProcessor->getFunctionalLogger())->writeLogFunc(oss.str());
				dynamic_cast<OutLogger*>(m_loadersProcessor->getOutLogger())->writeLogFunc(oss.str());
			}
		}
		else
		{
			throw std::exception("Unexpected command process status in callback.");
		}
	}
}
