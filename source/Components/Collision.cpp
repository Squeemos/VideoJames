#include "Collision.h"

BoxCollider::BoxCollider() : __box(10.0f, 10.0f)
{
}

PointCollider::PointCollider()
{
}

bool Collider::check_collision(Collider& first_collider, Transform& first_transform, Collider& second_collider, Transform& second_transform)
{
	if (first_collider.__type == ColliderType::None || second_collider.__type == ColliderType::None)
	{
		return false;
	}
	else if (first_collider.__type == ColliderType::Point && second_collider.__type == ColliderType::Point)
	{
		std::shared_ptr<PointCollider> first_cast = std::static_pointer_cast<PointCollider>(first_collider.__collider);
		std::shared_ptr<PointCollider> second_cast = std::static_pointer_cast<PointCollider>(second_collider.__collider);

		first_cast;
		second_cast;
	}

	first_transform;
	second_transform;

	return false;
}
