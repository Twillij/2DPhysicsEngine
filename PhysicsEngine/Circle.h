#pragma once
#include "PhysicsObject.h"
#include <glm/vec4.hpp>

class Circle : public PhysicsObject
{
public:
	Circle(vec2 centre = vec2(0), float radius = 10);
	~Circle() {}

	float radius;

	void Draw(Renderer2D* renderer) override;
};
