#include "Collision.h"
#include "../Trace.h"

bool Collider::check_collision(Collider& first_collider, Transform& first_transform, Collider& second_collider, Transform& second_transform)
{
	glm::vec2 first_translation = first_transform.get_translation();
	glm::vec2 second_translation = second_transform.get_translation();

	float distance = glm::distance(first_translation, second_translation);

	if (first_collider.__type == ColliderType::None || second_collider.__type == ColliderType::None)
	{
		return false;
	}
	else if (first_collider.__type == ColliderType::Point && second_collider.__type == ColliderType::Point)
	{
		return false;
	}
	else if (first_collider.__type == ColliderType::Point && second_collider.__type == ColliderType::Circle)
	{
		float radius = std::static_pointer_cast<CircleCollider>(second_collider.__collider)->get_radius();
		return distance <= radius;
	}
	else if (first_collider.__type == ColliderType::Circle && second_collider.__type == ColliderType::Point)
	{
		float radius = std::static_pointer_cast<CircleCollider>(first_collider.__collider)->get_radius();
		return distance <= radius;
	}
	else if (first_collider.__type == ColliderType::Point && second_collider.__type == ColliderType::Box)
	{
		glm::vec2 second_bb = std::static_pointer_cast<BoxCollider>(second_collider.__collider)->get_bounding_box();
		float second_length = glm::length(second_bb);
		if (distance > second_length)
			return false;

		bool x = std::abs(first_translation.x - second_translation.x) <= second_bb.x;
		bool y = std::abs(first_translation.y - second_translation.y) <= second_bb.y;
		return x && y;
	}
	else if (first_collider.__type == ColliderType::Box && second_collider.__type == ColliderType::Point)
	{
		glm::vec2 first_bb = std::static_pointer_cast<BoxCollider>(first_collider.__collider)->get_bounding_box();
		float first_length = glm::length(first_bb);
		if (distance > first_length)
			return false;

		bool x = std::abs(first_translation.x - second_translation.x) <= first_bb.x;
		bool y = std::abs(first_translation.y - second_translation.y) <= first_bb.y;
		return x && y;
	}
	else if (first_collider.__type == ColliderType::Circle && second_collider.__type == ColliderType::Circle)
	{
		float first_radius = std::static_pointer_cast<CircleCollider>(first_collider.__collider)->get_radius();
		float second_radius = std::static_pointer_cast<CircleCollider>(second_collider.__collider)->get_radius();

		return first_radius + second_radius <= distance;
	}
	else if (first_collider.__type == ColliderType::Box && second_collider.__type == ColliderType::Box)
	{
		// Very simple AABB that doesn't take into account the direction of collision
		// or the rest of AABB
		glm::vec2 first_bb = std::static_pointer_cast<BoxCollider>(first_collider.__collider)->get_bounding_box();
		glm::vec2 second_bb = std::static_pointer_cast<BoxCollider>(second_collider.__collider)->get_bounding_box();

		float left_length = glm::length(first_bb);
		float second_length = glm::length(second_bb);
		if (left_length + second_length <= distance)
			return false;
		
		bool x = std::abs(first_translation.x - second_translation.x) <= (first_bb.x + second_bb.x);
		bool y = std::abs(first_translation.y - second_translation.y) <= (first_bb.y + second_bb.y);

		return x && y;
	}

	return false;
}

LineCollider::LineCollider()
{
}

CircleCollider::CircleCollider() : __radius(1.0f)
{
}

CircleCollider::CircleCollider(const float& r) : __radius(r)
{
}

float CircleCollider::get_radius() const
{
	return __radius;
}

BoxCollider::BoxCollider() : __box(10.0f, 10.0f)
{
}

BoxCollider::BoxCollider(const glm::vec2& bounding_box)
{
	__box = bounding_box;
}

BoxCollider::BoxCollider(const float& bb_x, const float& bb_y)
{
	__box.x = bb_x;
	__box.y = bb_y;
}

PointCollider::PointCollider()
{
}
