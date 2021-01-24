#include "Line.h"
#include "LineCollider.h"

Line::Line(vec2 from, vec2 to)
{
	a = from;
	b = to;

	// set collider
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
