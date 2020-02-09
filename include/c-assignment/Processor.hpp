#pragma once
#include <c-assignment/LoadersProcessor.hpp> //Read as Loader's processor 
#include <c-assignment/CommandResources.hpp>
#include <c-assignment/Initializer.hpp>
#include <c-assignment/Command.hpp>
#include <c-assignment/DateLogger.hpp>
#include <c-assignment/FunctionalLogger.hpp>
#include <c-assignment/OutLogger.hpp>
#include <map>
#include <functional>
#include <random>

namespace cassign
{
	/*
	Result of processing a command:
	- PROCRESULT_UNKNOWN_CMD: means that the command is unknown. Mistyped command by the user? Command not initialized?
	- PROCRESULT_BUSY: means that the processor is processing already a command and it didn't finish yet at the time that there is an attempt to process another.
	- PROCRESULT_PROCESSING: means that the processor requested a command to process with success.
	- PROCRESULT_PROCESSED: means that the command process has finished with success.
	- PROCRESULT_ERROR: means that the command process has finished, but with an error (not implemented for this exercise).
	*/
	enum class ProcStatus
	{
		PROCRESULT_UNKNOWN_CMD,
		PROCRESULT_BUSY,
		PROCRESULT_PROCESSING,
		PROCRESULT_PROCESSED
	};

	/*
	Holds the process status and the processing time.
	The processing time is always zero for the statuses: PROCRESULT_UNKNOWN_CMD, PROCRESULT_BUSY, PROCRESULT_PROCESSING.
	The processing time represents the time a command took to process and is only available for the status PROCRESULT_PROCESSED.
	*/
	struct ProcResult
	{
		ProcResult(ProcStatus _procStatus, float _procTime)
			: procStatus(_procStatus)
			, procTime(_procTime)
		{}

		ProcStatus procStatus;
		float procTime;
	};

	enum class ProcessorAvailability {
		PROCESSOR_BUSY,
		PROCESSOR_READY_TO_PROCESS
	};

	class Processor : public LoadersProcessor, public CommandResources
	{
	public:
		/*
		Constructs the processor, giving it the resources needed for command processing.
		*/
		Processor(cassign::DateLogger* dateLogger, cassign::FunctionalLogger* functionalLogger, cassign::OutLogger* outLogger);
		//Inherited from both CommandResources and LoadersProcessor.
		Logger* getDateLogger() const override;
		//Inherited from both CommandResources and LoadersProcessor.
		Logger* getFunctionalLogger() const override;
		//Inherited from both CommandResources and LoadersProcessor.
		Logger* getOutLogger() const override;
		//Inherited from CommandResources.
		float getRandomSeconds(const size_t minSeconds, const size_t maxSeconds) override;
		//Inherited from CommandResources.
		void sleepForSeconds(const float seconds) const override;
		//Inherited from CommandResources.
		void addAllowedCommand(Command* command) override;
		/*
		Inherited from LoadersProcessor.
		Processes a command asynchronously.
		It returns synchronously and immediately a processing result. Those results are always prior to a command processing.
		When the command finishes processing, its processing result is returned via the callback passed on the method setcommandProcessedCallback.
		*/
		ProcResult process(const std::string& command) override;

		//Sets the command processed callback. As commands are processed asynchronously, a callback is necessary to report when they finish processing.
		void setProcessedCallback(std::function<void(ProcResult)> processedCallback);

	private:

		cassign::DateLogger* m_dateLogger;
		cassign::FunctionalLogger* m_functionalLogger;
		cassign::OutLogger* m_outLogger;
		cassign::ProcessorAvailability m_processorAvailability;
		std::function<void(ProcResult)> m_processedCallback;
		std::default_random_engine m_dre;
		std::mutex m_threadMutex;
		/*
		List that holds allowed commands to get processed. 
		Only allowed commands are processed, so do not forget to initialize them!
		Another read that can be made about this list: it contains the known commands. 
		If a command is not here, then it will eventually result in an "Unknown command" message.
		*/
		std::map<std::string, Command*> m_allowedCommands;
	};
}
