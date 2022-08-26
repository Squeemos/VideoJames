#pragma once

#include <glm/mat4x4.hpp>

// Camera class so we can look at things and move around the scene
class Camera
{
public:
	Camera();
	~Camera();

	// Gets the projection * view matrix for drawing
	const glm::mat4 get_projection_view() const;

	// So we can move and rotate the camera
	void translate(const glm::vec2& direction);
	void rotate(const float& degrees);

private:
	// Position is where the center of the camera is
	// Target is where the camera is pointing (ideally this doesn't change that often)
	glm::vec3 position, target;

	// Size is how big of a rectangle the camera sees, bigger values = more stuff on screen
	glm::vec2 size;
	
	// Clipping planes
	float near_clipping, far_clipping;
	float rotation;
};

