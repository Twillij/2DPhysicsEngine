#include "PhysicsEngineApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "Gizmos.h"
#include "Box.h"
#include "Circle.h"
#include "Line.h"
#include <iostream>

bool PhysicsEngineApp::startup()
{
	// increase the 2d line count to maximise the number of objects we can draw
	Gizmos::create(255U, 255U, 65535U, 65535U);

	world = new PhysicsWorld();
	renderer = new Renderer2D();
	font = new Font("./font/consolas.ttf", 32);

	Box* platform = new Box(vec2(0, -40), vec2(80, 2), 0);
	world->SpawnObject(platform);

	Box* wall = new Box(vec2(90, 0), vec2(2, 56), 0);
	world->SpawnObject(wall);

	Circle* staticCircleLeft = new Circle(vec2(-30, 0), 7.5f, 0);
	world->SpawnObject(staticCircleLeft);

	Circle* staticCircleRight = new Circle(vec2(30, 0), 7.5f, 0);
	world->SpawnObject(staticCircleRight);

	Circle* staticCircleTop = new Circle(vec2(0, 25), 7.5f, 0);
	world->SpawnObject(staticCircleTop);

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

	if (input->wasMouseButtonPressed(0))
	{
		float mouseX = (input->getMouseX() - 640) / (640 / 100);
		float mouseY = (input->getMouseY() - 360) / (360 / 100 * 16 / 9);
		world->SpawnObject(new Circle(vec2(mouseX, mouseY)));
	}

	if (input->wasMouseButtonPressed(1))
	{
		float mouseX = (input->getMouseX() - 640) / (640 / 100);
		float mouseY = (input->getMouseY() - 360) / (360 / 100 * 16 / 9);
		world->SpawnObject(new Box(vec2(mouseX, mouseY)));
	}

	if (input->wasKeyPressed(INPUT_KEY_BACKSPACE))
	{
		int worldStaticCount = 5;
		vector<PhysicsObject*> worldObjects = world->GetWorldObjects();

		for (int i = worldStaticCount; i < worldObjects.size(); ++i)
		{
			world->DestroyObject(worldObjects[i]);
		}
	}

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
	renderer->drawText(font, "Left click to spawn circles", 0, 700);
	renderer->drawText(font, "Right click to spawn boxes", 0, 675);
	renderer->drawText(font, "Press ESC to quit", 0, 0);
	renderer->drawText(font, "Press BKSP to clear", 0, 25);

	// done drawing sprites
	renderer->end();
}
