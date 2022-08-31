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
	EngineError() : message("Default Error thrown") {}
	EngineError(const ErrorType& t, const std::string& m)
	{
		message = "Error Type : ";
		switch (t)
		{
		case ErrorType::None:
			message += "None";
			break;
		case ErrorType::Window:
			message += "Window";
			break;
		case ErrorType::Graphics:
			message += "Graphics";
			break;
		default:
			break;
		}

		message += "\n" + m;
	}
	~EngineError() {}

	const char* what() const noexcept { return message.c_str(); }
protected:
	std::string message;
};