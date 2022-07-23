#pragma once

#include <memory>

class Shader;
class Mesh;
class Texture;

class Material
{
public:
	Material() {}
	Material(std::shared_ptr<Shader>& s, std::shared_ptr<Mesh>& m, std::shared_ptr<Texture>& t) : shader(s), mesh(m), texture(t) {}
	~Material() {}

	std::shared_ptr<Shader> shader;
	std::shared_ptr<Mesh> mesh;
	std::shared_ptr<Texture> texture;
};