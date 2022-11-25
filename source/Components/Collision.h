#pragma once

#include <glm/vec2.hpp>
#include <memory>
#include "Transform.h"

enum class ColliderType
{
	None = 0,
	Point = 1,
	Line = 2,
	Circle = 3,
	Box = 4,
	Mesh = 5,
};

class ColliderBase
{
public:
	ColliderBase() {}

protected:

};

class Collider
{
public:
	Collider() : __type(ColliderType::None), __collider(nullptr) {}
	Collider(ColliderType type, std::shared_ptr<ColliderBase> collider) : __type(type), __collider(collider) { }

	static bool check_collision(Collider& first_collider, Transform& first_transform, Collider& second_collider, Transform& second_transform);

protected:
	ColliderType __type;
	std::shared_ptr<ColliderBase> __collider;
};

class PointCollider : public ColliderBase
{
public:
	PointCollider();

private:
};

class BoxCollider : public ColliderBase
{
public:
	BoxCollider();

private:
	glm::vec2 __box;
};