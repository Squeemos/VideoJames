#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/ext.hpp>

#include "Camera.h"
#include "Input.h"

#include <iostream>

// Make the camera size based off the monitor size
Camera::Camera() : position(0, 0, 3.0f), target(0, 0, 0), speed(5.0f), size(1920.0f, 1080.0f, 100.0f)
{
	std::cout << "Creating Camera" << std::endl;
}

Camera::~Camera()
{
	std::cout << "Destroying Camera" << std::endl;
}
void Camera::update(double dt)
{
	if (check_key(GLFW_KEY_I))
	{
		position.z -= speed * static_cast<float>(dt);
		target.z -= speed * static_cast<float>(dt);
	}
	if (check_key(GLFW_KEY_K))
	{
		position.z += speed * static_cast<float>(dt);
		target.z += speed * static_cast<float>(dt);
	}
	if (check_key(GLFW_KEY_J))
	{
		position.x += speed * static_cast<float>(dt);
		target.x += speed * static_cast<float>(dt);
	}
	if (check_key(GLFW_KEY_L))
	{
		position.x -=  speed * static_cast<float>(dt);
		target.x -= speed * static_cast<float>(dt);
	}
}

glm::mat4 Camera::get_projection()
{
	// glm::mat4 view = glm::ortho(position.x - (size.x / 2.0f), position.x + (size.x / 2.0f), position.y - (size.y / 2.0f), position.y + (size.y / 2.0f));

	return glm::ortho(position.x - (size.x / 2.0f), position.x + (size.x / 2.0f), position.y - (size.y / 2.0f), position.y + (size.y / 2.0f), -size.z, size.z);
	// return glm::perspective(glm::radians(90.0f), size.x / size.y, .1f, size.z);
}

glm::mat4 Camera::get_view()
{
	glm::mat4 view = glm::lookAt(position, target, glm::vec3(0, 1.0f, 0));
	return view;
}