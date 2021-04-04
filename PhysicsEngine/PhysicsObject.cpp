#include "PhysicsObject.h"
#include "PhysicsWorld.h"
#include "Collision.h"
#include "Box.h"
#include <iostream>
#include <glm/geometric.hpp>

static const float LINEAR_THRESHOLD = 0.1f;
static const float ANGULAR_THRESHOLD = 0.01f;

PhysicsWorld* PhysicsObject::GetWorld()
{
	return world;
}

void PhysicsObject::SetWorld(PhysicsWorld* world)
{
	this->world = world;
}

float PhysicsObject::GetMass()
{
	return mass;
}

void PhysicsObject::SetMass(float mass)
{
	this->mass = (mass >= 0) ? mass : 0.0f;
	this->SetMoment();
}

float PhysicsObject::GetInverseMass()
{
	return (mass > 0) ? 1.0f / mass : 0.0f; 
}

float PhysicsObject::GetInverseMoment()
{
	return (moment > 0) ? 1.0f / moment : 0.0f;
}

void PhysicsObject::ApplyForce(vec2 force, vec2 contact)
{
	velocity += force * GetInverseMass();

	float torque = contact.x * force.y - contact.y * force.x;
	angularVelocity += torque * GetInverseMoment();
}

void PhysicsObject::Update(float deltaTime)
{
	velocity -= velocity * linearDrag * deltaTime;
	velocity = (length(velocity) < LINEAR_THRESHOLD) ? vec2(0) : velocity;
	position += velocity * deltaTime * deltaTime;

	angularVelocity -= angularVelocity * angularDrag * deltaTime;
	angularVelocity = (abs(angularVelocity) < ANGULAR_THRESHOLD) ? 0 : angularVelocity;
	rotation += angularVelocity *deltaTime *deltaTime;
}
