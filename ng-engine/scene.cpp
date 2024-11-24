#include "scene.h"
#include "game_object.h"
#include <vector>
#include <cassert>

Scene::Scene() {

}

Scene::~Scene() {
	for (GameObject* gameObject : this->gameObjects) {
		delete gameObject;
	}
}

/**
* Adds the specified GameObject to the scene.
* The scene takes ownership of the GameObject.
*/
void Scene::addGameObject(GameObject* gameObject) {
	assert(gameObject->scene == nullptr);
	this->gameObjects.push_back(gameObject);
	gameObject->scene = this;
}

/**
* Removes the specified GameObject from the scene.
* The ownership of the GameObject is returned to the caller.
*/
void Scene::removeGameObject(GameObject* gameObject) {
	assert(gameObject->scene == this);
	std::vector<GameObject*>::iterator index = std::find(this->gameObjects.begin(), this->gameObjects.end(), gameObject);
	assert(index != this->gameObjects.end());
	this->gameObjects.erase(index);
	gameObject->scene = nullptr;
}

void Scene::update() {
	for (GameObject* gameObject : this->gameObjects) {
		gameObject->update();
	}
}