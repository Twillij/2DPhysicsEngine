#include "LineCollider.h"
#include "CollisionDetection.h"
#include <glm/geometric.hpp>

LineCollider::LineCollider()
{
	type = ColliderType::Line;
}

LineCollider::LineCollider(PhysicsObject* object) : Collider(object)
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
	return distance(a, b);
}

vec2 LineCollider::GetNormal()
{
	float distX = b.x - a.x;
	float distY = b.y - a.y;

	return normalize(vec2(-distY, distX));
}
