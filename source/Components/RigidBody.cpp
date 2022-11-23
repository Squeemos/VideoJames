#include "RigidBody.h"
#include "../Components/Transform.h"

RigidBody::RigidBody() : __velocity(0, 0), __force(0, 0), __mass(1.0)
{
}

RigidBody::RigidBody(RigidBody&& other) noexcept :  __velocity(other.__velocity), __force(other.__force), __mass(other.__mass)
{
}

RigidBody& RigidBody::operator=(RigidBody&& other) noexcept
{
	__velocity = other.__velocity;
	__force = other.__force;
	__mass = other.__mass;
	return *this;
}

void RigidBody::move(const glm::vec2& f)
{
	f;
}

void RigidBody::apply_force(const glm::vec2& f)
{
	f;
}

void RigidBody::update(double dt, Transform& tform)
{
	dt;
	tform;
}
