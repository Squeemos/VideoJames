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
	glm::mat4 get_matrix();

	// Other getters for specific sections
	inline const glm::vec2& get_translation() const { return __translation; }
	inline const glm::vec2& get_scale() const { return __scaling; }
	inline const float& get_rotation() const { return __rotation; }
	inline const float& get_z_order() const { return __z_order; }
	
	// Methods to translate with different options
	inline void translate(const glm::vec2& r) { __translation += r; __dirty = true; }
	inline void translate(const float& x, const float& y) { __translation.x += x; __translation.y += y; __dirty = true; }
	inline void translate_x(const float& x) { __translation.x += x; __dirty = true; }
	inline void translate_y(const float& y) { __translation.y += y; __dirty = true; }
	inline void set_translation(const glm::vec2& r) { __translation = r; __dirty = true; }
	inline void set_translation(const float& x, const float& y) { __translation.x = x; __translation.y = y; __dirty = true; }
	inline void set_translation_x(const float& x) { __translation.x = x; __dirty = true; }
	inline void set_translation_y(const float& y) { __translation.y = y; __dirty = true; }

	// Methods to scale with different options
	inline void scale(const glm::vec2& s) { __scaling += s; __dirty = true; }
	inline void scale(const float& x, const float& y) { __scaling.x += x; __scaling.y += y; __dirty = true; }
	inline void scale_x(const float& x) { __scaling.x += x; __dirty = true; }
	inline void scale_y(const float& y) { __scaling.y += y; __dirty = true; }
	inline void set_scale(const glm::vec2& s) { __scaling = s; __dirty = true; }
	inline void set_scale(const float& x, const float& y) { __scaling.x = x; __scaling.y = y; __dirty = true; }
	inline void set_scale_x(const float& x) { __scaling.x = x; __dirty = true; }
	inline void set_scale_y(const float& y) { __scaling.y = y; __dirty = true; }

	// Methods to adjust the rotation
	inline void rotate(const float& r) { __rotation += r; __dirty = true; }
	inline void set_rotation(const float& r) { __rotation = r; __dirty = true; }

	// Methods to change the z_order
	inline void set_z_order(const float& z) { __z_order = z; }

	// Compare two transforms by z_order
	inline static bool compare(const Transform& left, const Transform& right) { return left.__z_order < right.__z_order; }

	inline bool get_dirty() const { return __dirty; }

private:
	glm::vec2 __translation;
	glm::vec2 __scaling;
	float __rotation;
	float __z_order;

	bool __dirty;
	glm::mat4 __matrix;
};

