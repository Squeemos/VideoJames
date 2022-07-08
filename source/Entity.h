#pragma once

typedef float vec3[3];
typedef struct std::pair<typename _Ty1, typename _Ty2>;

class Entity
{
public:
	Entity();
	~Entity();
	std::pair<float*, unsigned long long> draw();

	vec3 position;
	float vertices[9];
};

