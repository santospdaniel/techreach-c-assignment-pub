#pragma once
#include <c-assignment/Logger.hpp>

namespace cassign
{
    /*
    FunctionalLogger implements the functional logger requirement. By extending the Logger, it can prefix the log lines with line-number and class-function-name information.
    Also, adds implementation to the fetchLogDataInfo method in order to output the even lines of the log.
    */
    class FunctionalLogger : public virtual Logger
    {
    public:
        FunctionalLogger(std::ostream* outStream, std::istream* inStream);
        /*
        Is not inherited from Logger. Adds the cppMethod and the withLineCount arguments to form the log line perfix.
        Intentionally hides the Logger::writeLog, but consumes it internally.
        */
        void writeLog(const std::string& info, const std::string& cppMethod);
        //Inherited from Logger. Fetches the even line numbers from the log into the outstream argument.
        void fetchLogDataInto(std::ostream& outStream) const override;

    protected:
        /*
        Gets the prefix of the log line. The prefix is provided by the cppMethod argument. It is supposed to be in the format class-function-name.
        If withLineCount is true the prefix will be line-number and class-function-name.
        If withLineCount is false the prefix will be just class-function-name.
        */
        std::string getPrefix(const std::string& cppMethod, const bool withLineCount);

    private:
        inline std::string replaceStr(const std::string& originalStr, const std::string& findStr, const std::string& replaceStr) 
        {
            if (!originalStr.empty() && !findStr.empty()) //most probable code flow to optmize CPU's local cache usage.
            {
                size_t pos = originalStr.find(findStr);
                if (pos != std::string::npos) //most probable code flow to optmize CPU's local cache usage.
                {
                    std::string copOfOriginalConstStr = originalStr;
                    return copOfOriginalConstStr.replace(pos, findStr.length(), replaceStr);
                }
                return originalStr;
            }
            return originalStr;
        }

        int m_lineCount;

    };

};

//This macro adds compile information to the log.
#ifndef writeLogFunc
#define writeLogFunc(info) writeLog((info),__FUNCTION__)
#endif // !writeLogFunc

