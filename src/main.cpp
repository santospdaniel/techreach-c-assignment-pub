#include <c-assignment/FileStreamsProvider.hpp>
#include <c-assignment/Logger.hpp>
#include <c-assignment/OutLogger.hpp>
#include <c-assignment/DateLogger.hpp>
#include <c-assignment/FunctionalLogger.hpp>
#include <c-assignment/Processor.hpp>
#include <c-assignment/Loader.hpp>
#include <vector>
#include <functional>
#include <stdlib.h>
#include <signal.h>

using namespace cassign;

void intSignalHandler(int signal)
{
	exit(0);
}

void setupIntSignal() 
{
	signal(SIGINT, &intSignalHandler);
}

int main()
{
	OutLogger outLogger(&std::cout);
	FileStreamsProvider dateLogProvider("date_log.log");
	FileStreamsProvider funcLogProvider("functional_log.log");
	dateLogProvider.initialize();
	funcLogProvider.initialize();
	DateLogger dateLogger(dateLogProvider.getOutStream(), dateLogProvider.getInStream());
	FunctionalLogger functionalLogger(funcLogProvider.getOutStream(), funcLogProvider.getInStream());
	outLogger.writeLogFunc("C-Assignment command prompt program. To quit press CTRL+C.");
	Processor processor(&dateLogger, &functionalLogger, &outLogger);
	Loader loader(&processor);
	loader.initialize();
	processor.setProcessedCallback(std::bind(&Loader::processCallback, loader, std::placeholders::_1));

	setupIntSignal();

	while (true)
	{
		loader.promptUser(&std::cin);
	}
	return 0; 
}