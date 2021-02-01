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

void PhysicsObject::SetMass(float mass)
{
	this->mass = (mass >= 0) ? mass : 0;
	this->SetMoment();
}

float PhysicsObject::GetInverseMass()
{
	return (mass > 0) ? 1 / mass : 0; 
}

float PhysicsObject::GetInverseMoment()
{
	return (moment > 0) ? 1 / moment : 0;
}

void PhysicsObject::ApplyForce(vec2 force, vec2 contact)
{
	velocity += force * GetInverseMass();

	float torque = force.y * contact.x - force.x * contact.y; //std::cout << "torque: " << torque << std::endl;
	angularVelocity += torque * GetInverseMoment(); std::cout << "angular velocity: " << angularVelocity << std::endl;
}

void PhysicsObject::Update(float deltaTime)
{
	ApplyForce(world->gravity, vec2(0));

	position += velocity * deltaTime * deltaTime;
	rotation += angularVelocity * deltaTime * deltaTime; //std::cout << "rotation: " << rotation << std::endl;
}
