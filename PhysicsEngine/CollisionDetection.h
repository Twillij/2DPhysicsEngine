#pragma once
#include "Collision.h"
#include "LineCollider.h"
#include "CircleCollider.h"

namespace physics
{
	Collision Line2LineCollision(LineCollider* lineA, LineCollider* lineB);
	Collision Line2CircleCollision(LineCollider* line, CircleCollider* circle);
	Collision Circle2CircleCollision(CircleCollider* circleA, CircleCollider* circleB);
}