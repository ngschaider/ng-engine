#include <exception>
#include <iostream>

#include "engine.h"
#include "render_system.h"

int main() {
	Engine* engine = new Engine();

	Scene* scene = new Scene();
	engine->setScene(scene);

	GameObject* go = new GameObject();
	scene->addGameObject(go);

	RenderSystem* renderSystem = new RenderSystem();
	go->addComponent(renderSystem);

	while (true) {
		engine->update();
	}
	
	// To clean everything up:
	delete engine;
	// We do not need to clean up the engine's scene, gameobjects and component.
	// The engine takes care of that for us.

	return EXIT_SUCCESS;
}