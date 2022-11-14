#include "RigidBody.h"
#include "../Components/Transform.h"

RigidBody::RigidBody(Transform* tform) : transform(tform), old_position(tform->get_translation()), velocity(0, 0), force(0, 0), mass(1.0)
{
}

RigidBody::RigidBody(RigidBody&& other) noexcept : transform(other.transform), old_position(other.transform->get_translation()), velocity(other.velocity), force(other.force), mass(other.mass)
{
}

RigidBody& RigidBody::operator=(RigidBody&& other) noexcept
{
	transform = other.transform;
	old_position = other.transform->get_translation();
	velocity = other.velocity;
	force = other.force;
	mass = other.mass;
	return *this;
}

void RigidBody::move(const glm::vec2& f)
{
	old_position = transform->get_translation();
	transform->translate(f);
}

void RigidBody::apply_force(const glm::vec2& f)
{
	force.x = f.x;
	force.y = f.y;
}

void RigidBody::update(double dt)
{
	float float_dt = static_cast<float>(dt);
	old_position = transform->get_translation();

	velocity += force / mass * float_dt;
	transform->translate(velocity * float_dt);
	
	force.x = 0;
	force.y = 0;
}
