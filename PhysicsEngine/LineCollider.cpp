#include "LineCollider.h"
#include "Collision.h"
#include "CollisionDetection.h"

LineCollider::LineCollider()
{
	type = ColliderType::Line;
}

Collision LineCollider::CheckCollision(LineCollider* lineCollider)
{
	return physics::Line2LineCollision(this, lineCollider);
}

Collision LineCollider::CheckCollision(CircleCollider* circCollider)
{
	return physics::Line2CircleCollision(this, circCollider);
}
