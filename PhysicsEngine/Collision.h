#pragma once
#include <glm/vec2.hpp>

using namespace glm;

class Collider;
class PhysicsObject;

class Collision
{
public:
	Collision(Collider* a, Collider* b);
	~Collision() {}

	PhysicsObject* objectA = nullptr;
	PhysicsObject* objectB = nullptr;

	vec2 pointA = vec2(0);
	vec2 pointB = vec2(0);
	vec2 normal = vec2(0);
	float depth = 0;

	bool hasCollided = false;
};
