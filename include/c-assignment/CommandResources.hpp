#pragma once
#include <c-assignment/Logger.hpp>
namespace cassign
{
	class Command; //Forward declaration. CommandResources uses Command, the same way Command uses CommandResources.

	/*
	Contains all the resources available to an allowed command.
	These resources are supposed to be consumed inside the command's process method, so it can do whatever it is supposed to do, not allowing further access to other resources of the program for security and stability sake.
	In order for a command to become allowed it is necessary to add it via the addAllowedCommand method.
	*/
	class CommandResources
	{
	public:
		//DateLogger is a resource that can be used by the allowed commands.
		virtual Logger* getDateLogger() const = 0;
		//FunctionalLogger is a resource that can be used by the allowed commands.
		virtual Logger* getFunctionalLogger() const = 0;
		//OutLogger is a resource that can be used by the allowed commands.
		virtual Logger* getOutLogger() const = 0;
		//Getting random seconds is a resource that can be used by the allowed commands.
		virtual float getRandomSeconds(const size_t minSeconds, const size_t maxSeconds) = 0;
		//Sleeping for some seconds is a resource that can be used by the allowed commands.
		virtual void sleepForSeconds(const float seconds) const = 0;
		//Adds a command to the allowed command list. Only allowed commands can access the resources.
		virtual void addAllowedCommand(Command* command) = 0;

	};
}
