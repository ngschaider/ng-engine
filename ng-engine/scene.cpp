#include "scene.h"
#include "game_object.h"
#include <vector>
#include "component.h"
#include <cassert>
#include <exception>

Scene::Scene() {
	this->engine = nullptr;
}

Scene::~Scene() {
	for (GameObject* gameObject : this->gameObjects) {
		delete gameObject;
	}
}


/**
* Adds the specified GameObject to the scene.
* The scene takes ownership of the game object.
*/
void Scene::addGameObject(GameObject* gameObject) {
	assert(gameObject->scene == nullptr); // assert that the game object is not attached to any scene

	// assert that the game object is not in the scene's list of game objects
	std::vector<GameObject*>::iterator index = std::find(this->gameObjects.begin(), this->gameObjects.end(), gameObject);
	assert(index == this->gameObjects.end());

	this->gameObjects.push_back(gameObject); // store the game object in the scene's list of game objects
	gameObject->scene = this; // give the game object a reference to this scene
	gameObject->addedToScene(); // call the game object's event to notify it about this event
}

/**
* Removes the specified game object from the scene.
* The ownership of the game object is returned to the caller.
*/
void Scene::removeGameObject(GameObject* gameObject) {
	assert(gameObject->scene == this); // assert that the game object is attached to this scene

	// assert that the game object is in the scene's list of game objects
	std::vector<GameObject*>::iterator index = std::find(this->gameObjects.begin(), this->gameObjects.end(), gameObject);
	assert(index != this->gameObjects.end());

	this->gameObjects.erase(index); // remove the game object from this scene's list of game objects
	gameObject->scene = nullptr; // remove the scene reference inside the game object 
	gameObject->removedFromScene(); // call the game object's event to notify it about this event
}

/**
* returns the first active camera component in the scene
*/
Camera* Scene::getActiveCamera() {
	std::vector<Camera*> cameras = this->getComponents<Camera>();
	for (Camera* camera : cameras) {
		if (camera->isActive) {
			return camera;
		}
	}

	// we could not find an active camera in the scene
	// it is the responsibility of the caller to handle this case adequately.
	return nullptr; 
}

void Scene::earlyUpdate() {
	for (GameObject* gameObject : this->gameObjects) {
		gameObject->earlyUpdate();
	}
}

void Scene::update() {
	for (GameObject* gameObject : this->gameObjects) {
		gameObject->update();
	}
}

void Scene::lateUpdate() {
	for (GameObject* gameObject : this->gameObjects) {
		gameObject->lateUpdate();
	}
}

void Scene::fixedUpdate() {
	for (GameObject* gameObject : this->gameObjects) {
		gameObject->fixedUpdate();
	}
}

void Scene::addedToEngine() {
	for (GameObject* gameObject : this->gameObjects) {
		gameObject->addedToEngine();
	}
}
void Scene::removedFromEngine() {
	for (GameObject* gameObject : this->gameObjects) {
		gameObject->removedFromEngine();
	}
}
void Scene::started() {
	for (GameObject* gameObject : this->gameObjects) {
		gameObject->started();
	}
}
void Scene::stopped() {
	for (GameObject* gameObject : this->gameObjects) {
		gameObject->stopped();
	}
}