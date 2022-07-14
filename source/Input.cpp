#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <map>

static std::map<int, int> input_handler;

void update_input(int key, int action)
{
	input_handler[key] = action;
}

int check_key(int key)
{
	const auto iterator = input_handler.find(key);
	if (iterator != input_handler.end())
		return iterator->second;
	else
		return 0;
}