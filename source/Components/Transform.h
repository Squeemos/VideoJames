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
	Transform(const glm::vec2& t, const glm::vec2& s, const float& r, const float& z);

	~Transform();

	// Gets the world coordinates of the transform
	glm::mat4 get_matrix() const;

	// Other getters for specific sections
	inline const glm::vec2& get_translation() const { return translation; }
	inline const glm::vec2& get_scale() const { return scaling; }
	inline const float& get_rotation() const { return rotation; }
	inline const float& get_z_order() const { return z_order; }
	
	// Methods to translate with different options
	inline void translate(const glm::vec2& r) { translation += r; }
	inline void translate(const float& x, const float& y) { translation.x += x; translation.y += y; }
	inline void translate_x(const float& x) { translation.x += x; }
	inline void translate_y(const float& y) { translation.y += y; }
	inline void set_translation(const glm::vec2& r) { translation = r; }
	inline void set_translation(const float& x, const float& y) { translation.x = x; translation.y = y; }
	inline void set_translation_x(const float& x) { translation.x = x; }
	inline void set_translation_y(const float& y) { translation.y = y; }

	// Methods to scale with different options
	inline void scale(const glm::vec2& s) { scaling += s; }
	inline void scale(const float& x, const float& y) { scaling.x += x; scaling.y += y; }
	inline void scale_x(const float& x) { scaling.x += x; }
	inline void scale_y(const float& y) { scaling.y += y; }
	inline void set_scale(const glm::vec2& s) { scaling = s; }
	inline void set_scale(const float& x, const float& y) { scaling.x = x; scaling.y = y; }
	inline void set_scale_x(const float& x) { scaling.x = x; }
	inline void set_scale_y(const float& y) { scaling.y = y; }

	// Methods to adjust the rotation
	inline void rotate(const float& r) { rotation += r; }
	inline void set_rotation(const float& r) { rotation = r; }

	// Methods to change the z_order
	inline void set_z_order(const float& f) { z_order = f; }

	// Compare two transforms by z_order
	inline static bool compare(const Transform& left, const Transform& right) { return left.z_order < right.z_order; }

private:
	glm::vec2 translation;
	glm::vec2 scaling;
	float rotation;
	float z_order;
};

