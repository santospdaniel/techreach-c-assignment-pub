#include <c-assignment/OutCommand.hpp>
#include <c-assignment/OutLogger.hpp>
namespace cassign
{
	const std::string OutCommand::COMMAND_NAME = "out";

	OutCommand::OutCommand(CommandResources* commandResources)
		: Command(COMMAND_NAME, commandResources)
	{}

	float OutCommand::process()
	{
		dynamic_cast<OutLogger*>(m_commandResources->getOutLogger())->writeLogFunc("Processing command.");
		float seconds = m_commandResources->getRandomSeconds(1, 3);
		m_commandResources->sleepForSeconds(seconds);
		return seconds;
	}
}