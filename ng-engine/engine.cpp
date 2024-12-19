#include "engine.h"
#include <exception>
#include "game_object.h"
#include <cassert>
#include <string>
#include <iostream>

Engine::Engine() {
	this->scene = nullptr;
}

Engine::~Engine() {
	if (this->scene != nullptr) {
		delete this->scene;
	}
}

/**
* Sets the specified scene as the engine's current scene.
* The engine takes ownership of the new scene and returns ownership of the old scene.
*/
Scene* Engine::setScene(Scene* scene) {
	if(scene != nullptr) assert(scene->engine == nullptr); // assert that the new scene is not attached to any engine yet

	Scene* oldScene = this->scene;
	if (oldScene != nullptr) {
		oldScene->engine = nullptr; // remove engine reference from old scene
		oldScene->removedFromEngine(); // inform old scene about removal from the scene
	}
	this->scene = scene; // save reference to new scene
	if (scene != nullptr) {
		scene->engine = this; // save engine reference to new scene
		scene->addedToEngine(); // notify new scene about the event
	}

	return oldScene; // return the reference to the old scene so it can be used again (we are transferring the object ownership to the caller)
}

void Engine::update() {
	if (this->scene == nullptr) return;
	this->scene->update();
}

void Engine::stop() {
	this->shouldStop = true;
}

void Engine::start() {
	if (this->scene != nullptr) {
		this->scene->started();
	}

	this->shouldStop = false;
	while (!this->shouldStop) {
		try {
			this->update();
		}
		catch (std::exception e) {
			std::cout << "Exception!" << std::endl;
		}
	}

	// Inform scene, that the engine has been stopped!
	if (this->scene != nullptr) {
		this->scene->stopped();
	}
}