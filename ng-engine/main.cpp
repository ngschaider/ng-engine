#include <exception>
#include <iostream>

#include "engine.h"
#include "render_system.h"
#include "triangle_renderer.h"
#include "rectangle_renderer.h"
#include "text_renderer.h"
#include "control_velocity.h"
#include "input_system.h"
#include "rigid_body.h"

int main() {
	Engine* engine = new Engine();

	Scene* scene = new Scene();
	engine->setScene(scene);
	try {
		GameObject* systems = new GameObject();
		systems->transform()->position = Vector3(0, 0, -10);
		scene->addGameObject(systems);
		systems->addComponent(new RenderSystem());
		systems->addComponent(new Camera());
		systems->addComponent(new InputSystem());

		GameObject* rectangle = new GameObject();
		scene->addGameObject(rectangle);
		rectangle->addComponent(new RigidBody());
		rectangle->addComponent(new RectangleRenderer());
		rectangle->addComponent(new ControlVelocity());

		GameObject* text = new GameObject();
		text->transform()->scale = Vector3(0.02f, 0.02f, 1.0f);
		scene->addGameObject(text);
		text->addComponent(new TextRenderer("Hello World!"));
	}
	catch (std::exception e) {
		std::cout << "Exception in setup:" << std::endl;
		std::cout << e.what() << std::endl;
	}

	while (true) {
		try {
			engine->update();
		}
		catch (std::exception e) {
			std::cout << "Exception!" << std::endl;
		}
	}
	
	// To clean everything up:
	delete engine;

	return EXIT_SUCCESS;
}