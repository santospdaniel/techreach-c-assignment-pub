#pragma once
#include <c-assignment/Initializer.hpp>
#include <string>
namespace cassign 
{
	class CommandResources; //Forward declaration. Command uses CommandResources, the same way CommandResources uses Command.

	/*
	Represents an abstract command that can be processed via calling the process method, that is implementation specific.
	The command is identified by a name, which can be used in a program to uniquely identify it among other commands. An usage example is to invoke it from a prompt line feed.
	The command is supplied with resources to make them available to the process method.
	*/
	class Command : public Initializer
	{
	public:
		//The command is identified by a name and is supplied with resources that may be used inside the process method.
		Command(const std::string name, CommandResources* commandResources);
		//Inherited from Initializer. By initializing a command it will become allowed to use the resources.
		void initialize() override;
		/*
		Returns the command name. This name is the unique command name inside a program. 
		For instance, it can be used to invoke this command via a prompt line feed.
		*/
		const std::string getName() const;
		/*
		Process the command. This means the command gets executed, eventually consuming the CommandResources provided in the constructor.
		The processing time (the elapsed time between the start and the end of the processing) is returned by this method.
		*/
		virtual float process() = 0;

	protected:
		CommandResources* m_commandResources;
		const std::string m_name;
	};
}