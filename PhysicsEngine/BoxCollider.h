#pragma once
#include "Collider.h"

class BoxCollider : public Collider
{
public:
	BoxCollider();
	~BoxCollider() {}

	vec2 centre = vec2(0);
	vec2 extents = vec2(0);
	
	Collision CheckCollision(LineCollider* line) override;
	Collision CheckCollision(CircleCollider* circle) override;
	Collision CheckCollision(BoxCollider* box) override;

	vec2* GetBoxCorners();
};
