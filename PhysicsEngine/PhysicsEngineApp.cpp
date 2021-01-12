#include "PhysicsEngineApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"

bool PhysicsEngineApp::startup()
{
	world = new PhysicsWorld();
	renderer = new Renderer2D();
	font = new Font("./font/consolas.ttf", 32);

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
