#include "Circle.h"
#include "CircleCollider.h"

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
	renderer->drawCircle(position.x, position.y, radius);
}
