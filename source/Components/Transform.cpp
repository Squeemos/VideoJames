#include "Transform.h"

#include <GLFW/glfw3.h>

#include <glm/gtc/matrix_transform.hpp>

Transform::Transform() : translation(0,0), scaling(100,100), rotation(0.0f), z_order(0)
{
}

Transform::Transform(const glm::vec2& t, const glm::vec2& s, const float& r) : translation(t), scaling(s), rotation(r), z_order(0)
{
}

Transform::Transform(const glm::vec2& t, const glm::vec2& s, const float& r, const float& z) : translation(t), scaling(s), rotation(r), z_order(z)
{
}

Transform::~Transform()
{
}

glm::mat4 Transform::get_world() const
{
	//glm::mat4 world = glm::mat4(1);
	//world = glm::translate(world, glm::vec3(translation, z_order));
	//world = glm::rotate(world, glm::radians(rotation), glm::vec3(0, 0, 0.1f));
	//world = glm::scale(world, glm::vec3(scaling, 1.0f));
	//return world;

	glm::mat4 t = glm::translate(glm::mat4(1), glm::vec3(translation, z_order));
	glm::mat4 r = glm::rotate(glm::mat4(1), glm::radians(rotation), glm::vec3(0, 0, 1));
	glm::mat4 s = glm::scale(glm::mat4(1), glm::vec3(scaling, 1));

	return t * r * s;
}

const glm::vec2& Transform::get_translation() const
{
	return translation;
}

const glm::vec2& Transform::get_scale() const
{
	return scaling;
}

const float& Transform::get_rotation() const
{
	return rotation;
}

void Transform::translate(const glm::vec2& r)
{
	translation += r;
}

void Transform::translate(const float& x, const float& y)
{
	translation.x += x;
	translation.y += y;
}

void Transform::translate_x(const float& x)
{
	translation.x += x;
}

void Transform::translate_y(const float& y)
{
	translation.y += y;
}

void Transform::set_translation(const glm::vec2& r)
{
	translation = r;
}

void Transform::set_translation(const float& x, const float& y)
{
	translation.x = x;
	translation.y = y;
}

void Transform::set_translation_x(const float& x)
{
	translation.x = x;
}

void Transform::set_translation_y(const float& y)
{
	translation.y = y;
}

void Transform::scale(const glm::vec2& s)
{
	scaling += s;
}

void Transform::scale(const float& x, const float& y)
{
	scaling.x += x;
	scaling.y += y;
}

void Transform::scale_x(const float& x)
{
	scaling.x += x;
}

void Transform::scale_y(const float& y)
{
	scaling.y += y;
}

void Transform::set_scale(const glm::vec2& s)
{
	scaling = s;
}

void Transform::set_scale(const float& x, const float& y)
{
	scaling.x = x;
	scaling.y = y;
}

void Transform::set_scale_x(const float& x)
{
	scaling.x = x;
}

void Transform::sset_scale_y(const float& y)
{
	scaling.y = y;
}

void Transform::rotate(const float& r)
{
	rotation += r;
}

void Transform::set_rotation(const float& r)
{
	rotation = r;
}

void Transform::set_z_order(const float& f)
{
	z_order = f;
}
