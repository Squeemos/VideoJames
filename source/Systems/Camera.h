#pragma once

#include <glm/mat4x4.hpp>
#include <algorithm>

constexpr float min_camera_zoom = 0.00001f;

// Camera class so we can look at things and move around the scene
class Camera
{
public:
	Camera();
	~Camera();

	// Gets the projection * view matrix for drawing
	const glm::mat4 get_world_projection() const;
	const glm::mat4 get_sceen_projection() const;
	const glm::mat4 get_view() const;
	const glm::mat4 get_rotation() const;

	// So we can move the camera
	inline void translate(const glm::vec2& direction) { __position.x += direction.x; __position.y += direction.y; }
	inline void translate(const float& x, const float& y) { __position.x += x; __position.y += y; }
	inline void translate_x(const float& x) { __position.x += x; }
	inline void translate_y(const float& y) { __position.y += y; }
	inline void set_translation(const glm::vec2& pos) { __position.x = pos.x; __position.y = pos.y; }
	inline void set_translation(const float& x, const float& y) { __position.x = x; __position.y = y; }

	// So we can rotate the camera
	inline void rotate(const float& degrees) { __rotation += degrees; }
	inline void set_rotation(const float& degrees) { __rotation = degrees; }

	// Getter
	inline const glm::vec3& get_position() const { return __position; }
	inline const glm::vec3& get_target() const { return __target; }

	// Stuff the zoom the camera in/out
	inline void zoom_x(const float& x) { __zoom.x = std::max(min_camera_zoom, __zoom.x + x); }
	inline void zoom_y(const float& y) { __zoom.y = std::max(min_camera_zoom, __zoom.y + y); }
	inline void set_zoom_x(const float& x) { __zoom.x = x; }
	inline void set_zoom_y(const float& y) { __zoom.y = y; }
	inline void reset_zoom() { __zoom.x = 1.0f; __zoom.y = 1.0f; }

	glm::vec2 mouse_to_world(const glm::vec2& mouse_screen) const;
	glm::vec2 mouse_to_screen(const glm::vec2& mouse_screen) const;

private:
	// Position is where the center of the camera is
	// Target is where the camera is pointing (ideally this doesn't change that often)
	glm::vec3 __position, __target;

	// Size is how big of a rectangle the camera sees, bigger values = more stuff on screen
	glm::vec2 __size;
	glm::vec2 __zoom;
	
	// Clipping planes
	float __near_clipping, __far_clipping;
	float __rotation;
};

