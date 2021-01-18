#pragma once
#include "Collision.h"
#include "PointCollider.h"
#include "LineCollider.h"
#include "CircleCollider.h"

namespace physics
{
	Collision Point2PointCollision(PointCollider* pointColliderA, PointCollider* pointColliderB);
	//Collision Point2LineCollision(PointCollider* pointCollider, LineCollider* lineCollider);
	//Collision Point2CircleCollision(PointCollider* pointCollider, CircleCollider* circCollider);
	Collision Line2LineCollision(LineCollider* lineColliderA, LineCollider* lineColliderB);
	Collision Line2CircleCollision(LineCollider* lineCollider, CircleCollider* circCollider);
}