#include "PhysicsWorld.h"
#include "PhysicsObject.h"

PhysicsWorld::~PhysicsWorld()
{
	for (int i = 0; i < objects.size(); ++i)
		delete objects[i];
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
