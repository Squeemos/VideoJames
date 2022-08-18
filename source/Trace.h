#pragma once

#include <iostream>
#include <fstream>
#include <mutex>
#include <iostream>

class TraceSystem
{
public:
	TraceSystem(const std::string& file_path)
	{
		file.open(file_path);
		if (file.rdstate() & std::ofstream::failbit)
			std::cerr << "Cannot create the trace file. Error from: " << file_path << std::endl;
	}
	~TraceSystem()
	{
		file.close();
	}

	// Prevent copying
	TraceSystem() = delete;
	TraceSystem(const TraceSystem& other) = delete;
	TraceSystem& operator=(const TraceSystem& other) = delete;

	void operator<<(const std::string& message)
	{
		mutex.lock();

		#ifdef _DEBUG
		std::cout << message << std::endl;
		#endif

		file << message << std::endl;
		mutex.unlock();
	}

private:
	std::ofstream file;
	std::mutex mutex;
};

inline void trace_message(const std::string& message)
{
	static TraceSystem ts = TraceSystem("./trace.log");
	ts << message;
}