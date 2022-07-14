#include "Entity.h"
#include "linmath.h"
#include "Window.h"
#include "Texture.h"
#include "Input.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include <iostream>

// ECS when the time is right

Entity::Entity() : position(0.0f, 0.0f), scale(0.0f, 0.0f), rotation(0.0f, 0.0f, 0.0f), tex(nullptr)
{
    std::cout << "Creating Entity" << std::endl;
}

Entity::Entity(glm::vec2 new_pos, const std::string& texture, rgb_mode mode, std::string name) : scale(1.0f, 1.0f),
                                                                                                 rotation(0.0f, 0.0f, 0.0f),
                                                                                                 name(name)
{
    std::cout << "Creating Entity: " << name << std::endl;
    position = new_pos;
    tex = std::make_unique<Texture>(texture, mode);
}

Entity::~Entity()
{
    std::cout << "Destroying Entity: " << name << std::endl;
}

void Entity::draw()
{
}

void Entity::update(double dt)
{
    if (check_key(GLFW_KEY_D))
        position += glm::vec2(0.001f, 0);
    if (check_key(GLFW_KEY_A))
        position += glm::vec2(-0.001f, 0);
    if (check_key(GLFW_KEY_W))
        position += glm::vec2(0, 0.001f);
    if (check_key(GLFW_KEY_S))
        position += glm::vec2(0, -0.001f);
    if (check_key(GLFW_KEY_UP))
        scale += glm::vec2(.001f, .001f);
    if (check_key(GLFW_KEY_DOWN))
        scale += glm::vec2(-.001f, -.001f);
    if (check_key(GLFW_KEY_KP_8))
        rotation.x += .001f;
    if (check_key(GLFW_KEY_KP_2))
        rotation.x -= .001f;
    if (check_key(GLFW_KEY_KP_4))
        rotation.y -= .001f;
    if (check_key(GLFW_KEY_KP_6))
        rotation.y += .001f;
    if (check_key(GLFW_KEY_Q))
        rotation.z += .001f;
    if (check_key(GLFW_KEY_E))
        rotation.z -= .001f;
}