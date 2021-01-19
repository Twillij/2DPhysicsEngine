#pragma once
#include <glm/vec2.hpp>

using namespace glm;

class PhysicsObject;
class Collision;
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
	virtual Collision CheckCollision(LineCollider* line) = 0;
	virtual Collision CheckCollision(CircleCollider* circle) = 0;
	virtual Collision CheckCollision(RectangleCollider* rectangle) = 0;
	virtual Collision CheckCollision(PolygonCollider* polygon) = 0;

protected:
	ColliderType type = ColliderType::None;
};
