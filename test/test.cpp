#include <c-assignment/FileStreamsProvider.hpp>
#include <c-assignment/Logger.hpp>
#include <c-assignment/DateLogger.hpp>
#include <c-assignment/FunctionalLogger.hpp>
#include <c-assignment/OutLogger.hpp>
#include <iostream>
#include <assert.h>
#include <sstream>
#include <regex>

void testDateLoggerWith2Lines()
{
	cassign::FileStreamsProvider strmProv("test_date_log.log");
	strmProv.initialize();
	cassign::DateLogger dlogger(strmProv.getOutStream(), strmProv.getInStream());
	dlogger.writeLog("test 123");
	dlogger.writeLog("test 456");
	std::ostringstream oss;
	dlogger.fetchLogDataInto(oss);
	assert(oss.str() == "2\n");
}

void testDateLoggerEmpty()
{
	cassign::FileStreamsProvider strmProv("test_date_log.log");
	strmProv.initialize();
	cassign::DateLogger dlogger(strmProv.getOutStream(), strmProv.getInStream());
	std::ostringstream oss;
	dlogger.fetchLogDataInto(oss);
	assert(oss.str() == "0\n");
}

void testFunctionalLoggerWith2Lines()
{
	cassign::FileStreamsProvider strmProv("test_functional_log.log");
	strmProv.initialize();
	cassign::FunctionalLogger flogger(strmProv.getOutStream(), strmProv.getInStream());
	flogger.writeLogFunc("test 123");
	flogger.writeLogFunc("test 456");
	std::ostringstream oss;
	flogger.fetchLogDataInto(oss);
	assert(oss.str() == "[2][testFunctionalLoggerWith2Lines] test 456\n");
}

void testFunctionalLoggerWith1Line()
{
	cassign::FileStreamsProvider strmProv("test_functional_log.log");
	strmProv.initialize();
	cassign::FunctionalLogger flogger(strmProv.getOutStream(), strmProv.getInStream());
	flogger.writeLogFunc("test 123");
	std::ostringstream oss;
	flogger.fetchLogDataInto(oss);
	assert(oss.str() == "(no even lines found)\n");
}

void testFunctionalLoggerEmpty()
{
	cassign::FileStreamsProvider strmProv("test_functional_log.log");
	strmProv.initialize();
	cassign::FunctionalLogger flogger(strmProv.getOutStream(), strmProv.getInStream());
	std::ostringstream oss;
	flogger.fetchLogDataInto(oss);
	assert(oss.str() == "(no even lines found)\n");
}

void testOutLogger()
{
	std::ostringstream oss;
	oss << "132 ";
	cassign::OutLogger ologger(&oss);
	ologger.writeLogFunc("test 345");
	std::regex pattern("132 \\[\\d\\d:\\d\\d:\\d\\d\\]\\[testOutLogger\\] test 345\n");
	assert(std::regex_match(oss.str(), pattern));
}

void testLoggers() 
{
	testDateLoggerWith2Lines();
	testDateLoggerEmpty();
	testFunctionalLoggerWith2Lines();
	testFunctionalLoggerWith1Line();
	testFunctionalLoggerEmpty();
	testOutLogger();
}

int main()
{
	testLoggers();
	return 0;
}