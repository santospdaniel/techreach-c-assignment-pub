#pragma once
#include <c-assignment/Initializer.hpp>
#include <istream>
#include <vector>

namespace cassign
{
    class LoadersProcessor;
    struct ProcResult;
    class Command;

    /*
    Loader implements the loader requirement.
    It reads the user input from the keyboard and calls the processor process method with it.
    Logging is done depending on its result. There is the synchronous logging and the asynchronous logging. The later takes place in the method processCallbak.
    The synchronous logging is the one that is possible to infer immediatly, like "unknown command" or "processor is busy".
    The asynchrous logging is the one that is onlye possible to achieve when the command ends processing. It informs the processing time.
    */
    class Loader : public Initializer
    {
    public:
        /*
        Creates all the available commands. 
        Receives the Loader's processor as argument. The LoadersProcessor is a bare version of the Processor, that only exposes to the loader the methods is really needs to consume. 
        */
        Loader(LoadersProcessor* loadersProcessor);
        //Inherited from Initializer. Initializes the commands.
        void initialize() override;
        void promptUser(std::istream* istream);
        void processCallback(ProcResult procResult) const;

    private:
        cassign::LoadersProcessor* m_loadersProcessor;
        std::vector<std::shared_ptr<Command>> m_commands;
        
        static const std::string MESSAGE_COMMAND_PROCESSED;
        static const std::string MESSAGE_PROCESSING_UNITS;
        static const std::string MESSAGE_UNKNOWN_COMMAND;
        static const std::string MESSAGE_PROCESSOR_BUSY;
    };
}