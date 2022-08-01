#include "Scene.h"
#include "Trace.h"
#include "Camera.h"

Scene::Scene()
{
	send_trace_message("Creating Scene");
}

Scene::~Scene()
{
	send_trace_message("Destroying Scene");
	registry.clear();
}

Camera& Scene::get_camera()
{
	return *camera;
}
