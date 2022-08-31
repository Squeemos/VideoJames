#include "Engine.h"
#include "Errors.h"
#include "Trace.h"

// Main
int main()
{
	try
	{
		Engine e = Engine();
		e.run();
		return 0;
	}
	catch (const EngineError& e)
	{
		trace_message(e.what());
		return -1;
	}
}