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

void Engine::stop() {
	this->shouldStop = true;

	if (this->scene != nullptr) {
		this->scene->stopped();
	}
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
}