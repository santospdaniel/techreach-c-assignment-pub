#include <c-assignment/RdtCommand.hpp>
#include <c-assignment/DateLogger.hpp>
namespace cassign
{
	const std::string RdtCommand::COMMAND_NAME = "rdt";

	RdtCommand::RdtCommand(CommandResources* commandResources)
		: Command(COMMAND_NAME, commandResources)
	{}

	float RdtCommand::process()
	{
		dynamic_cast<DateLogger*>(m_commandResources->getDateLogger())->fetchLogDataInto(std::cout);
		return 0.0f;
	}
}