#include <c-assignment/RfcCommand.hpp>
#include <c-assignment/FunctionalLogger.hpp>
namespace cassign
{
	const std::string RfcCommand::COMMAND_NAME = "rfc";

	RfcCommand::RfcCommand(CommandResources* commandResources)
		: Command(COMMAND_NAME, commandResources)
	{}

	float RfcCommand::process()
	{
		dynamic_cast<FunctionalLogger*>(m_commandResources->getFunctionalLogger())->fetchLogDataInto(std::cout);
		return 0.0f;
	}
}