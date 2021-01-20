#include "Circle.h"
#include "CircleCollider.h"

Circle::Circle()
{
	CircleCollider* circleCollider = new CircleCollider();
	circleCollider->object = this;
	circleCollider->centre = position;
	circleCollider->radius = radius;
	collider = circleCollider;
}

void Circle::Draw(Renderer2D* renderer)
{
	renderer->drawCircle(position.x, position.y, radius);
}
