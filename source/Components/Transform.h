#pragma once

#include <string>
#include <glm/vec2.hpp>
#include <glm/mat4x4.hpp>

class Transform
{
public:
	Transform();
	Transform(const glm::vec2& t, const glm::vec2& s, const float& r);
	~Transform();

	glm::mat4 get_world() const;
	const glm::vec2& get_translation() const;
	const glm::vec2& get_scale() const;
	const float& get_rotation() const;
	
	void translate(const glm::vec2& r);
	void translate(const float& x, const float& y);
	void translate_x(const float& x);
	void translate_y(const float& y);

	void scale(const glm::vec2& s);
	void scale(const float& x, const float& y);
	void scale_x(const float& x);
	void scale_y(const float& y);

	void rotate(const float& r);

private:
	glm::vec2 translation;
	glm::vec2 scaling;
	float rotation;
};

