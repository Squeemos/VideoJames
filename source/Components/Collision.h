#pragma once

#include <glm/vec2.hpp>
#include <memory>
#include <vector>
#include "Transform.h"

typedef std::vector<glm::vec2> Polytope;

enum class ColliderType
{
	None = 0,
	Point = 1,
	Circle = 2,
	Box = 3,
};

class CollisionInfo
{
public:
	CollisionInfo();
	CollisionInfo(bool c);
	CollisionInfo(glm::vec2& a, glm::vec2& b, glm::vec2& c);

	bool collided;
	glm::vec2 vectors[3];
};

class ColliderBase
{
public:
	ColliderBase() {}
	virtual Polytope populate_polytope(const Transform& t) = 0;

protected:

};

class Collider
{
public:
	Collider() : __type(ColliderType::None), __collider(nullptr) {}
	Collider(ColliderType type, std::shared_ptr<ColliderBase> collider) : __type(type), __collider(collider) { }

	static CollisionInfo check_collision(Collider& first_collider, Transform& first_transform, Collider& second_collider, Transform& second_transform);

protected:
	ColliderType __type;
	std::shared_ptr<ColliderBase> __collider;
};

class PointCollider : public ColliderBase
{
public:
	PointCollider();
	Polytope populate_polytope(const Transform& t);

private:
};

class CircleCollider : public ColliderBase
{
public:
	CircleCollider();
	CircleCollider(const float& r);
	CircleCollider(const float& r, unsigned n_samples);
	float get_radius() const;
	Polytope populate_polytope(const Transform& t);

private:
	float __radius;
	unsigned __number_of_samples;
};

class BoxCollider : public ColliderBase
{
public:
	BoxCollider();
	BoxCollider(const glm::vec2& bounding_box);
	BoxCollider(const float& bb_x, const float& bb_y);
	glm::vec2 get_bounding_box() const;
	Polytope populate_polytope(const Transform& t);

private:
	glm::vec2 __box;
};