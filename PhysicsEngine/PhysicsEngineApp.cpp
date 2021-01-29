#include "PhysicsEngineApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "Gizmos.h"
#include "Box.h"
#include "Circle.h"
#include "Line.h"

bool PhysicsEngineApp::startup()
{
	// increase the 2d line count to maximise the number of objects we can draw
	Gizmos::create(255U, 255U, 65535U, 65535U);

	world = new PhysicsWorld();
	renderer = new Renderer2D();
	font = new Font("./font/consolas.ttf", 32);

	Box* platform = new Box(vec2(0, -40), vec2(50, 2));
	platform->SetMass(0);
	world->SpawnObject(platform);
	world->SpawnObject(new Circle());

	return true;
}

void PhysicsEngineApp::shutdown()
{
	delete font;
	delete renderer;
	delete world;
}

void PhysicsEngineApp::update(float deltaTime)
{
	// input example
	Input* input = Input::getInstance();

	world->Update(deltaTime);

	// exit the application
	if (input->isKeyDown(INPUT_KEY_ESCAPE))
		quit();
}

void PhysicsEngineApp::draw()
{
	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	renderer->begin();

	// draw your stuff here!
	world->Draw(renderer);

	// output some text, uses the last used colour
	renderer->drawText(font, "Press ESC to quit", 0, 0);

	// done drawing sprites
	renderer->end();
}
