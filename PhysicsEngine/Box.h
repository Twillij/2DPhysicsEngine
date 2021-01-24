#pragma once
#include "PhysicsObject.h"
#include <glm/vec4.hpp>

class Box : public PhysicsObject
{
public:
	Box(vec2 centre = vec2(0), vec2 extents = vec2(5));
	~Box() {}

	vec2 extents;

	void Draw(Renderer2D* renderer) override;
};
