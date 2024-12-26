#include "engine.h"
#include <exception>
#include "game_object.h"
#include <cassert>
#include <string>
#include <iostream>
#include "debug.h"
#include <chrono>

Engine::Engine() {
	this->scene = nullptr;
}

Engine::~Engine() {
	if (this->scene != nullptr) {
		delete this->scene;
	}
}

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


void Engine::earlyUpdate() {
	if (this->scene == nullptr) return;
	this->scene->earlyUpdate();
}

void Engine::update() {
	if (this->scene == nullptr) return;
	this->scene->update();
}

void Engine::lateUpdate() {
	if (this->scene == nullptr) return;
	this->scene->lateUpdate();
}

void Engine::fixedUpdate() {
	if (this->scene == nullptr) return;
	this->scene->fixedUpdate();
}

void Engine::stop() {
	this->shouldStop = true;
}


double Engine::getTimestamp() {
	const auto p1 = std::chrono::system_clock::now();
	return (double)p1.time_since_epoch().count() / 1e9;
}

void Engine::start() {
	if (this->scene != nullptr) {
		this->scene->started();
	}

	this->shouldStop = false;

	double previous = this->getTimestamp();
	double simulationTime = this->getTimestamp();
	while (!this->shouldStop) {
		try {
			double current = this->getTimestamp();
			this->_elapsed = current - previous;

			while (current - simulationTime > Engine::FIXED_UPDATE_INTERVAL) {
				this->fixedUpdate();
				simulationTime += Engine::FIXED_UPDATE_INTERVAL;
			}

			this->earlyUpdate();
			this->update();
			this->lateUpdate();

			this->_elapsed = 0;
			previous = current;
		}

		catch (std::exception e) {
			std::cout << "Exception!" << std::endl;
			std::cout << e.what() << std::endl;
		}
	}

	// Inform scene, that the engine has been stopped!
	if (this->scene != nullptr) {
		this->scene->stopped();
	}
}