#include "Circle.h"
#include "CircleCollider.h"

Circle::Circle()
{
	CircleCollider* defaultCollider = new CircleCollider();
	defaultCollider->centre = position;
	defaultCollider->radius = radius;
	collider = defaultCollider;
}

Circle::~Circle()
{
	delete collider;
}

void Circle::Draw(Renderer2D* renderer)
{
	renderer->drawCircle(position.x, position.y, radius);
}
