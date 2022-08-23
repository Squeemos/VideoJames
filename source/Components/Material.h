#pragma once

#include <memory>

#include "Mesh.h"
#include "Texture.h"

class Material
{
public:
	Material() = default;
	~Material() = default;

	inline void add_mesh(std::shared_ptr<Mesh> m) { mesh = m; }
	inline void add_texture(std::shared_ptr<Texture> t) { texture = t; }

	inline bool has_mesh() const { return mesh != nullptr; }
	inline bool has_texture() const { return texture != nullptr; }

	inline void bind_mesh() const { mesh->bind(); }
	inline void unbind_mesh() const { mesh->unbind(); }

	inline void bind_texture() const { texture->bind(); }
	inline void unbind_texture() const { texture->unbind(); }

private:
	std::shared_ptr<Mesh> mesh;
	std::shared_ptr<Texture> texture;
};