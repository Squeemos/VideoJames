#pragma once
#include <utility>

typedef float vec3[3];

class Entity
{
public:
	Entity();
	~Entity();
	void update(double dt);
	std::pair<float*, unsigned long long> draw();

	vec3 position;
	float vertices[18];
};

