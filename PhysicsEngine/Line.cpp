#include "Line.h"
#include "LineCollider.h"

Line::Line()
{
	LineCollider* lineCollider = new LineCollider();
	lineCollider->object = this;
	lineCollider->pointA = pointA;
	lineCollider->pointB = pointB;
	collider = lineCollider;
}

void Line::Draw(Renderer2D* renderer)
{
	renderer->drawLine(pointA.x, pointA.y, pointB.x, pointB.y);
}
