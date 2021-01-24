#pragma once
#include "Collider.h"

class LineCollider : public Collider
{
public:
	LineCollider();
	LineCollider(PhysicsObject* object);
	~LineCollider() {}

	vec2 a = vec2(0);
	vec2 b = vec2(0);

	Collision CheckCollision(LineCollider* line) override;
	Collision CheckCollision(CircleCollider* circle) override;
	Collision CheckCollision(BoxCollider* box) override;

	float GetLength();
	vec2 GetNormal();
};
