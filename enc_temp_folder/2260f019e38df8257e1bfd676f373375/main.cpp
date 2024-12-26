#include <exception>
#include <iostream>
#include <string>

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
#include "circle_collider.h"
#include "rectangle_collider.h"
#include "console_window.h"
#include "circle_renderer.h"

int main() {
	Engine* engine = new Engine();

	Scene* scene = new Scene();
	engine->setScene(scene);
	try {
		GameObject* systems = new GameObject("Systems");
		systems->transform()->position = Vector3(0, 0, 0);
		systems->addComponent(new RenderSystem());
		Camera* camera = new Camera();
		camera->size = Vector2(40, 20);
		systems->addComponent(camera);
		systems->addComponent(new InputSystem());
		systems->addComponent(new ImGuiRenderer());
		systems->addComponent(new HierarchyWindow());
		systems->addComponent(new InspectorWindow());
		systems->addComponent(new CollisionSystem());
		systems->addComponent(new MenuBar());
		systems->addComponent(new Debug());
		systems->addComponent(new ConsoleWindow());
		scene->addGameObject(systems);

		GameObject* square1 = new GameObject("Square 1");
		square1->transform()->position = Vector3(3, 0, 0);
		RigidBody* rb1 = new RigidBody();
		rb1->linearVelocity = Vector3(-0.05f, 0, 0);
		square1->addComponent(rb1);
		square1->addComponent(new RectangleCollider());
		square1->addComponent(new RectangleRenderer());
		// square1->addComponent(new ControlVelocity());
		scene->addGameObject(square1);

		GameObject* square2 = new GameObject("Square 2");
		square2->transform()->position = Vector3(-3, 0, 0);
		RigidBody* rb2 = new RigidBody();
		rb2->linearVelocity = Vector3(0.05f, 0, 0);
		square2->addComponent(rb2);
		square2->addComponent(new RectangleCollider());
		square2->addComponent(new RectangleRenderer());
		scene->addGameObject(square2);

		GameObject* line = new GameObject("Line");
		scene->addGameObject(line);

		// Set up vertical middle line
		constexpr int numParts = 28;
		float cameraHeight = scene->getActiveCamera()->size.y();
		for (int i = 0; i < numParts; i++) {
			GameObject* part = new GameObject("Part " + std::to_string(i));
			part->transform()->position = Vector3(0, camera->size.y() / numParts * i - camera->size.y() / 2, 0);
			part->transform()->scale = Vector3(0.3, camera->size.y() / numParts * 0.7, 1);
			part->transform()->parent = line->transform();
			part->addComponent(new RectangleRenderer());
			scene->addGameObject(part);
		}

		GameObject* leftBar = new GameObject("Left Bar");
		leftBar->transform()->position = Vector3(2 - camera->size.x() / 2, 0, 0);
		leftBar->transform()->scale = Vector3(2, camera->size.y(), 1);
		leftBar->addComponent(new RectangleRenderer());
		leftBar->addComponent(new ControlVelocity);
		leftBar->addComponent(new RectangleCollider());
		RigidBody* leftRigidBody = new RigidBody();
		leftRigidBody->mass = INFINITY;
		leftBar->addComponent(leftRigidBody);
		scene->addGameObject(leftBar);

		GameObject* rightBar = new GameObject("Right Bar");
		rightBar->transform()->position = Vector3(camera->size.x() / 2 - 2, 0, 0);
		rightBar->transform()->scale = Vector3(2, camera->size.y() - 1, 1);
		rightBar->addComponent(new RectangleRenderer());
		rightBar->addComponent(new ControlVelocity);
		rightBar->addComponent(new RectangleCollider());
		RigidBody* rightRigidBody = new RigidBody();
		rightRigidBody->mass = INFINITY;
		rightBar->addComponent(rightRigidBody);
		scene->addGameObject(rightBar);

		GameObject* ball = new GameObject("Ball");
		//ball->transform()->scale = Vector3(2, 2, 1);
		ball->addComponent(new CircleRenderer());
		ball->addComponent(new RigidBody());
		ball->addComponent(new CircleCollider());
		scene->addGameObject(ball);

	}
	catch (std::exception e) {
		std::cout << "Exception in setup: " << std::endl;
		std::cout << e.what() << std::endl;
	}

	// Start game loop, this can be stopped by calling engine->stop() somewhere in a component's update() method
	engine->start();

	// Clean everything up. 
	// The scene, game objects and components are also cleaned up by this 
	// as the methods to add them to the hierarchy take the ownership of the objects.
	delete engine; 

	return EXIT_SUCCESS;
}