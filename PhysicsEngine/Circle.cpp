#include "Circle.h"
#include "CollisionDetection.h"
#include <Gizmos.h>
#include <iostream>

Circle::Circle(vec2 centre, float radius, float mass)
{
	this->position = centre;
	this->radius = radius;
	SetMass(mass);
}

void Circle::Draw(Renderer2D* renderer)
{
	vec2 line = vec2(sinf(rotation), cosf(rotation)) * radius;
	Gizmos::add2DCircle(position, radius, 12, vec4(1, 1, 1, 0));
	Gizmos::add2DLine(position, position + line, vec4(1, 1, 1, 1));
}

Collision Circle::CheckCollision(PhysicsObject* other)
{
	return other->CheckCollision(this);
}

Collision Circle::CheckCollision(Line* line)
{
	return physics::LineToCircle(line, this);
}

Collision Circle::CheckCollision(Circle* circle)
{
	return physics::CircleToCircle(this, circle);
}

Collision Circle::CheckCollision(Box* box)
{
	return physics::CircleToBox(this, box);
}

void Circle::SetMoment()
{
	moment = mass * radius * radius / 2;
}
