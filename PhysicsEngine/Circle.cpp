#include "Circle.h"
#include "CircleCollider.h"
#include <Gizmos.h>

Circle::Circle(vec2 centre, float radius)
{
	position = centre;
	this->radius = radius;

	// set collider
	CircleCollider* circleCollider = new CircleCollider(this);
	circleCollider->centre = position;
	circleCollider->radius = radius;
	collider = circleCollider;
}

void Circle::Draw(Renderer2D* renderer)
{
	Gizmos::add2DCircle(position, radius, 12, vec4(1, 1, 1, 0));
}
