#pragma once
#include "Application.h"
#include "Renderer2D.h"

using namespace aie;

class PhysEngineApp : public aie::Application
{
public:
	PhysEngineApp() {}
	virtual ~PhysEngineApp() {}

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:
	Renderer2D* renderer;
	Font* font;
};
