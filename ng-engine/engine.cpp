#include "engine.h"
#include <exception>
#include "game_object.h"
#include <cassert>
#include <string>

Engine::Engine() {
}

Engine::~Engine() {
	if (this->scene != nullptr) {
		delete this->scene;
	}
}

/**
* Sets the specified scene as the engine's current scene.
* The engine takes ownership of the scene.
* TODO: Make it possible to use the old scene after a new one has been set. 
*/
void Engine::setScene(Scene* scene) {
	if (this->scene != nullptr) {
		delete this->scene;
	}
	this->scene = scene;
}

void Engine::update() {
	if (this->scene == nullptr) return;
	this->scene->update();
}