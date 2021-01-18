#include "CollisionDetection.h"

Collision physics::Line2LineCollision(LineCollider* lineColliderA, LineCollider* lineColliderB)
{
	Collision collision(lineColliderA, lineColliderB);
	vec2 pointA = lineColliderA->pointA;
	vec2 pointB = lineColliderA->pointB;
	vec2 pointC = lineColliderB->pointA;
	vec2 pointD = lineColliderB->pointB;

	// calculate the distance to the point of intersection
	float div = ((pointD.y - pointC.y) * (pointB.x - pointA.x) - (pointD.x - pointC.x) * (pointB.y - pointA.y));
	float uA = ((pointD.x - pointC.x) * (pointA.y - pointC.y) - (pointD.y - pointC.y) * (pointA.x - pointC.x)) / div;
	float uB = ((pointB.x - pointA.x) * (pointA.y - pointC.y) - (pointB.y - pointA.y) * (pointA.x - pointC.x)) / div;

	if (uA >= 0 && uA <= 1 && uB >= 0 && uB <= 1)
	{
		collision.hasCollided = true;
		collision.pointA.x = pointA.x + (uA * (pointB.x - pointA.x));
		collision.pointA.y = pointA.y + (uA * (pointB.y - pointB.y));
	}

	return collision;
}

Collision physics::Line2CircleCollision(LineCollider* lineCollider, CircleCollider* circCollider)
{
	Collision collision(lineCollider, circCollider);



	return collision;
}
