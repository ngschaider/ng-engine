#include "engine.h"
#include <exception>
#include "game_object.h"
#include <cassert>
#include <string>

Engine::Engine() {
}

Engine::~Engine() {
	for (GameObject* gameObject : this->gameObjects) {
		delete gameObject;
	}
}

/**
* Adds the specified GameObject to the Engine.
* The engine takes ownership of the GameObject.
*/
void Engine::addGameObject(GameObject* gameObject) {
	assert(gameObject->engine == nullptr);
	this->gameObjects.push_back(gameObject);
	gameObject->engine = this;
}

/**
* Removes the specified GameObject from the Engine.
* The ownership of the GameObject is returned to the caller.
*/
void Engine::removeGameObject(GameObject* gameObject) {
	assert(gameObject->engine == this);
	std::vector<GameObject*>::iterator index = std::find(this->gameObjects.begin(), this->gameObjects.end(), gameObject);
	assert(index != this->gameObjects.end());
	this->gameObjects.erase(index);
	gameObject->engine = nullptr;
}