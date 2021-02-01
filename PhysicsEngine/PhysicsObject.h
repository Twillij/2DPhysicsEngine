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

	float rotation = 0;
	float angularVelocity = 0;

	PhysicsWorld* GetWorld();
	void SetWorld(PhysicsWorld* world);

	float GetMass();
	void SetMass(float mass);

	float GetInverseMass();
	float GetInverseMoment();

	void ApplyForce(vec2 force, vec2 contact);

	virtual void Update(float deltaTime);
	virtual void Draw(Renderer2D* renderer) {}

	virtual Collision CheckCollision(PhysicsObject* other) = 0;
	virtual Collision CheckCollision(Line* line) = 0;
	virtual Collision CheckCollision(Circle* circle) = 0;
	virtual Collision CheckCollision(Box* box) = 0;

protected:
	float mass = 1;
	float moment = 0;

	virtual void SetMoment() {}

private:
	PhysicsWorld* world = nullptr;
};
