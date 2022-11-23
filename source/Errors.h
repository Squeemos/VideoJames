#pragma once

#include <exception>
#include <string>

enum class ErrorType
{
	None = 0,
	Window = 1,
	Graphics = 2,
};

class EngineError : public std::exception
{
public:
	EngineError() : __message("Default Error thrown") {}
	EngineError(const ErrorType& t, const std::string& m)
	{
		__message = "Error Type : ";
		switch (t)
		{
		case ErrorType::None:
			__message += "None";
			break;
		case ErrorType::Window:
			__message += "Window";
			break;
		case ErrorType::Graphics:
			__message += "Graphics";
			break;
		default:
			break;
		}

		__message += "\n" + m;
	}
	~EngineError() {}

	const char* what() const noexcept { return __message.c_str(); }
protected:
	std::string __message;
};