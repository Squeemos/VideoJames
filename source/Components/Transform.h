#pragma once

#include <string>
#include <glm/vec2.hpp>
#include <glm/mat4x4.hpp>

// Basic transform object that holds in translation/scale/rotation for an entity
class Transform
{
public:
	// Default transform
	Transform();

	// Non-defualt so we can specify extras
	Transform(const glm::vec2& t, const glm::vec2& s, const float& r);
	~Transform();

	// Gets the world coordinates of the transform
	glm::mat4 get_world() const;

	// Other getters for specific sections
	const glm::vec2& get_translation() const;
	const glm::vec2& get_scale() const;
	const float& get_rotation() const;
	
	// Methods to translate with different options
	void translate(const glm::vec2& r);
	void translate(const float& x, const float& y);
	void translate_x(const float& x);
	void translate_y(const float& y);

	// Methods to scale with different options
	void scale(const glm::vec2& s);
	void scale(const float& x, const float& y);
	void scale_x(const float& x);
	void scale_y(const float& y);

	// Rotate the object about it's center in degrees
	void rotate(const float& r);

private:
	glm::vec2 translation;
	glm::vec2 scaling;
	float rotation;
};

