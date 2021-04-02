#include "Box.h"
#include "CollisionDetection.h"
#include <Gizmos.h>
#include <iostream>

Box::Box(vec2 centre, vec2 extents, float mass)
{
	this->position = centre;
	this->extents = extents;
	SetMass(mass);
}

float Box::GetWidth()
{
	return extents.x * 2;
}

float Box::GetHeight()
{
	return extents.y * 2;
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

void Box::SetMoment()
{
	float width = GetWidth();
	float height = GetHeight();
	moment = mass * (width * width + height * height) / 12;
}

void Box::Draw(Renderer2D* renderer)
{
	Gizmos::add2DAABB(position, extents, vec4(1, 1, 1, 1));
}
