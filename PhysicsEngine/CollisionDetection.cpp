#include "CollisionDetection.h"
#include <glm/vec2.hpp>
#include <glm/geometric.hpp>
#include <vector>

using namespace glm;
using namespace std;

Collision physics::LineToLineCollision(LineCollider* lineA, LineCollider* lineB)
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

Collision physics::LineToCircleCollision(LineCollider* line, CircleCollider* circle)
{
	Collision collision(line, circle);

	if (line && circle)
	{
		float distA = distance(line->a, circle->centre);
		float distB = distance(line->b, circle->centre);

		// if either ends of the line are inside the circle, then a collision occurs
		if (distA <= circle->radius || distB <= circle->radius)
		{
			collision.hasCollided = true;
			return collision;
		}

		vec2 distVec = circle->centre - line->a;
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
			float perpDist = distance(closest, circle->centre);

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

Collision physics::LineToBoxCollision(LineCollider* line, BoxCollider* box)
{
	Collision collision(line, box);

	if (line && box)
	{
		vec2* corners = box->GetBoxCorners();
		vector<Collision> collisions;

		LineCollider lineCollider[4];
		lineCollider[0].a = corners[0];
		lineCollider[0].b = corners[1];
		lineCollider[1].a = corners[1];
		lineCollider[1].b = corners[2];

		
		for (int i = 0; i < 4; ++i)
		{
			// create line colliders from the four corners of the box
			int j = (i + 1 < 4) ? i + 1 : 0;
			lineCollider[i].a = corners[i];
			lineCollider[i].b = corners[j];

			// check collision against each side of the box
			Collision lineCollision = LineToLineCollision(line, &lineCollider[i]);

			if (lineCollision.hasCollided)
			{
				collision.hasCollided = true;
			}
		}
	}

	return collision;
}

Collision physics::CircleToCircleCollision(CircleCollider* circleA, CircleCollider* circleB)
{
	Collision collision(circleA, circleB);

	if (circleA && circleB)
	{
		float dist = distance(circleA->centre, circleB->centre);
		float rSum = circleA->radius + circleB->radius;

		// if the circle is in the same position
		if (dist)
		{
			collision.hasCollided = true;
			collision.penetration = circleA->radius;
			collision.normal = vec2(1, 0);
		}
		// if the circle is colliding but not in the same position
		else if (dist <= circleA->radius + circleB->radius)
		{	
			collision.hasCollided = true;
			collision.penetration = rSum - dist;
			collision.normal = (circleB->centre - circleA->centre) / dist;
		}
	}

	return collision;
}

Collision physics::CircleToBox(CircleCollider* circle, BoxCollider* box)
{
	Collision collision(circle, box);

	if (circle && box)
	{
		vec2 closest = circle->centre; // temp variable for the square's closest edges to the circle

		float boxLeft = box->centre.x - box->extents.x;
		float boxRight = box->centre.x + box->extents.x;
		float boxTop = box->centre.y + box->centre.y;
		float boxBot = box->centre.y - box->centre.y;

		// check which edges of the box are closest to the circle

		if (circle->centre.x < boxLeft)
			closest.x = boxLeft;
		else if (circle->centre.x > boxRight)
			closest.x = boxRight;

		if (circle->centre.y < boxBot)
			closest.y = boxBot;
		else if (circle->centre.y > boxTop)
			closest.y = boxTop;

		float dist = distance(closest, circle->centre);

		if (dist <= circle->radius)
		{
			collision.hasCollided = true;
		}
	}

	return collision;
}

Collision physics::BoxToBoxCollision(BoxCollider* boxA, BoxCollider* boxB)
{
	Collision collision(boxA, boxB);

	if (boxA && boxB)
	{
		// calculate the distance vector from A to B
		vec2 distVec = boxB->centre - boxA->centre;

		// calculate the overlap on the x axis
		float overlapX = boxA->extents.x + boxB->extents.x - abs(distVec.x);

		// SAT test on x axis
		if (overlapX > 0)
		{
			// at this point a collision would have already occured
			collision.hasCollided = true;

			// calculate the overlap on the y axis
			float overlapY = boxA->extents.y + boxB->extents.y - abs(distVec.y);

			// SAT test on y axis
			if (overlapY > 0)
			{
				// determine which axis has the least penetration
				if (overlapX > overlapY)
				{
					// point towards B knowing that the distance vector points from A to B
					collision.normal = (distVec.x < 0) ? vec2(-1, 0) : vec2(1, 0);
					collision.penetration = overlapX;
				}
				else
				{
					// point towards B knowing that the distance vector points from A to B
					collision.normal = (distVec.y < 0) ? vec2(0, -1) : vec2(0, 1);
					collision.penetration = overlapY;
				}
			}
		}
	}

	return collision;
}
