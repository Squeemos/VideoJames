#include "Collision.h"
#include "../Trace.h"
#include <glm/gtx/rotate_vector.hpp>
#include <limits>
#include <numbers>

inline constexpr float pi = std::numbers::pi_v<float>;
inline constexpr float tolerance = .00001f;

inline static glm::vec2 scalar_triple_product(const glm::vec2& a, const glm::vec2& b, const glm::vec2& c)
{
	return b * glm::dot(a, c) - a * glm::dot(b, c);
}

static glm::vec2 support(Polytope polytope, glm::vec2 vector)
{
	float max_dp = -std::numeric_limits<float>::infinity();
	glm::vec2 best = glm::vec2(0);
	for (glm::vec2 point : polytope)
	{
		float dot = glm::dot(point, vector);
		if (dot > max_dp)
		{
			max_dp = dot;
			best = point;
		}
	}

	return best;
}

static glm::vec2 support_2(Polytope polytope_1, Polytope polytope_2, glm::vec2 vector)
{
	glm::vec2 first = support(polytope_1, vector);
	glm::vec2 second = support(polytope_2, -vector);

	return first - second;
}

//static unsigned support_index(Polytope polytope, glm::vec2 vector)
//{
//	float max_dp = -std::numeric_limits<float>::infinity();
//	unsigned index = 0;
//	for (unsigned i = 0; i < polytope.size(); ++i)
//	{
//		float dot = glm::dot(polytope[i], vector);
//		if (dot > max_dp)
//		{
//			max_dp = dot;
//			index = i;
//		}
//	}
//
//	return index;
//}

CollisionInfo Collider::check_collision(Collider& first_collider, Transform& first_transform, Collider& second_collider, Transform& second_transform)
{
	glm::vec2 first_translation = first_transform.get_translation();
	glm::vec2 second_translation = second_transform.get_translation();

	float distance = glm::distance(first_translation, second_translation);

	if (first_collider.__type == ColliderType::None || second_collider.__type == ColliderType::None)
	{
		return CollisionInfo();
	}
	else if (first_collider.__type == ColliderType::Point && second_collider.__type == ColliderType::Point)
	{
		return CollisionInfo();
	}
	else if (first_collider.__type == ColliderType::Point && second_collider.__type == ColliderType::Circle)
	{
		return CollisionInfo(distance <= std::static_pointer_cast<CircleCollider>(second_collider.__collider)->get_radius());
	}
	else if (first_collider.__type == ColliderType::Circle && second_collider.__type == ColliderType::Point)
	{
		return CollisionInfo(distance <= std::static_pointer_cast<CircleCollider>(first_collider.__collider)->get_radius());
	}
	else
	{
		Polytope p1 = first_collider.__collider->populate_polytope(first_transform);
		Polytope p2 = second_collider.__collider->populate_polytope(second_transform);

		glm::vec2 a = support_2(p1, p2, glm::vec2(1.0f, 1.0f));
		glm::vec2 v = -a;
		glm::vec2 b = support_2(p1, p2, v);

		// Second point fails, no collision
		if (glm::dot(b, v) <= 0)
			return CollisionInfo();

		glm::vec2 ab = b - a;
		v = scalar_triple_product(ab, -a, ab);
		while (true)
		{
			glm::vec2 c = support_2(p1, p2, v);
			// Third point fails, no collision
			if (glm::dot(c, v) <= 0)
				return CollisionInfo();

			glm::vec2 c0 = -c;
			glm::vec2 cb = b - c;
			glm::vec2 ca = a - c;
			glm::vec2 cb_perp = scalar_triple_product(ca, cb, cb);
			glm::vec2 ca_perp = scalar_triple_product(cb, ca, ca);

			if (glm::dot(ca_perp, c0) > tolerance)
			{
				b = c;
				v = ca_perp;
			}
			else if (glm::dot(cb_perp, c0) > tolerance)
			{
				a = c;
				v = cb_perp;
			}
			else
				return CollisionInfo(a, b, c);
		}
	}

	return CollisionInfo();
}

CircleCollider::CircleCollider() : __radius(1.0f), __number_of_samples(16)
{
}

CircleCollider::CircleCollider(const float& r) : __radius(r), __number_of_samples(16)
{
}

CircleCollider::CircleCollider(const float& r, unsigned n_samples) : __radius(r), __number_of_samples(n_samples)
{
}

float CircleCollider::get_radius() const
{
	return __radius;
}

Polytope CircleCollider::populate_polytope(const Transform& t)
{
	glm::vec2 translation = t.get_translation();
	Polytope p(__number_of_samples);
	float theta = 2.0f * pi / __number_of_samples;

	for (unsigned i = 0; i < __number_of_samples; ++i)
	{
		p[i].x = __radius * cos(theta * i) + translation.x;
		p[i].y = __radius * sin(theta * i) + translation.y;
	}

	return p;
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

glm::vec2 BoxCollider::get_bounding_box() const
{
	return __box;
}

Polytope BoxCollider::populate_polytope(const Transform& t)
{
	glm::vec2 translation = t.get_translation();
	Polytope p(4);

	float rotation = glm::radians(t.get_rotation());
	glm::vec2 cos_vec = __box * cos(rotation);
	glm::vec2 sin_vec = __box * sin(rotation);

	p[0].x = translation.x + cos_vec.x - sin_vec.y;
	p[0].y = translation.y + sin_vec.x + cos_vec.y;

	p[1].x = translation.x - cos_vec.x - sin_vec.y;
	p[1].y = translation.y - sin_vec.x + cos_vec.y;

	p[2].x = translation.x - cos_vec.y + sin_vec.y;
	p[2].y = translation.y - sin_vec.x - cos_vec.y;

	p[3].x = translation.x + cos_vec.x + sin_vec.y;
	p[3].y = translation.y + sin_vec.x - cos_vec.y;

	return p;
}

PointCollider::PointCollider()
{
}

Polytope PointCollider::populate_polytope(const Transform& t)
{
	return Polytope{ t.get_translation() };
}

CollisionInfo::CollisionInfo() : collided(false), vectors()
{
}

CollisionInfo::CollisionInfo(bool c) : collided(c), vectors()
{
}

CollisionInfo::CollisionInfo(glm::vec2& a, glm::vec2& b, glm::vec2& c) : collided(true)
{
	vectors[0] = a;
	vectors[1] = b;
	vectors[2] = c;
}
