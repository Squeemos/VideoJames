#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/gtc/matrix_transform.hpp>
#pragma warning(disable : 4201)
#include <glm/gtc/quaternion.hpp>

#include "Camera.h"
#include "Input.h"
#include "Trace.h"

#include <iostream>

Camera::Camera() : position(0, 0, 3.0f), target(0, 0, -1.0f), speed(10.0f), size(1920.0f, 1080.0f, 1000.0f), mouse(0.0f, 0.0f), rotation(0.0f, 0.0f)
{
	send_trace_message("Creating Camera");
}

Camera::~Camera()
{
	send_trace_message("Destroying Camwera");
}

void Camera::update(double dt, glm::vec2& vector)
{
	rotation.x += (vector.x - mouse.x) * static_cast<float>(dt) * speed;
	rotation.y += (mouse.y - vector.y) * static_cast<float>(dt) * speed;

	if (rotation.y > 89.99f)
		rotation.y = 89.99f;
	else if (rotation.y < -89.99f)
		rotation.y = -89.99f;

	mouse = vector;

	glm::vec3 direction {};
	direction.x = cos(glm::radians(rotation.x)) * cos(glm::radians(rotation.y));
	direction.y = sin(glm::radians(rotation.y));
	direction.z = sin(glm::radians(rotation.x)) * cos(glm::radians(rotation.y));

	target = glm::normalize(direction);

	if (check_key(GLFW_KEY_W))
		position += target * speed * static_cast<float>(dt);
	if(check_key(GLFW_KEY_S))
		position -= target * speed * static_cast<float>(dt);
}

glm::mat4 Camera::get_projection()
{
	// return glm::ortho(position.x - (size.x / 2.0f), position.x + (size.x / 2.0f), position.y - (size.y / 2.0f), position.y + (size.y / 2.0f), -size.z, size.z);
	return glm::perspective(glm::radians(90.0f), size.x / size.y, .0001f, size.z);
}

glm::mat4 Camera::get_view()
{
	return glm::lookAt(position, target, glm::vec3(0, 1.0f, 0));
}