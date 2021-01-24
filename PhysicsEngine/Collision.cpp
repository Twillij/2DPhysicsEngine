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

vec2 Collision::CalculateNormal(bool setValue)
{
	vec2 newNormal = normalize(b - a);
	
	if (setValue)
		normal = newNormal;

	return newNormal;
}

float Collision::CalculateDepth(bool setValue)
{
	float dist = distance(a, b);

	if (setValue)
		depth = dist;

	return dist;
}
