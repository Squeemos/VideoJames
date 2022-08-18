#include "Renderer.h"

#include "../Components/Transform.h"

#include "../Trace.h"

#include <entt/entt.hpp>

Renderer::Renderer()
{
	trace_message("Creating Render System");
}

Renderer::~Renderer()
{
	trace_message("Destroying Render System");
}

void Renderer::render(const auto& renderables)
{
	// Set the camera transform
	for (auto e : renderables)
	{
		const auto& [transform] = renderables.get<Transform>(e);

		trace_message(transform.as_string());
	}
}
