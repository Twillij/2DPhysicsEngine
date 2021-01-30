#pragma once
#include "PhysicsObject.h"
#include <glm/vec4.hpp>

class Circle : public PhysicsObject
{
public:
	Circle(vec2 centre = vec2(0), float radius = 5);
	~Circle() {}

	float radius;

	Collision CheckCollision(PhysicsObject* other) override;
	Collision CheckCollision(Line* line) override;
	Collision CheckCollision(Circle* circle) override;
	Collision CheckCollision(Box* box) override;

	void Draw(Renderer2D* renderer) override;
};
