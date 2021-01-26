#pragma once
#include "PhysicsObject.h"
#include <glm/vec4.hpp>

class Circle : public PhysicsObject
{
public:
	Circle(vec2 centre = vec2(0), float radius = 10);
	~Circle() {}

	float radius;

	Collision CheckCollision(Line* line) override;
	Collision CheckCollision(Circle* circle) override;
	Collision CheckCollision(Box* box) override;

	void Draw(Renderer2D* renderer) override;
};
