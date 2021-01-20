#pragma once
#include "Collision.h"
#include "LineCollider.h"
#include "CircleCollider.h"
#include "BoxCollider.h"

namespace physics
{
	Collision LineToLineCollision(LineCollider* lineA, LineCollider* lineB);
	Collision LineToCircleCollision(LineCollider* line, CircleCollider* circle);
	Collision LineToBoxCollision(LineCollider* line, BoxCollider* box);
	Collision CircleToCircleCollision(CircleCollider* circleA, CircleCollider* circleB);
	Collision CircleToBox(CircleCollider* circle, BoxCollider* box);
	Collision BoxToBoxCollision(BoxCollider* boxA, BoxCollider* boxB);
}