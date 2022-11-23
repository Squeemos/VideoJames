#pragma once

#include <iostream>
#include <fstream>
#include <mutex>
#include <iostream>

// A simple trace system that is thread safe and can be created only when asked to send a trace message
class TraceSystem
{
public:
	// Start a trace system with a specific file in mind
	TraceSystem(const std::string& file_path)
	{
		// Open the file
		__file.open(file_path);
		// Check to make sure that it was read correctly
		if (__file.rdstate() & std::ofstream::failbit)
		{
			std::cerr << "Cannot create the trace file. Error from: " << file_path << std::endl;
			std::abort();
		}
	}

	// Shutdown the trace system and close the file
	~TraceSystem()
	{
		__file.close();
	}

	// Prevent copying
	TraceSystem() = delete;
	TraceSystem(const TraceSystem& other) = delete;
	TraceSystem& operator=(const TraceSystem& other) = delete;

	// Actually write the message into the file
	void operator<<(const std::string& message)
	{
		__mutex.lock();

		#ifdef _DEBUG
		std::cout << message << std::endl;
		#endif

		__file << message << std::endl;
		__mutex.unlock();
	}

private:
	std::ofstream __file;
	std::mutex __mutex;
};

// How to interact with the trace system
// TODO : Make it use an instance like the input system so we can maybe have multiple different logs for things
inline void trace_message(const std::string& message)
{
	static TraceSystem ts = TraceSystem("./trace.log");
	ts << message;
}