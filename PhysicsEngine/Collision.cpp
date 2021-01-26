#include "Collision.h"
#include <glm/geometric.hpp>

Collision::Collision(PhysicsObject* a, PhysicsObject* b)
{
	objectA = a;
	objectB = b;
}
