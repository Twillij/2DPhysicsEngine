#include "LineCollider.h"
#include "CollisionDetection.h"
#include <glm/geometric.hpp>

LineCollider::LineCollider()
{
	type = ColliderType::Line;
}

Collision LineCollider::CheckCollision(LineCollider* line)
{
	return physics::LineToLineCollision(this, line);
}

Collision LineCollider::CheckCollision(CircleCollider* circle)
{
	return physics::LineToCircleCollision(this, circle);
}

Collision LineCollider::CheckCollision(BoxCollider* box)
{
	return physics::LineToBoxCollision(this, box);
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
