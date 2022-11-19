#pragma once

#include <glm/mat4x4.hpp>

// Camera class so we can look at things and move around the scene
class Camera
{
public:
	Camera();
	~Camera();

	// Gets the projection * view matrix for drawing
	const glm::mat4 get_projection() const;
	const glm::mat4 get_view() const;
	const glm::mat4 get_rotation() const;

	// So we can move the camera
	inline void translate(const glm::vec2& direction) { position.x += direction.x; position.y += direction.y; }
	inline void translate(const float& x, const float& y) { position.x += x; position.y += y; }
	inline void translate_x(const float& x) { position.x += x; }
	inline void translate_y(const float& y) { position.y += y; }
	inline void set_translation(const glm::vec2& pos) { position.x = pos.x; position.y = pos.y; }
	inline void set_translation(const float& x, const float& y) { position.x = x; position.y = y; }

	// So we can rotate the camera
	inline void rotate(const float& degrees) { rotation += degrees; }
	inline void set_rotation(const float& degrees) { rotation = degrees; }

	// Getter
	inline const glm::vec3& get_position() const { return position; }
	inline const glm::vec3& get_target() const { return target; }

	inline void zoom_x(const float& x) { zoom.x += x; }
	inline void zoom_y(const float& y) { zoom.y += y; }
	inline void reset_zoom() { zoom.x = 1.0f; zoom.y = 1.0f; }

	glm::vec2 mouse_to_world(const glm::vec2& mouse_screen);

private:
	// Position is where the center of the camera is
	// Target is where the camera is pointing (ideally this doesn't change that often)
	glm::vec3 position, target;

	// Size is how big of a rectangle the camera sees, bigger values = more stuff on screen
	glm::vec2 size;
	glm::vec2 zoom;
	
	// Clipping planes
	float near_clipping, far_clipping;
	float rotation;
};

