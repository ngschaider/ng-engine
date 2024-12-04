#include <exception>
#include <iostream>

#include "engine.h"
#include "render_system.h"
#include "triangle_renderer.h"
#include "rectangle_renderer.h"

int main() {
	Engine* engine = new Engine();

	Scene* scene = new Scene();
	engine->setScene(scene);

	GameObject* systems = new GameObject();
	systems->transform()->position = Vector3(0, 0, 10);
	scene->addGameObject(systems);
	RenderSystem* renderSystem = new RenderSystem();
	systems->addComponent(renderSystem);
	Camera* camera = new Camera();
	systems->addComponent(camera);

	GameObject* rectangle = new GameObject();
	scene->addGameObject(rectangle);
	RectangleRenderer* rectangleRenderer = new RectangleRenderer();
	rectangle->addComponent(rectangleRenderer);

	while (true) {
		engine->update();
	}
	
	// To clean everything up:
	delete engine;
	// We do not need to clean up the engine's scene, gameobjects and component.
	// The engine takes care of that for us.

	return EXIT_SUCCESS;
}