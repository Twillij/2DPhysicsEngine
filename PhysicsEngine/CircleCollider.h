#pragma once
#include "Collider.h"

class CircleCollider : public Collider
{
public:
	CircleCollider();
	~CircleCollider() {}

	vec2 centre = vec2(0);
	float radius = 0;

	Collision CheckCollision(LineCollider* line) override;
	Collision CheckCollision(CircleCollider* circle) override;
	//Collision CheckCollision(RectangleCollider* other) override;
	//Collision CheckCollision(PolygonCollider* other) override;
};
