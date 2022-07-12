#include "Entity.h"
#include "linmath.h"
#include "Window.h"
#include "Texture.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>

#include <iostream>
#include <utility>

// ECS when the time is right

Entity::Entity() : position(0, 0)
{
    std::cout << "Making Entity" << std::endl;
}

Entity::Entity(glm::vec2 new_pos, const std::string& texture, rgb_mode mode)
{
    position = new_pos;
    tex = std::make_unique<Texture>(texture, mode);
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
        position += glm::vec2(0.01f, 0);
    }
    if (check_key(GLFW_KEY_LEFT))
    {
        position += glm::vec2(-0.01f, 0);
    }
    if (check_key(GLFW_KEY_UP))
    {
        position += glm::vec2(0, 0.01f);
    }
    if (check_key(GLFW_KEY_DOWN))
    {
        position += glm::vec2(0, -0.01f);
    }
}