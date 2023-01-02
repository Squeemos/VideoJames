#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#endif // !STB_IMAGE_IMPLEMENTATION
#include "External/stb_image.h"

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