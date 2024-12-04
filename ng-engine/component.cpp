#include "component.h"
#include "game_object.h"

Component::Component() {
	this->gameObject = nullptr;
}

void Component::update() {

}

Scene* Component::scene() const {
	if (this->gameObject == nullptr) {
		return nullptr;
	}

	return this->gameObject->scene;
}

Transform* Component::transform() const {
	if (this->gameObject == nullptr) {
		return nullptr;
	}

	return this->gameObject->transform();
}