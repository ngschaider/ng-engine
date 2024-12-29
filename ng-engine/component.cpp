#include "component.h"
#include "scene.h"
#include "engine.h"
#include "game_object.h"

void Component::setEnabled(bool enabled) {
	this->isEnabledSelf = enabled;
}

bool Component::getEnabled() {
	return this->isEnabledSelf && this->gameObject->getEnabled();
}

void Component::earlyUpdate() {

}

void Component::update() {

}

void Component::lateUpdate() {

}

void Component::fixedUpdate() {

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