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
    tex = std::make_shared<Texture>(texture, mode);

    // Have this be reading from a file of meshes
    GLfloat verts [32]{
        // positions          // colors           // texture coords
         1.0f,  1.0f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
         1.0f, -1.0f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
        -1.0f, -1.0f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
        -1.0f,  1.0f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
    };

    GLuint indices[6]{ 0,1,3,1,2,3 };

    mesh = std::make_shared<Mesh>(verts, static_cast<GLuint>(sizeof(verts)), indices, static_cast<GLuint>(sizeof(indices)));
}

Entity::~Entity()
{
    std::cout << "Destroying Entity: " << name << std::endl;
}

void Entity::draw()
{
    // Use shader program
    mesh->use_shader_program();

    // Set the texture
    mesh->set_texture();

    // Make the things
    glm::mat4 model = glm::mat4(1);
    model = glm::translate(model, glm::vec3(position, 0));

    // Clean up rotations (turn into quat)
    model = glm::rotate(model, rotation.x, glm::vec3(1.0f, 0, 0));
    model = glm::rotate(model, rotation.y, glm::vec3(0, 1.0f, 0));
    model = glm::rotate(model, rotation.z, glm::vec3(0, 0, 1.0f));

    model = glm::scale(model, glm::vec3(scale, 0));

    glm::mat4 projection = glm::perspective(glm::radians(90.0f), 1.0f, 0.1f, 100.0f);

    glm::mat4 view = glm::lookAt(glm::vec3(0, 0, 3.0f), glm::vec3(0, 0, 0), glm::vec3(0, 1.0f, 0)); // Camera

    mesh->shader_set_mat4("model", model);
    mesh->shader_set_mat4("projection", projection);
    mesh->shader_set_mat4("view", view); // The camera

    tex->use();

    // Bind the mesh
    mesh->draw();
    
    // Unbind the mesh
    mesh->unbind();
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
        rotation.x -= .001f;
    if (check_key(GLFW_KEY_KP_2))
        rotation.x += .001f;
    if (check_key(GLFW_KEY_KP_4))
        rotation.y -= .001f;
    if (check_key(GLFW_KEY_KP_6))
        rotation.y += .001f;
    if (check_key(GLFW_KEY_Q))
        rotation.z += .001f;
    if (check_key(GLFW_KEY_E))
        rotation.z -= .001f;
}