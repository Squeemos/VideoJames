#include "Entity.h"
#include "linmath.h"
#include "Window.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <utility>

// ECS when the time is right

Entity::Entity() : position{0,0,0}
{
	std::cout << "Making Entity" << std::endl;
}

Entity::~Entity()
{
    std::cout << "Destroying Entity" << std::endl;
}

void Entity::draw()
{
}

void Entity::update(double dt)
{
    if (check_key(GLFW_KEY_RIGHT))
    {
        vec3 move{ 1,0,0 };
        vec3_add(position, position, move);
    }

    //std::cout << position[0] << " " << position[1] << " " << position[2] << std::endl;
}