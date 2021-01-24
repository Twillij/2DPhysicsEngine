#pragma once
#include <glm/vec2.hpp>

using namespace glm;

class Collider;
class PhysicsObject;

class Collision
{
public:
	Collision(PhysicsObject* a, PhysicsObject* b);
	Collision(Collider* a, Collider* b);
	~Collision() {}

	PhysicsObject* objectA = nullptr;
	PhysicsObject* objectB = nullptr;

	bool hasCollided = false;
	vec2 a = vec2(0);
	vec2 b = vec2(0);
	vec2 normal = vec2(0);
	float depth = 0;
	
	vec2 CalculateNormal(bool setValue = true);
	float CalculateDepth(bool setValue = true);
};
