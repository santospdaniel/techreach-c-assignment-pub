#include <c-assignment/FcCommand.hpp>
#include <c-assignment/FunctionalLogger.hpp>
namespace cassign
{
	const std::string FcCommand::COMMAND_NAME = "fc";

	FcCommand::FcCommand(CommandResources* commandResources)
		: Command(COMMAND_NAME, commandResources)
	{}

	float FcCommand::process()
	{
		dynamic_cast<FunctionalLogger*>(m_commandResources->getFunctionalLogger())->writeLogFunc("Processing command.");
		float seconds = m_commandResources->getRandomSeconds(1, 3);
		m_commandResources->sleepForSeconds(seconds);
		return seconds;
	}
}