#include "Renderer.h"
#include "Graphics.h"
#include "Camera.h"

#include "../Trace.h"

#include <glad/glad.h>

#include <map>

Renderer::Renderer()
{
	trace_message("Creating Render System");

	__shader = std::make_shared<Shader>("./data/shaders/vertex_shader.vert", "./data/shaders/frag_shader.frag");
}

Renderer::~Renderer()
{
	trace_message("Destroying Render System");
}

void Renderer::render(RenderList renderables, std::shared_ptr<Camera> camera)
{
	__shader->use();

	// Set the camera transform
	__shader->set_uniform("world_projection", camera->get_world_projection());
	__shader->set_uniform("screen_projection", camera->get_sceen_projection());
	__shader->set_uniform("view", camera->get_view());
	__shader->set_uniform("rotation", camera->get_rotation());

	for (const auto& [e, transform, material, tag] : renderables.each())
	{
		if (material.has_mesh())
		{
			__shader->set_uniform("model", transform.get_matrix());
			switch (tag.get_type())
			{
			case RenderType::World:
				__shader->set_uniform("screen_or_world", true);
				break;
			case RenderType::Screen:
				__shader->set_uniform("screen_or_world", false);
				break;
			default:
				break;
			}
			
			if (material.has_texture())
			{
				__shader->set_uniform("textured", true);
				material.bind_texture();
				__shader->set_uniform("texture0", 0); //static_cast<int>(mesh.texture->id) ?

				material.bind_mesh();
				material.unbind_mesh();

				material.unbind_texture();
			}
			else
			{
				__shader->set_uniform("textured", false);
				__shader->set_uniform("color", material.get_color());
				material.bind_mesh();
				material.unbind_mesh();
			}
		}
	}
	__shader->unuse();
}
