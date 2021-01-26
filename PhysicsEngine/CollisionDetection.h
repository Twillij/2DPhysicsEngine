#pragma once
#include "Collision.h"
#include "Line.h"
#include "Circle.h"
#include "Box.h"

namespace physics
{
	Collision LineToLine(Line* lineA, Line* lineB);
	Collision LineToCircle(Line* line, Circle* circle);
	Collision LineToBox(Line* line, Box* box);
	Collision CircleToCircle(Circle* circleA, Circle* circleB);
	Collision CircleToBox(Circle* circle, Box* box);
	Collision BoxToBox(Box* boxA, Box* boxB);
}