#pragma once
#include "Collision.h"
#include "LineCollider.h"
#include "CircleCollider.h"
#include "BoxCollider.h"

namespace physics
{
	Collision Line2LineCollision(LineCollider* lineA, LineCollider* lineB);
	Collision Line2CircleCollision(LineCollider* line, CircleCollider* circle);
	Collision Line2BoxCollision(LineCollider* line, BoxCollider* box);
	Collision Circle2CircleCollision(CircleCollider* circleA, CircleCollider* circleB);
	Collision Circle2Box(CircleCollider* circle, BoxCollider* box);
	Collision Box2BoxCollision(BoxCollider* boxA, BoxCollider* boxB);
}