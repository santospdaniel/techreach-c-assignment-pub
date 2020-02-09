#pragma once
#include <c-assignment/Logger.hpp>
#include <time.h>

namespace cassign 
{
    /*
    DateLogger implements the date logger requirement. By extending the Logger, it can prefix the log lines with date-time information.
    Also, adds implementation to the fetchLogDataInfo method in order to output the number of lines the log file has.
    */
    class DateLogger : public virtual Logger
    {
    public:
        DateLogger(std::ostream* outStream, std::istream* inStream);
        /*Inherited from Logger. Prefixes the log info with date information.*/
        void writeLog(const std::string& info) override;
        /*Inherited from Logger. Fetches the number of lines logged into the outstream argument.*/
        void fetchLogDataInto(std::ostream& outStream) const override;

    protected:
        std::string getPrefix(bool withDate = true) const;

    private:
        tm getCurrentLocalTime() const;
        char* formatTime(char* buffer, size_t buffSize, const tm& time, bool withDate) const;
        
        static const char* m_dateTimeFormat;
        static const char* m_timeFormat;
    };
};