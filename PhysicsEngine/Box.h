#pragma once
#include "PhysicsObject.h"
class Box : public PhysicsObject
{
public:
	Box();
	~Box() {}

	vec2 extents = vec2(0);

	void Draw(Renderer2D* renderer) override;
};
