#pragma once
#include <glm/vec2.hpp>

using namespace glm;

class PhysicsObject;
class Collision;
class PointCollider;
class LineCollider;
class CircleCollider;
class RectangleCollider;
class PolygonCollider;

class Collider
{
public:
	Collider() {}
	virtual ~Collider() {}

	enum class ColliderType
	{
		None,
		Point,
		Line,
		Circle,
		Rectangle,
		Polygon
	};

	PhysicsObject* object = nullptr;

	virtual Collision CheckCollision(Collider* other) = 0;
	virtual Collision CheckCollision(PointCollider* pointCollider) = 0;
	virtual Collision CheckCollision(LineCollider* lineCollider) = 0;
	virtual Collision CheckCollision(CircleCollider* circCollider) = 0;
	virtual Collision CheckCollision(RectangleCollider* rectCollider) = 0;
	virtual Collision CheckCollision(PolygonCollider* polyCollider) = 0;

protected:
	ColliderType type = ColliderType::None;
};
