#include "PhysicsEngineApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"

bool PhysicsEngineApp::startup() {
	
	renderer = new Renderer2D();
	font = new Font("./font/consolas.ttf", 32);

	return true;
}

void PhysicsEngineApp::shutdown()
{
	delete font;
	delete renderer;
}

void PhysicsEngineApp::update(float deltaTime)
{
	// input example
	Input* input = Input::getInstance();

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
	
	// output some text, uses the last used colour
	renderer->drawText(font, "Press ESC to quit", 0, 0);

	// done drawing sprites
	renderer->end();
}