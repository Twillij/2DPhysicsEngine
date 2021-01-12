#pragma once
#include <Renderer2D.h>
#include <glm/vec2.hpp>

using glm::vec2;

class PhysicsObject
{
public:
	PhysicsObject() {}
	virtual ~PhysicsObject() {}

	vec2 position;
	vec2 velocity;

	virtual void Update(float deltaTime) {}
	virtual void Draw(Renderer2D* renderer) {}
};

