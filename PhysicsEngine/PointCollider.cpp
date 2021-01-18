#include "PointCollider.h"
#include "CollisionDetection.h"

PointCollider::PointCollider()
{
	type = ColliderType::Point;
}

Collision PointCollider::CheckCollision(PointCollider* pointCollider)
{
	return physics::Point2PointCollision(this, pointCollider);
}
