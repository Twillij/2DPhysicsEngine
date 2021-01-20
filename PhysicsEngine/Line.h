#pragma once
#include "PhysicsObject.h"
class Line : public PhysicsObject
{
public:
	Line();
	~Line() {}

	vec2 pointA = vec2(0);
	vec2 pointB = vec2(0);

	void Draw(Renderer2D* renderer) override;
};
