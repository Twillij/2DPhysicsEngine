#pragma once
#include "Collider.h"
#include <glm/vec2.hpp>

class PointCollider : public Collider
{
public:
	PointCollider();
	~PointCollider() {}

	vec2 point;

	Collision CheckCollision(PointCollider* pointCollider);
	//Collision CheckCollision(LineCollider* lineCollider);
	//Collision CheckCollision(CircleCollider* circCollider);
	//Collision CheckCollision(RectangleCollider* rectCollider);
	//Collision CheckCollision(PolygonCollider* polyCollider);
};
