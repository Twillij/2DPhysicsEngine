#pragma once
#include "PhysicsObject.h"
#include <glm/vec4.hpp>

class Box : public PhysicsObject
{
public:
	Box(vec2 centre = vec2(0), vec2 extents = vec2(5), float mass = 1);
	~Box() {}

	vec2 extents;

	float GetWidth();
	float GetHeight();

	Collision CheckCollision(PhysicsObject* other) override;
	Collision CheckCollision(Line* line) override;
	Collision CheckCollision(Circle* circle) override;
	Collision CheckCollision(Box* box) override;

	void Draw(Renderer2D* renderer) override;

protected:
	void SetMoment() override;
};
