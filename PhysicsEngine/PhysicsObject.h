#pragma once
#include <Renderer2D.h>
#include <glm/vec2.hpp>

using namespace aie;
using namespace glm;

class PhysicsWorld;
class Collision;
class Line;
class Circle;
class Box;

class PhysicsObject
{
public:
	PhysicsObject() {}
	virtual ~PhysicsObject() {}

	vec2 position = vec2(0);
	vec2 velocity = vec2(0);
	float restitution = 0.5f;
	float staticFriction = 0.5f;
	float kineticFriction = 0.1f;

	PhysicsWorld* GetWorld();
	void SetWorld(PhysicsWorld* world);

	float GetMass();
	float GetInverseMass();
	void SetMass(float mass);

	void ApplyForce(vec2 force, float deltaTime);

	virtual void Update(float deltaTime);
	virtual void Draw(Renderer2D* renderer) {}

	virtual Collision CheckCollision(PhysicsObject* other);
	virtual Collision CheckCollision(Line* line) = 0;
	virtual Collision CheckCollision(Circle* circle) = 0;
	virtual Collision CheckCollision(Box* box) = 0;

private:
	float mass = 1;
	PhysicsWorld* world = nullptr;
};
