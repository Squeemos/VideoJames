#include "Entity.h"
#include "linmath.h"

#include <iostream>
#include <utility>


Entity::Entity() : position{0,0,0}, vertices{ -0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.0f,  0.5f, 0.0f }
{
	std::cout << "Making Entity" << std::endl;
}

Entity::~Entity()
{
}

std::pair<float*,unsigned long long> Entity::draw()
{
	std::cout << "Drawing " << sizeof(vertices) << std::endl;
	return std::make_pair<float*, unsigned long long>(vertices, sizeof(vertices));
}