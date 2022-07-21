#include "SandboxScene.h"
#include "Camera.h"
#include "Texture.h"
#include "Mesh.h"
#include "Shader.h"

#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <utility>
#include <cstdlib>
#include <tuple>

struct Name
{
public:
	Name() : name("") {}
	Name(const std::string& n) : name(n) {}
	~Name() {}
	const std::string& get() { return name; }
private:
	std::string name;
};

struct Transform
{
public:
	Transform() : position(0.0f,0.0f,0.0f) {}
	Transform(glm::vec3 tform) : position(tform) {}
	~Transform() {}
	const glm::vec3& get() { return position; }

private:
	glm::vec3 position;
};

SandboxScene::SandboxScene() : Scene()
{
	std::cout << "Creating Sandbox Scene" << std::endl;

	camera = std::make_unique<Camera>();

	entt::entity entity = registry.create();
	registry.emplace<Shader>(entity, "./shaders/vertex_shader.vert", "./shaders/frag_shader.frag");

	// Have this be reading from a file of meshes ---------------------------------
	GLfloat verts[32]{
		// positions          // colors           // texture coords
		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
	};

	GLuint indices[6]{ 0,1,3,1,2,3 };
	// ----------------------------------------------------------------------------

	registry.emplace<Mesh>(entity, verts, 32, indices, 6);
	registry.emplace<Texture>(entity, "./assets/rgba_tex.png", rgb_mode::rgba);
	registry.emplace<Name>(entity, "Kai'Sa");
	registry.emplace<Transform>(entity);
}

SandboxScene::~SandboxScene()
{
	std::cout << "Destroying Sandbox Scene" << std::endl;
}

void SandboxScene::update(double dt)
{
	camera->update(dt);
}

void SandboxScene::draw()
{
	auto group = registry.group<Shader>(entt::get<Transform, Mesh, Texture>);
	for (auto entity : group)
	{
		auto [shader, transform, mesh, texture] = group.get<Shader, Transform, Mesh, Texture>(entity);

		shader.use();
		shader.set_mat4("projection", camera->get_projection());
		shader.set_mat4("view", camera->get_view());

		glm::mat4 model = glm::mat4(1);
		model = glm::translate(model, transform.get());
		shader.set_mat4("model", model);
		
		shader.set_int("texture0", 0);
		texture.use();
		mesh.bind_vao();
		mesh.unbind_vao();
		shader.unbind();
	}
}