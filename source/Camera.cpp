#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Camera.h"
#include "Input.h"

#include <iostream>

Camera::Camera() : position(0, 0, 3.0f), target(0, 0, 0), speed(0.005f)
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
		position.z -= speed;
		target.z -= speed;
	}
	if (check_key(GLFW_KEY_K))
	{
		position.z += speed;
		target.z += speed;
	}
	if (check_key(GLFW_KEY_J))
	{
		position.x += speed;
		target.x += speed;
	}
	if (check_key(GLFW_KEY_L))
	{
		position.x -=  speed;
		target.x -= speed;
	}
}