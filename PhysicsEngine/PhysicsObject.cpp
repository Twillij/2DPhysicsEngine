#include "PhysicsObject.h"
#include "Collider.h"
#include "Collision.h"

PhysicsObject::~PhysicsObject()
{
	if (collider)
		delete collider;
}

void PhysicsObject::ApplyForce(vec2 force)
{
	velocity += force / mass;
}

Collision PhysicsObject::CheckCollision(PhysicsObject* other)
{
	if (collider && other)
	{
		return collider->CheckCollision(other->collider);
	}

	return Collision(this, other);
}
