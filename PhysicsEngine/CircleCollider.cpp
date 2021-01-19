#include "CircleCollider.h"
#include "CollisionDetection.h"

CircleCollider::CircleCollider()
{
	type = ColliderType::Circle;
}

Collision CircleCollider::CheckCollision(LineCollider* line)
{
	return physics::Line2CircleCollision(line, this);
}

Collision CircleCollider::CheckCollision(CircleCollider* circle)
{
	return physics::Circle2CircleCollision(this, circle);
}
