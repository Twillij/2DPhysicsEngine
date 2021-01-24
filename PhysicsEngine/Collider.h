#pragma once
#include <glm/vec2.hpp>

using namespace glm;

class PhysicsObject;
class Collision;
class LineCollider;
class CircleCollider;
class BoxCollider;
class PolygonCollider;

class Collider
{
public:
	Collider() {}
	Collider(PhysicsObject* object) : object(object) {}
	virtual ~Collider() {}

	enum class ColliderType
	{
		None,
		Line,
		Circle,
		Box,
		Polygon
	};

	PhysicsObject* object = nullptr;

	virtual Collision CheckCollision(Collider* other);
	virtual Collision CheckCollision(LineCollider* line) = 0;
	virtual Collision CheckCollision(CircleCollider* circle) = 0;
	virtual Collision CheckCollision(BoxCollider* box) = 0;
	//virtual Collision CheckCollision(PolygonCollider* polygon) = 0;

protected:
	ColliderType type = ColliderType::None;
};
