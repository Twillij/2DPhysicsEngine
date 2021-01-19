#include "LineCollider.h"
#include "CollisionDetection.h"
#include <glm/geometric.hpp>

LineCollider::LineCollider()
{
	type = ColliderType::Line;
}

Collision LineCollider::CheckCollision(LineCollider* line)
{
	return physics::Line2LineCollision(this, line);
}

Collision LineCollider::CheckCollision(CircleCollider* circle)
{
	return physics::Line2CircleCollision(this, circle);
}

Collision LineCollider::CheckCollision(BoxCollider* box)
{
	return physics::Line2BoxCollision(this, box);
}

float LineCollider::GetLength()
{
	return distance(pointA, pointB);
}

vec2 LineCollider::GetNormal()
{
	float distX = pointB.x - pointA.x;
	float distY = pointB.y - pointA.y;

	return normalize(vec2(-distY, distX));
}
