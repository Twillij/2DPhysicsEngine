#include "Collision.h"
#include "Collider.h"
#include <glm/geometric.hpp>

Collision::Collision(PhysicsObject* a, PhysicsObject* b)
{
	objectA = a;
	objectB = b;
}

Collision::Collision(Collider* a, Collider* b)
{
	objectA = a->object;
	objectB = b->object;
}
