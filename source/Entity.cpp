#include "Entity.h"
#include "linmath.h"
#include "Window.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <utility>

// ECS when the time is right

Entity::Entity() : position{0,0,0}, vertices{
    // first triangle
     0.5f,  0.5f, 0.0f,  // top right
     0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f,  0.5f, 0.0f,  // top left 
    // second triangle
     0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  // bottom left
    -0.5f,  0.5f, 0.0f   // top left
}
{
	std::cout << "Making Entity" << std::endl;
}

Entity::~Entity()
{
    std::cout << "Destroying Entity" << std::endl;
}

std::pair<float*,unsigned long long> Entity::draw()
{
    std::cout << position[0] << " " << position[1] << " " << position[2] << std::endl;
	return std::make_pair(vertices, sizeof(vertices));
}

void Entity::update(double dt)
{
    if (check_key(GLFW_KEY_RIGHT))
    {
        vec3 move{ 1,0,0 };
        vec3_add(position, position, move);

        vertices[1] += 0.001f;
    }
}