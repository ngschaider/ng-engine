#include <exception>
#include <iostream>

#include "engine.h"
#include "render_system.h"
#include "triangle_renderer.h"
#include "cube_renderer.h"
#include "rectangle_renderer.h"
#include "text_renderer.h"
#include "control_velocity.h"
#include "input_system.h"
#include "imgui_renderer.h"
#include "rigid_body.h"
#include "quaternion.h"
#include "hierarchy_window.h"
#include "inspector_window.h"
#include "menu_bar.h"
#include "collision_system.h"
#include "rectangle_collider_2d.h"

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
		systems->addComponent(new InspectorWindow());
		systems->addComponent(new CollisionSystem());
		systems->addComponent(new MenuBar());
		scene->addGameObject(systems);

		GameObject* go = new GameObject("Test");
		go->addComponent(new RectangleCollider2D());
		go->addComponent(new RectangleRenderer());
		scene->addGameObject(go);

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