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
	std::multimap<float, entt::entity> render_list;

	for (const auto& [e, transform, material] : renderables.each())
		render_list.insert(std::pair<float, entt::entity>(transform.get_z_order(), e));

	shader->use();

	// Set the camera transform
	shader->set_uniform("projection_view", camera->get_projection_view());

	for (auto iterator = render_list.begin(); iterator != render_list.end(); ++iterator)
	{
		const auto& [transform, material] = renderables.get<Transform, Material>(iterator->second);
		if (material.has_mesh())
		{
			shader->set_uniform("model", transform.get_world());
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
	//for (const auto& [e, transform, material] : renderables.each())
	//{
	//	
	//}
	shader->unuse();
}
