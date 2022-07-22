#pragma once

#include <vector>
#include <memory>
#include <string>

class Shader;

class ShaderManager
{
public:
	ShaderManager();
	~ShaderManager();
	std::shared_ptr<Shader> construct(const std::string& vertex, const std::string& fragment);
private:
	std::vector<std::shared_ptr<Shader>> shaders;
};

std::shared_ptr<Shader> construct_shader(const std::string& vertex, const std::string& fragment);
