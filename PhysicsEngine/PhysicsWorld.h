#pragma once
#include <Renderer2D.h>
#include <vector>

using namespace std;
using namespace aie;

class PhysicsObject;

class PhysicsWorld
{
public:
	PhysicsWorld() {}
	virtual ~PhysicsWorld();

	bool SpawnObject(PhysicsObject* object);
	bool DestroyObject(PhysicsObject* object);

	virtual void Update(float deltaTime);
	virtual void Draw(Renderer2D* renderer);

private:
	vec2 gravity = vec2(0, -9.81f);
	vector<PhysicsObject*> objects;
};
