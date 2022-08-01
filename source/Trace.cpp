#include "Trace.h"
#pragma warning(disable : 4996)
#include "stdio.h"
#include <fstream>
#include <iostream>
#include "Error.h"

#ifndef _DEBUG
#define _DEBUG false
#endif
// Used to see if we're printing to the console as well

static Trace t = Trace();

Trace::Trace()
{
	trace_file = fopen("trace.log", "w");
	if (!trace_file)
	{
		throw std::exception("Error creating trace log");
	}
}

Trace::~Trace()
{
	if (trace_file)
		fclose(trace_file);
	trace_file = nullptr;
}

void Trace::trace_message(const std::string& message)
{
	if (trace_file)
	{
		if (_DEBUG)
			std::cout << message << std::endl;
		fprintf(trace_file, message.c_str());
		fprintf(trace_file, "\n");
	}
}

void send_trace_message(const std::string& message)
{
	t.trace_message(message);
}
