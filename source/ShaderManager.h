#pragma once

#include <map>
#include <memory>

#include "Shader.h"

class ShaderManager
{
public:
	ShaderManager();
	~ShaderManager();
	std::shared_ptr<Shader> construct(const std::string& path);
private:
	std::map<std::string, std::shared_ptr<Shader>> shaders;
};

std::shared_ptr<Shader> construct_shader(const std::string& vertex);
