#pragma once
#include <string>
#include <iostream>
#include <mutex>

namespace cassign
{
    /*
    The Logger implements the logger requirement. It provides an abstraction for logging implementation.
    It gets access to an output stream to write the log lines into it, and an input stream to read information from the log.
    By writing / reading to streams it is possible to reuse this base class for all kinds of streams, like file streams, console streams, etc.
    For more information consult the FileStreamsProvider documentation.
    */
    class Logger
    {
    public:
        Logger(std::ostream* outStream, std::istream* inStream);
        /*
        Writes to the log the provided information, via the outStream provided in the constructor.
        This is guaranteed to be thread-safe.
        This method is prone to get overrided in derived classes, however check if there are there macros that might offer extra functionality.
        */
        virtual void writeLog(const std::string& info);
        //Fetches this log information via the inStream provided in the constructor, then writes the required information into the outStream argument of this method.
        virtual void fetchLogDataInto(std::ostream& outStream) const = 0;

    protected:
        std::ostream* m_outStream;
        std::istream* m_inStream;

    private:
        std::mutex m_writeMutex;
    };
};

