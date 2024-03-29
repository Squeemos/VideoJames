#pragma once

#include <memory>

#include "Mesh.h"
#include "Texture.h"

#include <glm/vec3.hpp>

// Class for holding onto the things that get rendered
class Material
{
public:
	// These don't need to really do anything since the default sets the ptrs to null
	Material() : __color(1.0, 0.65, 0.0) {}
	~Material() = default;

	// Add components to the material
	inline void add_mesh(std::shared_ptr<Mesh> m) { __mesh = m; }
	inline void add_texture(std::shared_ptr<Texture> t) { __texture = t; }
	inline void add_color(const glm::vec3& c) { __color = c; }

	// Check to see if they have valid members
	inline bool has_mesh() const { return __mesh != nullptr; }
	inline bool has_texture() const { return __texture != nullptr; }

	// Tell the mesh to bind for the draw step
	inline void bind_mesh() const { __mesh->bind(); }
	inline void unbind_mesh() const { __mesh->unbind(); }

	// Tell the texture to bind for the draw step
	inline void bind_texture() const { __texture->bind(); }
	inline void unbind_texture() const { __texture->unbind(); }

	// Get the color of the material (mostly used in case there isn't a texture)
	inline const glm::vec3& get_color() const { return __color; }

private:
	std::shared_ptr<Mesh> __mesh;
	std::shared_ptr<Texture> __texture;
	glm::vec3 __color;
};