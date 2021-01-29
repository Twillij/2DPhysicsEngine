#pragma once
#include "PhysicsObject.h"
#include <glm/vec4.hpp>

class Line : public PhysicsObject
{
public:
	Line(vec2 from = vec2(0), vec2 to = vec2(0));
	~Line() {}

	vec2 a;
	vec2 b;

	float GetLength();
	vec2 GetNormal();

	Collision CheckCollision(PhysicsObject* other) override;
	Collision CheckCollision(Line* line) override;
	Collision CheckCollision(Circle* circle) override;
	Collision CheckCollision(Box* box) override;

	void Draw(Renderer2D* renderer) override;
};
