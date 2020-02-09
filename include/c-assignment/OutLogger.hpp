#pragma once
#include <c-assignment/DateLogger.hpp>
#include <c-assignment/FunctionalLogger.hpp>
#include <ostream>
#include <ctime>

namespace cassign
{
    /*
    OutlLogger implements the stdout logger requirement. By extending both DateLogger and FunctionalLogger, it can prefix the log lines with time and class-function-name information.
    Also, contains no implementation to the fetchLogDataInfo.
    */
    class OutLogger : public DateLogger, public FunctionalLogger
    {
    public:
        OutLogger(std::ostream* outStream);
        //Inherited from Logger. Disambiguates super class methods.
        void writeLog(const std::string& info) override;
        //Is not inherited from Logger. Writes log information with compile information as prefix.
        void writeLog(const std::string& info, const std::string& cppMethod, const bool withLineCount);
        /*Inherited from Logger. Disambiguates super class methods.*/
        void fetchLogDataInto(std::ostream& outStream) const override;

    protected:
        std::string getPrefix(const std::string& cppMethod);
    };

};

//This macro adds compile information to the log.
#ifndef writeLogFunc
#define writeLogFunc(info) writeLog((info),__FUNCTION__, true)
#endif // !writeLogFunc
