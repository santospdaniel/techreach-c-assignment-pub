#pragma once
#include <c-assignment/Initializer.hpp>
#include <fstream>

namespace cassign 
{
	/*
	File streams provider is a convenient way to decouple logging from files. This way, the logging classes (Logger, DateLoger, etc) can write and read to just streams.
	The FileStreamsProvider makes possible for the logging classes to use files. A file path is passed in the constructor.
	After initializing this class it becomes possible to get the file output and input streams that can be used as argumments for the logging classes.
	*/
	class FileStreamsProvider : public Initializer
	{
	public:
		//Constructs the FileStreamsProvider indicating to which file it has to open output and input streams. However the constructor doesn't open them immediatly.
		FileStreamsProvider(const char* logFilePath);
		void initialize() override;
		std::ostream* getOutStream();
		std::istream* getInStream();

	private:
		std::string m_logFilePath;
		std::ofstream m_logFileOut;
		std::ifstream m_logFileIn;
	};
};

