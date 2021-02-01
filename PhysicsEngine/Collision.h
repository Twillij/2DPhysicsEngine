#pragma once
#include <glm/vec2.hpp>

using namespace glm;

class Collider;
class PhysicsObject;

class Collision
{
public:
	Collision(PhysicsObject* a, PhysicsObject* b);
	~Collision() {}

	PhysicsObject* objectA = nullptr;
	PhysicsObject* objectB = nullptr;

	bool hasCollided = false;
	vec2 contactA = vec2(0);
	vec2 contactB = vec2(0);
	float penetration = 0;
	vec2 normal = vec2(0);
};
