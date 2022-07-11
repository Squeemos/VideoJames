#include "Entity.h"
#include "linmath.h"
#include "Window.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>

#include <iostream>
#include <utility>

// ECS when the time is right

Entity::Entity() : position(1,1)
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
        position += glm::vec2(1, 0);
    }
}