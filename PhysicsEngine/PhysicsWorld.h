#pragma once
#include <Renderer2D.h>
#include <glm/vec2.hpp>
#include <vector>

using namespace aie;
using namespace glm;
using namespace std;

class PhysicsObject;
class Collision;

class PhysicsWorld
{
public:
	PhysicsWorld() {}
	virtual ~PhysicsWorld();

	float timeStep = 0.02f;
	vec2 gravity = vec2(0.0f, -9.81f);

	vector<PhysicsObject*> GetWorldObjects();

	bool SpawnObject(PhysicsObject* object);
	bool DestroyObject(PhysicsObject* object);
	void DestroyOffboundObjects(vec2 lowerBounds, vec2 upperBounds, float margin = 0);

	void CheckCollisions();
	void ResolveCollision(Collision collision);

	virtual void Update(float deltaTime);
	virtual void Draw(Renderer2D* renderer);

private:
	float accumulatedTime = 0;
	vector<PhysicsObject*> objects;
};
