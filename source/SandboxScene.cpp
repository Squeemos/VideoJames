#include "SandboxScene.h"
#include "Camera.h"
#include "Texture.h"
#include "Mesh.h"
#include "Shader.h"
#include "ShaderManager.h"

#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <utility>
#include <cstdlib>
#include <tuple>

class Name
{
public:
	Name() : name("") {}
	Name(const std::string& n) : name(n) {}
	~Name() {}
	const std::string& get() { return name; }
private:
	std::string name;
};

class Transform
{
public:
	Transform() : position(0.0f,0.0f,0.0f) {}
	Transform(glm::vec3 tform) : position(tform) {}
	~Transform() {}
	const glm::vec3& get() { return position; }

private:
	glm::vec3 position;
};

class Material
{
public:
	Material() {}
	Material(std::shared_ptr<Shader>& s, std::shared_ptr<Mesh>& m, std::shared_ptr<Texture>& t) : shader(s), mesh(m), texture(t) {}
	~Material() {}

	std::shared_ptr<Shader> shader;
	std::shared_ptr<Mesh> mesh;
	std::shared_ptr<Texture> texture;
};

SandboxScene::SandboxScene() : Scene()
{
	std::cout << "Creating Sandbox Scene" << std::endl;

	camera = std::make_unique<Camera>();

	entt::entity entity = registry.create();

	auto& material = registry.emplace<Material>(entity);

	material.shader = construct_shader("./shaders/vertex_shader.vert", "./shaders/frag_shader.frag");

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

	material.mesh = std::make_shared<Mesh>(verts, 32, indices, 6);
	material.texture = std::make_shared<Texture>("./assets/rgba_tex.png", rgb_mode::rgba);

	registry.emplace<Name>(entity, "Kai'Sa");
	registry.emplace<Transform>(entity);

	entt::entity entity2 = registry.create();
	auto& material2 = registry.emplace<Material>(entity2);
	material2.shader = construct_shader("./shaders/vertex_shader.vert", "./shaders/frag_shader.frag");
	material2.mesh = std::make_shared<Mesh>(verts, 32, indices, 6);
	material2.texture = std::make_shared<Texture>("./assets/rgb_tex.jpg", rgb_mode::rgb);
	registry.emplace<Name>(entity2, "Bagel");
	registry.emplace<Transform>(entity2, glm::vec3(1.0f,0.0f,0.0f));

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
	auto group = registry.group<Transform>(entt::get<Material>);
	for (auto entity : group)
	{
		auto [transform, material] = group.get<Transform, Material>(entity);

		material.shader->use();
		material.shader->set_mat4("projection", camera->get_projection());
		material.shader->set_mat4("view", camera->get_view());

		glm::mat4 model = glm::mat4(1);
		model = glm::translate(model, transform.get());
		material.shader->set_mat4("model", model);
		
		material.shader->set_int("texture0", 0);
		if (material.texture)
		{
			material.shader->set_int("texture_or_color", 1);
			material.texture->bind();
		}
		else
		{
			material.shader->set_int("texture_or_color", 0);
		}
		material.mesh->bind_vao();
		material.mesh->unbind_vao();
		if(material.texture)
			material.texture->unbind();
		material.shader->unbind();
	}
}