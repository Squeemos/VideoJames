#include "Renderer.h"
#include "Graphics.h"
#include "Camera.h"

#include "../Trace.h"

#include <glad/glad.h>

#include <map>

Renderer::Renderer(std::shared_ptr<Camera>& cam) : camera(cam)
{
	trace_message("Creating Render System");

	shader = std::make_shared<Shader>("./data/shaders/vertex_shader.vert", "./data/shaders/frag_shader.frag");
}

Renderer::~Renderer()
{
	trace_message("Destroying Render System");
}

void Renderer::render(RenderList renderables)
{
	shader->use();

	// Set the camera transform
	shader->set_uniform("world_projection", camera->get_world_projection());
	shader->set_uniform("screen_projection", camera->get_sceen_projection());
	shader->set_uniform("view", camera->get_view());
	shader->set_uniform("rotation", camera->get_rotation());

	for (const auto& [e, transform, material, tag] : renderables.each())
	{
		if (material.has_mesh())
		{
			shader->set_uniform("model", transform.get_matrix());
			switch (tag.get_type())
			{
			case RenderType::World:
				shader->set_uniform("screen_or_world", true);
				break;
			case RenderType::Screen:
				shader->set_uniform("screen_or_world", false);
				break;
			default:
				break;
			}
			
			if (material.has_texture())
			{
				shader->set_uniform("textured", true);
				material.bind_texture();
				shader->set_uniform("texture0", 0); //static_cast<int>(mesh.texture->id) ?

				material.bind_mesh();
				material.unbind_mesh();

				material.unbind_texture();
			}
			else
			{
				shader->set_uniform("textured", false);
				shader->set_uniform("color", material.get_color());
				material.bind_mesh();
				material.unbind_mesh();
			}
		}
	}
	shader->unuse();
}
