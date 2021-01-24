#include "Line.h"
#include "LineCollider.h"
#include <Gizmos.h>

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
	Gizmos::add2DLine(a, b, vec4(1, 1, 1, 0));
}
