#pragma once
#include <Renderer2D.h>
#include <glm/vec2.hpp>

using namespace aie;
using namespace glm;

class Collider;

class PhysicsObject
{
public:
	PhysicsObject() {}
	virtual ~PhysicsObject() {}

	vec2 position = vec2(0);
	vec2 velocity = vec2(0);
	float mass = 0;

	Collider* collider = nullptr;

	void ApplyForce(vec2 force);

	virtual void Update(float deltaTime) {}
	virtual void Draw(Renderer2D* renderer) {}
};