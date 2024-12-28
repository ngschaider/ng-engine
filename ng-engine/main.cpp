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
#include "game_manager.h"

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

		GameObject* line = new GameObject("Line");
		scene->addGameObject(line);

		// Set up vertical middle line
		constexpr int numParts = 28;
		float cameraHeight = scene->getActiveCamera()->size.y();
		for (int i = 0; i < numParts; i++) {
			GameObject* part = new GameObject("Part " + std::to_string(i));
			part->transform()->position = Vector3(0, camera->size.y() / numParts * i - camera->size.y() / 2, 0);
			part->transform()->scale = Vector3(0.3f, camera->size.y() / numParts * 0.7f, 1);
			part->transform()->parent = line->transform();
			part->addComponent(new RectangleRenderer());
			scene->addGameObject(part);
		}

		GameObject* leftBar = new GameObject("Left Bar");
		leftBar->transform()->position = Vector3(2 - camera->size.x() / 2, 0, 0);
		leftBar->transform()->scale = Vector3(0.5f, 5, 1);
		leftBar->addComponent(new RectangleRenderer());
		leftBar->addComponent(new ControlVelocity());
		leftBar->addComponent(new RectangleCollider());
		RigidBody* leftRigidBody = new RigidBody();
		leftRigidBody->mass = INFINITY;
		leftBar->addComponent(leftRigidBody);
		scene->addGameObject(leftBar);

		GameObject* rightBar = new GameObject("Right Bar");
		rightBar->transform()->position = Vector3(camera->size.x() / 2 - 2, 0, 0);
		rightBar->transform()->scale = Vector3(0.5f, camera->size.y(), 1);
		rightBar->addComponent(new RectangleRenderer());
		rightBar->addComponent(new RectangleCollider());
		RigidBody* rightRigidBody = new RigidBody();
		rightRigidBody->mass = INFINITY;
		rightBar->addComponent(rightRigidBody);
		scene->addGameObject(rightBar);

		GameObject* ball = new GameObject("Ball");
		ball->transform()->scale = Vector3(2, 2, 1);
		ball->addComponent(new CircleRenderer());
		RigidBody* ballRigidBody = new RigidBody();
		ballRigidBody->restitution = 1.0f;
		ball->addComponent(ballRigidBody);
		ball->addComponent(new RectangleCollider());
		scene->addGameObject(ball);

		GameObject* topBounds = new GameObject("Top Bounds");
		topBounds->transform()->position = Vector3(0, camera->size.y() / 2 + 0.5f, 0);
		topBounds->transform()->scale = Vector3(camera->size.x(), 1, 0);
		topBounds->addComponent(new RectangleCollider());
		RigidBody* rb1 = new RigidBody();
		rb1->mass = INFINITY;
		topBounds->addComponent(rb1);
		scene->addGameObject(topBounds);

		GameObject* bottomBounds = new GameObject("Bottom Bounds");
		bottomBounds->transform()->position = Vector3(0, -camera->size.y() / 2 - 0.5f, 0);
		bottomBounds->transform()->scale = Vector3(camera->size.x(), 1, 0);
		bottomBounds->addComponent(new RectangleCollider());
		RigidBody* rb2 = new RigidBody();
		rb2->mass = INFINITY;
		bottomBounds->addComponent(rb2);
		scene->addGameObject(bottomBounds);

		GameObject* leftBounds = new GameObject("Left Bounds");
		leftBounds->transform()->position = Vector3(-camera->size.x() / 2 - 0.5f, 0, 0);
		leftBounds->transform()->scale = Vector3(1, camera->size.y(), 1);
		leftBounds->addComponent(new RectangleCollider());
		RigidBody* rb3 = new RigidBody();
		rb3->mass = INFINITY;
		leftBounds->addComponent(rb3);
		scene->addGameObject(leftBounds);

		GameObject* gameOver = new GameObject("Game Over");
		gameOver->transform()->position = Vector3(1, 0, 0.0f);
		gameOver->transform()->scale = Vector3(0.02f, 0.02f, 1);
		scene->addGameObject(gameOver);

		GameObject* gameOver1 = new GameObject("Line 1");
		gameOver1->addComponent(new TextRenderer("Game Over!"));
		gameOver1->transform()->parent = gameOver->transform();
		scene->addGameObject(gameOver1);

		GameObject* gameOver2 = new GameObject("Line 2");
		gameOver2->transform()->position = Vector3(0, -1, 0);
		gameOver2->addComponent(new TextRenderer("Press SPACE to continue"));
		gameOver2->transform()->parent = gameOver->transform();
		scene->addGameObject(gameOver2);

		GameObject* start = new GameObject("Start");
		start->transform()->position = Vector3(1.0f, 8.0f, 0.0f);
		start->transform()->scale = Vector3(0.02f, 0.02f, 1);
		start->addComponent(new TextRenderer("Press SPACE to start"));
		scene->addGameObject(start);

		GameObject* scoreText = new GameObject("Score Text");
		scoreText->transform()->position = Vector3(1.0f, 8.0f, 0.0f);
		scoreText->transform()->scale = Vector3(0.02f, 0.02f, 1);
		scoreText->addComponent(new TextRenderer("Score: 0"));
		scene->addGameObject(scoreText);

		GameManager* gameManager = new GameManager();
		gameManager->leftBounds = leftBounds;
		gameManager->leftBar = leftBar;
		gameManager->scoreText = scoreText;
		gameManager->ball = ball;
		gameManager->gameOver = gameOver;
		gameManager->start = start;
		systems->addComponent(gameManager);

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