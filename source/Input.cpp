#include <map>

// This whole thing will probably be changed with an event system but I'm not entirely sure yet

static std::map<int, int> input_handler;

void update_input(int key, int action)
{
	input_handler[key] = action;
}

// Find if the key is pressed
int check_key(int key)
{
	// Try and find the key
	const auto iterator = input_handler.find(key);
	
	// If the iterator found something, return the status of the key
	if (iterator != input_handler.end())
		return iterator->second;
	// Otherwise it's not pressed
	else
		return 0;
}