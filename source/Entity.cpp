#include "Entity.h"
#include "linmath.h"
#include "Window.h"
#include "Texture.h"
#include "Input.h"
#include "Mesh.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include <iostream>

// ECS when the time is right

Entity::Entity() : position(0.0f, 0.0f, 0.0f), scale(0.0f, 0.0f, 0.0f), rotation(0.0f, 0.0f, 0.0f), tex(nullptr), speed(0.0f)
{
    std::cout << "Creating Entity" << std::endl;
}

Entity::Entity(glm::vec3 new_pos, const std::string& texture, rgb_mode mode, std::string name) : position(new_pos),
                                                                                                 scale(600.0f, 600.0f, 0.0f),
                                                                                                 rotation(0.0f, 0.0f, 0.0f),
                                                                                                 name(name),
                                                                                                 speed(100.0f)
{
    std::cout << "Creating Entity: " << name << std::endl;

    // Make the texture
    tex = std::make_shared<Texture>(texture, mode);

    // Have this be reading from a file of meshes ---------------------------------
    GLfloat verts [32]{
        // positions          // colors           // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
    };

    GLuint indices[6]{ 0,1,3,1,2,3 };
    // ----------------------------------------------------------------------------

    mesh = std::make_shared<Mesh>(verts, 32, indices, 6);
}

Entity::~Entity()
{
    std::cout << "Destroying Entity: " << name << std::endl;
}

void Entity::draw()
{
    // Set the texture
    mesh->set_texture();

    // Setup the entity's model uniform
    glm::mat4 model = glm::mat4(1);

    // Perform world translation
    model = glm::translate(model, position);

    // Clean up rotations (turn into quat)
    // Perform rotation
    model = glm::rotate(model, rotation.x, glm::vec3(1.0f, 0, 0));
    model = glm::rotate(model, rotation.y, glm::vec3(0, 1.0f, 0));
    model = glm::rotate(model, rotation.z, glm::vec3(0, 0, 1.0f));

    // Scale the entity
    model = glm::scale(model, scale);

    // Set the model uniform
    mesh->shader_set_mat4("model", model);

    // Use the texture
    tex->use();

    // Bind the mesh
    mesh->bind_vao();
    
    // Unbind the mesh
    mesh->unbind_vao();
}

void Entity::update(double dt)
{
    if (check_key(GLFW_KEY_D))
        position.x += speed * dt;
    if (check_key(GLFW_KEY_A))
        position.x -= speed * dt;
    if (check_key(GLFW_KEY_W))
        position.y += speed * dt;
    if (check_key(GLFW_KEY_S))
        position.y -= speed * dt;
    if (check_key(GLFW_KEY_UP))
        scale += glm::vec3(1.0f * dt, 1.0f * dt, 0.0f);
    if (check_key(GLFW_KEY_DOWN))
        scale += glm::vec3(-1.0f * dt, -1.0f * dt, 0.0f);
    if (check_key(GLFW_KEY_KP_8))
        rotation.x -= speed * dt;
    if (check_key(GLFW_KEY_KP_2))
        rotation.x += speed * dt;
    if (check_key(GLFW_KEY_KP_4))
        rotation.y -= speed * dt;
    if (check_key(GLFW_KEY_KP_6))
        rotation.y += speed * dt;
    if (check_key(GLFW_KEY_Q))
        rotation.z += speed * dt;
    if (check_key(GLFW_KEY_E))
        rotation.z -= speed * dt;
    if (check_key(GLFW_KEY_Z))
        position.z -= speed * dt;
    if (check_key(GLFW_KEY_X))
        position.z += speed * dt;
}