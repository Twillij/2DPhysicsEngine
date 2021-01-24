#pragma once
#include "PhysicsObject.h"
class Line : public PhysicsObject
{
public:
	Line(vec2 from = vec2(0), vec2 to = vec2(0));
	~Line() {}

	vec2 a;
	vec2 b;

	void Draw(Renderer2D* renderer) override;
};
