#pragma once

#include <memory>

class Shader;
class Model;

class Material
{
public:
	Material() {}
	Material(std::shared_ptr<Shader>& s, std::shared_ptr<Model>& m) : shader(s), model(m) {}
	~Material() {}

	std::shared_ptr<Shader> shader;
	std::shared_ptr<Model> model;
};