#pragma once
#include <Renderer2D.h>
#include <glm/vec2.hpp>

using namespace aie;
using namespace glm;

class PhysicsObject
{
public:
	PhysicsObject() {}
	virtual ~PhysicsObject() {}

	vec2 position = vec2(0);

	virtual void Update(float deltaTime) {}
	virtual void Draw(Renderer2D* renderer) {}
};
