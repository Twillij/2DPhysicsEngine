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
	//Collision CheckCollision(CircleCollider* circle) = 0;
	Collision CheckCollision(BoxCollider* box) override;
	//Collision CheckCollision(PolygonCollider* polygon) = 0;

	vec2* GetBoxCorners();
};
