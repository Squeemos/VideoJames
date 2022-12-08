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

class LineCollider : public ColliderBase
{
public:
	LineCollider();

private:

};

class CircleCollider : public ColliderBase
{
public:
	CircleCollider();
	CircleCollider(const float& r);
	float get_radius() const;

private:
	float __radius;
};

class BoxCollider : public ColliderBase
{
public:
	BoxCollider();
	BoxCollider(const glm::vec2& bounding_box);
	BoxCollider(const float& bb_x, const float& bb_y);
	glm::vec2 get_bounding_box() const { return __box; }

private:
	glm::vec2 __box;
};