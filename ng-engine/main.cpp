#include <exception>
#include <iostream>

#include "engine.h"
#include "render_system.h"
#include "triangle_renderer.h"
#include "cube_renderer.h"
#include "square_renderer.h"
#include "text_renderer.h"
#include "control_velocity.h"
#include "input_system.h"
#include "imgui_renderer.h"
#include "rigid_body.h"
#include "quaternion.h"
#include "hierarchy_window.h"

int main() {
	Engine* engine = new Engine();

	Scene* scene = new Scene();
	engine->setScene(scene);
	try {
		GameObject* systems = new GameObject("Systems");
		systems->transform()->position = Vector3(0, 0, 0);
		systems->addComponent(new RenderSystem());
		systems->addComponent(new Camera());
		systems->addComponent(new InputSystem());
		systems->addComponent(new ImGuiRenderer());
		systems->addComponent(new HierarchyWindow());
		scene->addGameObject(systems);

		GameObject* go1 = new GameObject("Triangle");
		go1->transform()->position = Vector3(-5, -2, 0);
		go1->addComponent(new TriangleRenderer());
		scene->addGameObject(go1);

		GameObject* go2 = new GameObject("Square");
		go2->transform()->position = Vector3(5, 5, 0);
		go2->addComponent(new SquareRenderer());
		scene->addGameObject(go2);
	}
	catch (std::exception e) {
		std::cout << "Exception in setup:" << std::endl;
		std::cout << e.what() << std::endl;
	}

	// Start infinite loop, this can be stopped by calling engine->stop() somewhere in a component's update() method
	engine->start();

	// Clean everything up. 
	// The scene, game objects and components are also cleaned up by this 
	// as the methods to add them to the hierarchy take the ownership of the objects.
	delete engine; 

	return EXIT_SUCCESS;
}