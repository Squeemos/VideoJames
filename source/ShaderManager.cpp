#include "ShaderManager.h"
#include "Shader.h"

#include <iostream>

static ShaderManager sm = ShaderManager();

ShaderManager::ShaderManager()
{
	std::cout << "Creating Shader Manager" << std::endl;

	// Reserve space for 10 shaders, can be changed later
	shaders.reserve(10 * sizeof(std::shared_ptr<Shader>));
}

ShaderManager::~ShaderManager()
{
	std::cout << "Destroying Shader Manager" << std::endl;
	shaders.clear();
}

std::shared_ptr<Shader> ShaderManager::construct(const std::string& vertex, const std::string& fragment)
{
	// Check if the shader already exists
	for (auto& shader : shaders)
	{
		if (shader->vert_path == vertex && shader->frag_path == fragment)
			return shader;
	}

	// Doesn't exist, so construct a new one
	std::shared_ptr<Shader> new_shader = std::make_shared<Shader>(vertex, fragment);
	shaders.push_back(new_shader);

	return new_shader;
}

std::shared_ptr<Shader> construct_shader(const std::string& vertex, const std::string& fragment)
{
	return sm.construct(vertex, fragment);
}
