#include "Circle.h"
#include "CollisionDetection.h"
#include <Gizmos.h>

Circle::Circle(vec2 centre, float radius)
{
	position = centre;
	this->radius = radius;
}

void Circle::Draw(Renderer2D* renderer)
{
	Gizmos::add2DCircle(position, radius, 12, vec4(1, 1, 1, 0));
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
