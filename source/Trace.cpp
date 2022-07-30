#include "Trace.h"
#pragma warning(disable : 4996)
#include "stdio.h"
#include <fstream>
#include <iostream>
#include "Error.h"

#ifndef _DEBUG
#define _DEBUG false
#endif


static FILE* trace_file;

void trace_init()
{
	trace_file = fopen("trace.log", "w");
	if (!trace_file)
	{
		throw std::exception("Error creating trace log");
	}
}

void send_trace_message(const std::string& message)
{
	if (trace_file)
	{
		if (_DEBUG)
			std::cout << message << std::endl;
		fprintf(trace_file, message.c_str());
		fprintf(trace_file, "\n");
	}
}

void trace_shutdown()
{
	if(trace_file)
		fclose(trace_file);
	trace_file = nullptr;
}
