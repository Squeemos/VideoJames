#pragma once
#include <utility>

typedef float vec3[3];

class Entity
{
public:
	Entity();
	~Entity();
	void draw();
	void update(double dt);

	vec3 position;
};

