#pragma once
#include <c-assignment/Command.hpp>
#include <c-assignment/CommandResources.hpp>

namespace cassign
{
	/*
	Implements the requirement about the "rdt" command.
	*/
	class RdtCommand : public Command
	{
	public:
		RdtCommand(CommandResources* commandResources);
		/*
		Inherited from Command.
		Reads the information from the DateLogger and outputs it to the console via CommandResources.
		*/
		float process() override;
	private:
		static const std::string COMMAND_NAME;
	};
}