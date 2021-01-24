#include "CircleCollider.h"
#include "CollisionDetection.h"

CircleCollider::CircleCollider()
{
	type = ColliderType::Circle;
}

CircleCollider::CircleCollider(PhysicsObject* object) : Collider(object)
{
	type = ColliderType::Circle;
}

Collision CircleCollider::CheckCollision(LineCollider* line)
{
	return physics::LineToCircleCollision(line, this);
}

Collision CircleCollider::CheckCollision(CircleCollider* circle)
{
	return physics::CircleToCircleCollision(this, circle);
}

Collision CircleCollider::CheckCollision(BoxCollider* box)
{
	return physics::CircleToBox(this, box);
}
