#pragma once
#include <string>

namespace cassign
{
	struct ProcResult; //Forward declaration. This is defined in Processor.
	class Logger; //Forward declaration. This is imported in the Processor.

	/*
	Loader's processor is a stripped down version of the Processor: represents the Processor in the Loader's perspective. 
	This way the Loader will not have full access to all the Processor methods, but just to the ones it really needs.
	*/
	class LoadersProcessor
	{
	public:
		//Processing commands is a resource that is available to the Loader.
		virtual ProcResult process(const std::string& command) = 0;
		//DateLogger is a resource that is available to the Loader.
		virtual Logger* getDateLogger() const = 0;
		//FunctionalLogger is a resource that is available to the Loader.
		virtual Logger* getFunctionalLogger() const = 0;
		//OutLogger is a resource that is available to the Loader.
		virtual Logger* getOutLogger() const = 0;
	};
}
