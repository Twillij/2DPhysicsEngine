#include "PhysicsWorld.h"
#include "PhysicsObject.h"
#include "Collision.h"
#include <Gizmos.h>
#include <glm/ext.hpp>

PhysicsWorld::~PhysicsWorld()
{
	for (int i = 0; i < objects.size(); ++i)
		delete objects[i];
}

bool PhysicsWorld::SpawnObject(PhysicsObject* object)
{
	if (object)
	{
		object->SetWorld(this);
		objects.push_back(object);
		return true;
	}

	return false;
}

bool PhysicsWorld::DestroyObject(PhysicsObject* object)
{
	for (int i = 0; i < objects.size(); ++i)
	{
		if (objects[i] == object)
		{
			delete objects[i];
			objects.erase(objects.begin() + i);
			return true;
		}
	}

	return false;
}

void PhysicsWorld::CheckCollisions()
{
	vector<Collision> collisions;

	for (int i = 0; i < objects.size() - 1; ++i)
	{
		for (int j = i + 1; j < objects.size(); ++j)
		{
			Collision collision = objects[i]->CheckCollision(objects[j]);

			if (collision.hasCollided)
				collisions.push_back(collision);
		}
	}
}

void PhysicsWorld::ResolveCollision(Collision collision)
{
	PhysicsObject* a = collision.objectA;
	PhysicsObject* b = collision.objectB;
	float inverseMassA = a->GetInverseMass();
	float inverseMassB = b->GetInverseMass();

	// calculate relative velocity
	vec2 rv = b->velocity - a->velocity;

	// calculate relative velocity in terms of the normal direction
	float velAlongNormal = dot(rv, collision.normal);

	// do not resolve if velocities are separating
	if (velAlongNormal > 0)
		return;

	// calculate restitution
	float e = std::min(a->restitution, b->restitution);

	// calculate impulse magnitude
	float m = -(1 + e) * velAlongNormal / (inverseMassA + inverseMassB);

	// apply impulse
	vec2 impulse = m * collision.normal;
	a->velocity -= inverseMassA * impulse;
	b->velocity += inverseMassB * impulse;

	// apply positional correction
	float percent = 0.2f;
	float buffer = 0.01f;
	vec2 correction = std::max(collision.penetration - buffer, 0.0f) / (inverseMassA + inverseMassB) * percent * collision.normal;
	a->position -= inverseMassA * correction;
	b->position += inverseMassA * correction;
}

void PhysicsWorld::Update(float deltaTime)
{
	for (int i = 0; i < objects.size(); ++i)
		objects[i]->Update(deltaTime);

	CheckCollisions();
}

void PhysicsWorld::Draw(Renderer2D* renderer)
{
	Gizmos::clear();

	for (int i = 0; i < objects.size(); ++i)
		objects[i]->Draw(renderer);

	static float aspectRatio = 16.0f / 9.0f;
	Gizmos::draw2D(glm::ortho<float>(-100, 100, -100 / aspectRatio, 100 / aspectRatio, -1.0f, 1.0f));
}
