#pragma once
#include <Renderer2D.h>
#include <glm/vec2.hpp>
#include <vector>

using namespace aie;
using namespace glm;
using namespace std;

class PhysicsObject;

class PhysicsWorld
{
public:
	PhysicsWorld() {}
	virtual ~PhysicsWorld();

	vec2 gravity = vec2(0.0f, -9.81f);

	bool SpawnObject(PhysicsObject* object);
	bool DestroyObject(PhysicsObject* object);

	void CheckCollisions();

	virtual void Update(float deltaTime);
	virtual void Draw(Renderer2D* renderer);

private:
	vector<PhysicsObject*> objects;
};
