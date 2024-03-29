#include "CollisionDetection.h"
#include <glm/vec2.hpp>
#include <glm/geometric.hpp>
#include <iostream>
#include <vector>

using namespace glm;
using namespace std;

Collision physics::LineToLine(Line* lineA, Line* lineB)
{
	Collision collision(lineA, lineB);

	if (lineA && lineB)
	{
		vec2 a = lineA->a;
		vec2 b = lineA->b;
		vec2 pointC = lineB->a;
		vec2 pointD = lineB->b;

		// calculate the distance to the point of intersection
		float div = ((pointD.y - pointC.y) * (b.x - a.x) - (pointD.x - pointC.x) * (b.y - a.y));
		float uA = ((pointD.x - pointC.x) * (a.y - pointC.y) - (pointD.y - pointC.y) * (a.x - pointC.x)) / div;
		float uB = ((b.x - a.x) * (a.y - pointC.y) - (b.y - a.y) * (a.x - pointC.x)) / div;

		// if uA and uB is within 0-1, then a collision occurs
		if (uA >= 0 && uA <= 1 && uB >= 0 && uB <= 1)
		{
			collision.hasCollided = true;
		}
	}

	return collision;
}

Collision physics::LineToCircle(Line* line, Circle* circle)
{
	Collision collision(line, circle);

	if (line && circle)
	{
		float distA = distance(line->a, circle->position);
		float distB = distance(line->b, circle->position);

		// if either ends of the line are inside the circle, then a collision occurs
		if (distA <= circle->radius || distB <= circle->radius)
		{
			collision.hasCollided = true;
			return collision;
		}

		vec2 distVec = circle->position -line->a;
		vec2 lineVec = line->b - line->a;
		float lineLength = line->GetLength();

		// calculate the t that minimizes distance
		float t = dot(distVec, lineVec) / (lineLength * lineLength);

		// if the point is on the line segment
		if (t > 0 && t < 1)
		{
			// find the closest point on the line to the circle's center
			vec2 closest(line->a.x + (t * lineVec.x), line->a.y + (t * lineVec.y));

			// find the perpendicular distance from the line to the circle's center
			float perpDist = distance(closest, circle->position);

			// if the distance is less than the radius, then a collision occurs
			if (perpDist <= circle->radius)
			{
				collision.hasCollided = true;
				collision.penetration = circle->radius - perpDist;
			}
		}
	}

	return collision;
}

Collision physics::LineToBox(Line* line, Box* box)
{
	Collision collision(line, box);

	if (line && box)
	{
		vector<Collision> collisions;

		vec2 corners[4];
		corners[0] = vec2(box->position.x + box->extents.x, box->position.y + box->extents.y);
		corners[1] = vec2(box->position.x + box->extents.x, box->position.y - box->extents.y);
		corners[2] = vec2(box->position.x - box->extents.x, box->position.y - box->extents.y);
		corners[3] = vec2(box->position.x - box->extents.x, box->position.y + box->extents.y);

		for (int i = 0; i < 4; ++i)
		{
			Line boxEdge;

			// create line colliders from the four corners of the box
			int j = (i + 1 < 4) ? i + 1 : 0;
			boxEdge.a = corners[i];
			boxEdge.b = corners[j];

			// check collision against each side of the box
			Collision lineCollision = LineToLine(line, &boxEdge);

			if (lineCollision.hasCollided)
			{
				collision.hasCollided = true;
			}
		}
	}

	return collision;
}

Collision physics::CircleToCircle(Circle* circleA, Circle* circleB)
{
	Collision collision(circleA, circleB);

	if (circleA && circleB)
	{
		float dist = distance(circleA->position, circleB->position);
		float rSum = circleA->radius + circleB->radius;

		// if the circle is in the same position
		if (dist == 0.0f)
		{
			collision.hasCollided = true;
			collision.penetration = circleA->radius;
			collision.normal = vec2(1, 0);
			collision.contactA = circleA->position;
			collision.contactB = circleB->position;
		}
		// if the circle is colliding but not in the same position
		else if (dist <= circleA->radius + circleB->radius)
		{
			collision.hasCollided = true;
			collision.penetration = rSum - dist;
			collision.normal = (circleB->position - circleA->position) / dist;
			collision.contactA = circleA->position + (collision.normal * circleA->radius);
			collision.contactB = circleB->position - (collision.normal * circleB->radius);
		}
	}

	return collision;
}

Collision physics::CircleToBox(Circle* circle, Box* box)
{
	Collision collision(circle, box);

	if (circle && box)
	{
		// calculate the distance vector from box to circle
		vec2 distVec = circle->position - box->position;

		// closest point on box to position of circle
		vec2 closest = distVec;

		// clamp point to edges of the box
		closest.x = clamp(closest.x, -box->extents.x, box->extents.x);
		closest.y = clamp(closest.y, -box->extents.y, box->extents.y);

		bool inside = false;

		if (distVec == closest)
		{
			// if the closest point has not been clamped, then the circle is inside the box
			inside = true;

			// find the closest axis
			if (abs(distVec.x) > abs(distVec.y))
			{
				// clamp to closest extent in that axis
				closest.x = (closest.x > 0) ? box->extents.x : -box->extents.x;
			}
			else
			{
				// clamp to closest extent in that axis
				closest.y = (closest.y > 0) ? box->extents.y : -box->extents.y;
			}
		}

		vec2 normal = distVec - closest;
		float normalLength = length(normal);

		// early out if the radius is shorter than the distance to the closest point
		// and circle is not inside box
		if (normalLength > circle->radius && !inside)
			return collision;

		// at this point collision is confirmed
		collision.hasCollided = true;

		// if the normal is (0, 0) then randomise the direction
		if (normal == vec2(0, 0))
		{
			srand(time(NULL));
			float exp = rand() % 2 + 1;
			normal.x = powf(-1, exp);
		}

		// collision normal needs to be flipped to point outside if circle is inside box
		collision.normal = (inside) ? normalize(normal) : -normalize(normal);
		collision.penetration = circle->radius - normalLength;
		collision.contactA = circle->position + collision.normal * circle->radius;
		collision.contactB = box->position + closest;
	}

	return collision;
}

Collision physics::BoxToBox(Box* boxA, Box* boxB)
{
	Collision collision(boxA, boxB);

	if (boxA && boxB)
	{
		// calculate the distance vector from A to B
		vec2 distVec = boxB->position - boxA->position;

		// calculate the overlap on the x axis
		float overlapX = boxA->extents.x + boxB->extents.x - abs(distVec.x);

		// SAT test on x axis
		if (overlapX > 0)
		{
			// calculate the overlap on the y axis
			float overlapY = boxA->extents.y + boxB->extents.y - abs(distVec.y);

			// SAT test on y axis
			if (overlapY > 0)
			{
				// at this point a collision is confirmed
				collision.hasCollided = true;

				// initialise the contact points as their own positions
				collision.contactA = boxA->position;
				collision.contactB = boxB->position;

				// determine which axis has the least penetration
				if (overlapX < overlapY)
				{
					// point towards B knowing that the distance vector points from A to B
					collision.normal = (distVec.x < 0) ? vec2(-1, 0) : vec2(1, 0);
					collision.penetration = overlapX;

					// if box A is to the left of box B, or vice versa
					// offset the contact points by their X extent
					if (boxA->position.x < boxB->position.x)
					{
						
						collision.contactA.x += boxA->extents.x;
						collision.contactB.x -= boxB->extents.x;
					}
					else
					{
						collision.contactA.x -= boxA->extents.x;
						collision.contactB.x += boxB->extents.x;
					}
				}
				else
				{
					// point towards B knowing that the distance vector points from A to B
					collision.normal = (distVec.y < 0) ? vec2(0, -1) : vec2(0, 1);
					collision.penetration = overlapY;

					// if box A is to the bottom of box B, or vice versa
					// offset the contact points by their Y extent
					if (boxA->position.x < boxB->position.x)
					{

						collision.contactA.y += boxA->extents.y;
						collision.contactB.y -= boxB->extents.y;
					}
					else
					{
						collision.contactA.y -= boxA->extents.y;
						collision.contactB.y += boxB->extents.y;
					}
				}
			}
		}
	}

	return collision;
}
