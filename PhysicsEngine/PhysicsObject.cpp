#include "PhysicsObject.h"
#include "PhysicsWorld.h"
#include "Collision.h"
#include <iostream>

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

float PhysicsObject::GetInverseMass()
{
	return (mass) ? 1 / mass : 0;
}

void PhysicsObject::SetMass(float mass)
{
	this->mass = (mass >= 0) ? mass : 0;
}

void PhysicsObject::ApplyForce(vec2 force, float deltaTime)
{
	velocity += force * GetInverseMass() * deltaTime; //cout << "velocity:" << velocity.x << "," << velocity.y << endl;
	angularVelocity += torque * (1 / moment) * deltaTime;
	position += velocity * deltaTime;
	rotation += angularVelocity * deltaTime;
}

void PhysicsObject::Update(float deltaTime)
{
	vec2 force = world->gravity;

	ApplyForce(force, deltaTime);
}
