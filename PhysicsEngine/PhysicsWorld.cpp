#include "PhysicsWorld.h"
#include "PhysicsObject.h"
#include "Collision.h"

PhysicsWorld::~PhysicsWorld()
{
	for (int i = 0; i < objects.size(); ++i)
		delete objects[i];
}

bool PhysicsWorld::SpawnObject(PhysicsObject* object)
{
	if (object)
	{
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

void PhysicsWorld::Update(float deltaTime)
{
	for (int i = 0; i < objects.size(); ++i)
		objects[i]->Update(deltaTime);

	CheckCollisions();
}

void PhysicsWorld::Draw(Renderer2D* renderer)
{
	for (int i = 0; i < objects.size(); ++i)
		objects[i]->Draw(renderer);
}
