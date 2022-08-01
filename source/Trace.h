#pragma once

#include <string>

void send_trace_message(const std::string& message);

class Trace
{
public:
	Trace();
	~Trace();

	void trace_message(const std::string& message);

private:
	FILE* trace_file;
};

