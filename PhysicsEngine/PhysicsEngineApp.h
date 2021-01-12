#pragma once
#include "Application.h"
#include "Renderer2D.h"

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
	Renderer2D* renderer;
	Font* font;
};
