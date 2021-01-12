#include "PhysicsWorld.h"
#include "PhysicsObject.h"

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

void PhysicsWorld::Update(float deltaTime)
{
	for (int i = 0; i < objects.size(); ++i)
		objects[i]->Update(deltaTime);
}

void PhysicsWorld::Draw(Renderer2D* renderer)
{
	for (int i = 0; i < objects.size(); ++i)
		objects[i]->Draw(renderer);
}
