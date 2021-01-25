#pragma once
#include <Renderer2D.h>
#include <glm/vec2.hpp>

using namespace aie;
using namespace glm;

class PhysicsWorld;
class Collider;
class Collision;

class PhysicsObject
{
public:
	PhysicsObject() {}
	virtual ~PhysicsObject();

	vec2 position = vec2(0);
	vec2 velocity = vec2(0);
	float restitution = 1;

	Collider* collider = nullptr;

	PhysicsWorld* GetWorld();
	void SetWorld(PhysicsWorld* world);

	float GetMass();
	float GetInverseMass();
	void SetMass(float mass);

	void ApplyForce(vec2 force);
	Collision CheckCollision(PhysicsObject* other);

	virtual void Update(float deltaTime);
	virtual void Draw(Renderer2D* renderer) {}

private:
	float mass = 0;
	PhysicsWorld* world = nullptr;
};
