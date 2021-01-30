#include "Box.h"
#include "CollisionDetection.h"
#include <Gizmos.h>
#include <iostream>

Box::Box(vec2 centre, vec2 extents)
{
	this->position = centre;
	this->extents = extents;
}

vec2* Box::GetBoxCorners()
{
	vec2 corners[4];

	corners[0] = vec2(position.x + extents.x, position.y + extents.y);
	corners[1] = vec2(position.x + extents.x, position.y - extents.y);
	corners[2] = vec2(position.x - extents.x, position.y - extents.y);
	corners[3] = vec2(position.x - extents.x, position.y + extents.y);

	return &corners[0];
}

Collision Box::CheckCollision(PhysicsObject* other)
{
	return other->CheckCollision(this);
}

Collision Box::CheckCollision(Line* line)
{
	return physics::LineToBox(line, this);
}

Collision Box::CheckCollision(Circle* circle)
{
	return physics::CircleToBox(circle, this);
}

Collision Box::CheckCollision(Box* box)
{
	return physics::BoxToBox(this, box);
}

void Box::Draw(Renderer2D* renderer)
{
	Gizmos::add2DAABB(position, extents, vec4(1, 1, 1, 1));
}
