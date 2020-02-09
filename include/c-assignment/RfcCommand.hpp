#pragma once
#include <c-assignment/Command.hpp>
#include <c-assignment/CommandResources.hpp>

namespace cassign
{
	/*
	Implements the requirement about the "rfc" command.
	*/
	class RfcCommand : public Command
	{
	public:
		RfcCommand(CommandResources* commandResources);
		/*
		Inherited from Command.
		Reads the information from the DateLogger and outputs it to the console via CommandResources.
		*/
		float process() override;
	private:
		static const std::string COMMAND_NAME;
	};
}