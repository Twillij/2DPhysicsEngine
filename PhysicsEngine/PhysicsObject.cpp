#include "PhysicsObject.h"
#include "PhysicsWorld.h"
#include "Collider.h"
#include "Collision.h"

PhysicsObject::~PhysicsObject()
{
	if (collider)
		delete collider;
}

PhysicsWorld* PhysicsObject::GetWorld()
{
	return world;
}

void PhysicsObject::SetWorld(PhysicsWorld* world)
{
	this->world = world;
}

void PhysicsObject::ApplyForce(vec2 force)
{
	velocity += force / mass;
}

Collision PhysicsObject::CheckCollision(PhysicsObject* other)
{
	if (collider && other)
	{
		return collider->CheckCollision(other->collider);
	}

	return Collision(this, other);
}

void PhysicsObject::Update(float deltaTime)
{
	velocity += world->gravity * deltaTime;

	position += velocity;
}
