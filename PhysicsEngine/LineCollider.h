#pragma once
#include "Collider.h"

class LineCollider : public Collider
{
public:
	LineCollider();
	~LineCollider() {}

	vec2 pointA = vec2(0);
	vec2 pointB = vec2(0);

	Collision CheckCollision(LineCollider* lineCollider) override;
	Collision CheckCollision(CircleCollider* circCollider) override;
	//Collision CheckCollision(RectangleCollider* rectCollider) override;
	//Collision CheckCollision(PolygonCollider* polyCollider) override;

	float GetLength();
};