#include "CollisionDetection.h"
#include <glm/vec2.hpp>
#include <glm/geometric.hpp>

using namespace glm;

Collision physics::Line2LineCollision(LineCollider* lineA, LineCollider* lineB)
{
	Collision collision(lineA, lineB);

	if (lineA && lineB)
	{
		vec2 pointA = lineA->pointA;
		vec2 pointB = lineA->pointB;
		vec2 pointC = lineB->pointA;
		vec2 pointD = lineB->pointB;

		// calculate the distance to the point of intersection
		float div = ((pointD.y - pointC.y) * (pointB.x - pointA.x) - (pointD.x - pointC.x) * (pointB.y - pointA.y));
		float uA = ((pointD.x - pointC.x) * (pointA.y - pointC.y) - (pointD.y - pointC.y) * (pointA.x - pointC.x)) / div;
		float uB = ((pointB.x - pointA.x) * (pointA.y - pointC.y) - (pointB.y - pointA.y) * (pointA.x - pointC.x)) / div;

		// if uA and uB is within 0-1, then a collision occurs
		if (uA >= 0 && uA <= 1 && uB >= 0 && uB <= 1)
		{
			collision.hasCollided = true;
			collision.pointA.x = pointA.x + (uA * (pointB.x - pointA.x));
			collision.pointA.y = pointA.y + (uA * (pointB.y - pointB.y));
			collision.pointB = collision.pointA;
		}
	}

	return collision;
}

Collision physics::Line2CircleCollision(LineCollider* line, CircleCollider* circle)
{
	Collision collision(line, circle);

	if (line && circle)
	{
		float distA = distance(line->pointA, circle->centre);
		float distB = distance(line->pointB, circle->centre);

		// if either ends of the line are inside the circle, then a collision occurs
		if (distA <= circle->radius || distB <= circle->radius)
		{
			collision.hasCollided = true;
			return collision;
		}

		vec2 distVec = circle->centre - line->pointA;
		vec2 lineVec = line->pointB - line->pointA;
		float lineLength = line->GetLength();

		// calculate the t that minimizes distance
		float t = dot(distVec, lineVec) / (lineLength * lineLength);

		// if the point is on the line segment
		if (t > 0 && t < 1)
		{
			// find the closest point to the circle's center
			vec2 closest(line->pointA.x + (t * lineVec.x), line->pointA.y + (t * lineVec.y));

			// find the perpendicular distance from the line to the circle's center
			float perpDist = distance(closest, circle->centre);

			// if the distance is less than the radius, then a collision occurs
			if (perpDist <= circle->radius)
			{
				collision.hasCollided = true;
				collision.pointA = closest;
				//collision.normal = line->GetNormal();
				//collision.pointB = circle->centre + (collision.normal * circle->radius);
				collision.depth = circle->radius - perpDist;
			}
		}
	}

	return collision;
}

Collision physics::Circle2CircleCollision(CircleCollider* circleA, CircleCollider* circleB)
{
	Collision collision(circleA, circleB);

	if (circleA && circleB)
	{
		float dist = distance(circleA->centre, circleB->centre);

		if (dist <= circleA->radius + circleB->radius)
		{
			collision.hasCollided = true;
		}
	}

	return collision;
}
