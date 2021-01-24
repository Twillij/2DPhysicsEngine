#pragma once
#include "PhysicsObject.h"
class Line : public PhysicsObject
{
public:
	Line();
	~Line() {}

	vec2 a = vec2(0);
	vec2 b = vec2(0);

	void Draw(Renderer2D* renderer) override;
};
