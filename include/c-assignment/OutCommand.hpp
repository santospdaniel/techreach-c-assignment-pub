#pragma once
#include <c-assignment/Command.hpp>
#include <c-assignment/CommandResources.hpp>

namespace cassign
{
	/*
	Implements the requirement about the "out" command.
	*/
	class OutCommand : public Command
	{
	public:
		OutCommand(CommandResources* commandResources);
		/*
		Inherited from Command.
		Calls the process data simulation method from Processor via CommandResources.
		Logs this process event using the OutLogger, once again via CommandResources.
		*/
		float process() override;
	private:
		static const std::string COMMAND_NAME;
	};
}