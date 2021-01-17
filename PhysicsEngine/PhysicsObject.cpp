#include "PhysicsObject.h"

void PhysicsObject::ApplyForce(vec2 force)
{
	velocity += force / mass;
}
