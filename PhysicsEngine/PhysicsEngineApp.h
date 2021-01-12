#pragma once
#include "Application.h"
#include "Renderer2D.h"
#include "PhysicsWorld.h"

using namespace aie;

class PhysicsEngineApp : public aie::Application
{
public:
	PhysicsEngineApp() {}
	virtual ~PhysicsEngineApp() {}

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:
	PhysicsWorld* world = nullptr;
	Renderer2D* renderer = nullptr;
	Font* font = nullptr;
};
