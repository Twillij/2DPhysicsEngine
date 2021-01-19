#pragma once
#include "Collider.h"

class LineCollider : public Collider
{
public:
	LineCollider();
	~LineCollider() {}

	vec2 pointA = vec2(0);
	vec2 pointB = vec2(0);

	Collision CheckCollision(LineCollider* line) override;
	Collision CheckCollision(CircleCollider* circle) override;
	Collision CheckCollision(BoxCollider* box) override;
	//Collision CheckCollision(PolygonCollider* polyCollider) override;

	float GetLength();
	vec2 GetNormal();
};
