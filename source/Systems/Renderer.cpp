#include "Renderer.h"
#include "Graphics.h"
#include "Camera.h"

#include "../Components/Transform.h"
#include "../Components/Texture.h"
#include "../Components/Mesh.h"

#include "../Trace.h"

#include <glad/glad.h>

Renderer::Renderer(std::shared_ptr<Camera>& cam) : camera(cam)
{
	trace_message("Creating Render System");

	shader = std::make_shared<Shader>("./shaders/vertex_shader.vert", "./shaders/frag_shader.frag");
}

Renderer::~Renderer()
{
	trace_message("Destroying Render System");
}

void Renderer::render(const entt::registry& renderables)
{
	// Set the camera transform
	//for (auto e : renderables)
	//{
	//	const auto& [transform] = renderables.get<Transform>(e);

	//	trace_message(transform.as_string());
	//}

	shader->use();

	// Set the camera transform
	shader->set_uniform("projection_view", camera->get_projection_view());

	const auto& view = renderables.view<Transform, Mesh>();
	for (auto e : view)
	{
		const auto& [transform, mesh] = view.get<Transform, Mesh>(e);

		shader->set_uniform("model", transform.get_world());
		//shader->set_uniform("model", glm::mat4(1));
		
		if (renderables.all_of<Texture>(e))
		{
			shader->set_uniform("textured", true);
			const auto& texture = renderables.get<Texture>(e);
			texture.bind();
			
			shader->set_uniform("texture0", static_cast<int>(0));

			mesh.bind();
			mesh.unbind();
			
			texture.unbind();
		}
		else
		{
			shader->set_uniform("textured", false);
			mesh.bind();
			mesh.unbind();
		}
	}
	shader->unuse();
}

void Renderer::update_camera(std::shared_ptr<Camera>& cam)
{
	camera = cam;
}
