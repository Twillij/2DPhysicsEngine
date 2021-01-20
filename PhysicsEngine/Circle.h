#pragma once
#include "PhysicsObject.h"

class Circle : public PhysicsObject
{
public:
	Circle();
	~Circle();

	float radius = 10;

	void Draw(Renderer2D* renderer) override;
};
