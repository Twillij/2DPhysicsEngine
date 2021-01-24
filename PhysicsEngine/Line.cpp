#include "Line.h"
#include "LineCollider.h"

Line::Line()
{
	LineCollider* lineCollider = new LineCollider();
	lineCollider->object = this;
	lineCollider->a = a;
	lineCollider->b = b;
	collider = lineCollider;
}

void Line::Draw(Renderer2D* renderer)
{
	renderer->drawLine(a.x, a.y, b.x, b.y);
}
