#pragma once
#include "Collision.h"
#include "LineCollider.h"
#include "CircleCollider.h"
#include <glm/vec2.hpp>

namespace physics
{
	Collision Line2LineCollision(LineCollider* lineColliderA, LineCollider* lineColliderB);
	Collision Line2CircleCollision(LineCollider* lineCollider, CircleCollider* circCollider);
}