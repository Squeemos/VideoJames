#pragma once

#include <glm/vec2.hpp>

class Transform;

class RigidBody
{
public:
	RigidBody();
	RigidBody(RigidBody&& other) noexcept;
	RigidBody& operator=(RigidBody&& other) noexcept;
	~RigidBody() = default;

	void move(const glm::vec2& f);
	void apply_force(const glm::vec2& f);
	void update(double dt, Transform& tform);

private:
	glm::vec2 __velocity;
	glm::vec2 __force;
	float __mass;
};