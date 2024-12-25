#include <exception>
#include <iostream>

#include "engine.h"
#include "debug.h"
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
#include "circle_collider_2d.h"
#include "rectangle_collider_2d.h"
#include "collision_visualizer.h"

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
		systems->addComponent(new CollisionVisualizer());
		systems->addComponent(new MenuBar());
		systems->addComponent(new Debug());
		scene->addGameObject(systems);

		GameObject* square1 = new GameObject("Square 1");
		square1->transform()->position = Vector3(-0.25f, 0, 0);
		RigidBody* rb1 = new RigidBody();
		rb1->linearVelocity = Vector3(0, 0, 0);
		square1->addComponent(rb1);
		square1->addComponent(new CircleCollider2D());
		square1->addComponent(new RectangleRenderer());
		scene->addGameObject(square1);

		GameObject* square2 = new GameObject("Square 2");
		square2->transform()->position = Vector3(0.25f, 0, 0);
		RigidBody* rb2 = new RigidBody();
		rb2->linearVelocity = Vector3(0, 0, 0);
		square2->addComponent(rb2);
		square2->addComponent(new CircleCollider2D());
		square2->addComponent(new RectangleRenderer());
		scene->addGameObject(square2);

		//GameObject* testLine = new GameObject("Test Line");
		//testLine->addComponent(new LineRenderer());
		//scene->addGameObject(testLine);

		//GameObject* circle = new GameObject("Circle");
		//circle->transform()->position = Vector3(-1, 0, 0);
		//RigidBody* rb2 = new RigidBody();
		//rb2->linearVelocity = Vector3(0, -0.001f, 0);
		//circle->addComponent(rb2);
		//circle->addComponent(new CircleCollider2D());
		//scene->addGameObject(circle);
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