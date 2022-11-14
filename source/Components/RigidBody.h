#pragma once

#include <glm/vec2.hpp>

class Transform;

class RigidBody
{
public:
	RigidBody() = delete;
	RigidBody(Transform* tform);
	RigidBody(RigidBody&& other) noexcept;
	RigidBody& operator=(RigidBody&& other) noexcept;
	~RigidBody() = default;

	void move(const glm::vec2& f);
	void apply_force(const glm::vec2& f);
	void update(double dt);

private:
	Transform* transform;
	glm::vec2 old_position;
	glm::vec2 velocity;
	glm::vec2 force;
	float mass;
};