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

void PhysicsWorld::DestroyOffboundObjects(vec2 lowerBounds, vec2 upperBounds, float margin)
{
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

	for (int i = 0; i < objects.size() - 1; ++i)
	{
		for (int j = i + 1; j < objects.size(); ++j)
		{
			Collision collision = objects[i]->CheckCollision(objects[j]);

			if (collision.hasCollided)
				collisions.push_back(collision);
		}
	}

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
	float ima = a->GetInverseMass();
	float imb = b->GetInverseMass();
	float imSum = ima + imb;
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

	float fBuffer = 1.0f;
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
		a->ApplyForce(fImpulse, ra);
		b->ApplyForce(-fImpulse, rb);
	}

	// apply positional correction
	float percent = 0.2f;
	float buffer = 0.01f;
	vec2 correction = std::max(collision.penetration - buffer, 0.0f) / (imSum) * percent * collision.normal;
	a->position -= ima * correction;
	b->position += imb * correction;
}

void PhysicsWorld::Update(float deltaTime)
{
	DestroyOffboundObjects(vec2(-100, -56.25f), vec2(100, 56.25f), 10);

	CheckCollisions();

	for (int i = 0; i < objects.size(); ++i)
	{
		objects[i]->ApplyForce(gravity, vec2(0));
		objects[i]->Update(deltaTime);
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
