#include "component.h"
#include "scene.h"
#include "engine.h"
#include "game_object.h"

Component::Component() {
	this->gameObject = nullptr;
}

Component::~Component() {

}

void Component::update() {

}

// Quick access methods
Scene* Component::scene() const {
	if (this->gameObject == nullptr) return nullptr;
	return this->gameObject->scene;
}

Engine* Component::engine() const {
	Scene* scene = this->scene();
	if (scene == nullptr) return nullptr;
	return scene->engine;
}

Transform* Component::transform() const {
	if (this->gameObject == nullptr) return nullptr;
	return this->gameObject->transform();
}


// events
void Component::addedToGameObject() {

}

void Component::removedFromGameObject() {

}

void Component::addedToScene() {

}

void Component::removedFromScene() {

}

void Component::addedToEngine() {

}

void Component::removedFromEngine() {

}

void Component::started() {

}

void Component::stopped() {

}