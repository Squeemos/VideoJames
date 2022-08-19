#pragma once

#include <entt/entt.hpp>

#include <memory>

class Shader;
class Camera;

class Renderer
{
public:
	Renderer(std::shared_ptr<Camera>& cam);
	~Renderer();

	void render(const entt::registry& renderables);
	void update_camera(std::shared_ptr<Camera>& cam);

private:
	std::shared_ptr<Shader> shader;
	std::shared_ptr<Camera> camera;
};

