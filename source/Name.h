#pragma once

#include <string>

class Name
{
public:
	Name() : name("") {}
	Name(const std::string& n) : name(n) {}
	~Name() {}

	// Operator overloads
	operator std::string& () { return name; }
	operator const std::string& () const { return name; }
private:
	std::string name;
};