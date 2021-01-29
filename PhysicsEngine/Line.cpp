#include "Line.h"
#include "CollisionDetection.h"
#include <Gizmos.h>
#include <glm/geometric.hpp>

Line::Line(vec2 from, vec2 to)
{
	a = from;
	b = to;
}

float Line::GetLength()
{
	return distance(a, b);
}

vec2 Line::GetNormal()
{
	float distX = b.x - a.x;
	float distY = b.y - a.y;

	return normalize(vec2(-distY, distX));
}

Collision Line::CheckCollision(PhysicsObject* other)
{
	return other->CheckCollision(this);
}

Collision Line::CheckCollision(Line* line)
{
	return physics::LineToLine(this, line);
}

Collision Line::CheckCollision(Circle* circle)
{
	return physics::LineToCircle(this, circle);
}

Collision Line::CheckCollision(Box* box)
{
	return physics::LineToBox(this, box);
}

void Line::Draw(Renderer2D* renderer)
{
	Gizmos::add2DLine(a, b, vec4(1, 1, 1, 0));
}
