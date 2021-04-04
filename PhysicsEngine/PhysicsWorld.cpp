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

vector<PhysicsObject*> PhysicsWorld::GetWorldObjects()
{
	return objects;
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

void PhysicsWorld::DestroyOffboundObjects(vec2 lowerBounds, vec2 upperBounds, float margin)
{
	// destroy all objects that exit the given boundaries
	for (int i = 0; i < objects.size(); ++i)
	{
		if (objects[i]->position.x < lowerBounds.x - margin ||
			objects[i]->position.x > upperBounds.x + margin ||
			objects[i]->position.y < lowerBounds.y - margin ||
			objects[i]->position.y > upperBounds.y + margin)
		{
			DestroyObject(objects[i]);
		}
	}
}

void PhysicsWorld::CheckCollisions()
{
	vector<Collision> collisions;

	// check for possible collisions between all physics objects
	// add the collision info to an array to be resolved
	for (int i = 0; i < objects.size() - 1; ++i)
	{
		for (int j = i + 1; j < objects.size(); ++j)
		{
			Collision collision = objects[i]->CheckCollision(objects[j]);

			if (collision.hasCollided)
				collisions.push_back(collision);
		}
	}

	// resolve all the collisions that occured
	for (int i = 0; i < collisions.size(); ++i)
	{
		if (collisions[i].hasCollided)
			ResolveCollision(collisions[i]);
	}
}

void PhysicsWorld::ResolveCollision(Collision collision)
{
	PhysicsObject* a = collision.objectA;
	PhysicsObject* b = collision.objectB;
	vec2 ra = collision.contactA - a->position;
	vec2 rb = collision.contactB - b->position;

	// calculate relative velocity
	vec2 rv = b->velocity + vec2(-b->angularVelocity * rb.y, b->angularVelocity * rb.x)
			- a->velocity - vec2(-a->angularVelocity * ra.y, a->angularVelocity * ra.x);

	// calculate relative velocity in terms of the normal direction
	float contactVel = dot(rv, collision.normal);

	// do not resolve if velocities are separating
	if (contactVel > 0)
		return;

	// calculate restitution
	float e = std::min(a->restitution, b->restitution);

	// calculate the inverse sum of masses
	float raCrossN = ra.x * collision.normal.y - ra.y * collision.normal.x;
	float rbCrossN = rb.x * collision.normal.y - rb.y * collision.normal.x;
	float imSum = a->GetInverseMass() + powf(raCrossN, 2) * a->GetInverseMoment()
				+ b->GetInverseMass() + powf(rbCrossN, 2) * b->GetInverseMoment();

	// calculate impulse magnitude
	float m = -(1 + e) * contactVel / (imSum);

	// apply impulse
	vec2 impulse = m * collision.normal;
	a->ApplyForce(-impulse, ra);
	b->ApplyForce(impulse, rb);

	// recalculate relative velocity after impulse is applied
	rv = b->velocity + vec2(-b->angularVelocity * rb.y, b->angularVelocity * rb.x)
		- a->velocity - vec2(-a->angularVelocity * ra.y, a->angularVelocity * ra.x);

	// recalculate relative velocity in terms of the normal direction
	contactVel = dot(rv, collision.normal);

	// calculate the tangent vector aka friction vector
	vec2 fv = normalize(rv - collision.normal * contactVel);

	// calculate the magnitude to apply along the friction vector
	float fm = -dot(rv, fv) / (imSum);

	float fBuffer = 0.01f;
	if (abs(fm) > fBuffer)
	{
		vec2 fImpulse;

		// approximate the constant in coulomb's law using the static friction of each object
		float c = sqrtf(a->staticFriction * b->staticFriction);

		// clamp magnitude of friction and create impulse vector
		if (abs(fm) < m * c)
		{
			fImpulse = fv * fm;
		}
		else
		{
			c = sqrtf(a->kineticFriction * b->kineticFriction);
			fImpulse = fv * -m * c;
		}

		// Apply friction impulse
		a->ApplyForce(-fImpulse, ra);
		b->ApplyForce(fImpulse, rb);
	}

	// apply positional correction
	float percent = 0.2f;
	float buffer = 0.01f;
	vec2 correction = std::max(collision.penetration - buffer, 0.0f) / (imSum) * percent * collision.normal;
	a->position -= a->GetInverseMass() * correction;
	b->position += b->GetInverseMass() * correction;
}

void PhysicsWorld::Update(float deltaTime)
{
	accumulatedTime += deltaTime;

	// update physics at fixed time step
	while (accumulatedTime >= timeStep)
	{
		DestroyOffboundObjects(vec2(-100, -56.25f), vec2(100, 56.25f), 10);

		CheckCollisions();

		for (int i = 0; i < objects.size(); ++i)
		{
			objects[i]->ApplyForce(gravity, vec2(0, 1));
			objects[i]->Update(timeStep);
		}

		accumulatedTime -= timeStep;
	}
}

void PhysicsWorld::Draw(Renderer2D* renderer)
{
	Gizmos::clear();

	for (int i = 0; i < objects.size(); ++i)
		objects[i]->Draw(renderer);

	static float aspectRatio = 16.0f / 9.0f;
	Gizmos::draw2D(glm::ortho<float>(-100, 100, -100 / aspectRatio, 100 / aspectRatio, -1.0f, 1.0f));
}
