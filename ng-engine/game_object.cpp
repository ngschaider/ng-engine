#include "game_object.h"
#include "transform.h"
#include "component.h"
#include "scene.h"
#include <cassert>
#include <vector>

GameObject::GameObject() {
	this->scene = nullptr;

	this->_transform = new Transform();
	this->addComponent(this->_transform);
}

GameObject::GameObject(const char* name) : GameObject() {
	this->name = name;
}

GameObject::~GameObject() {
	for (Component* component : this->components) {
		delete component;
	}
}

Engine* GameObject::engine() const {
	if (this->scene == nullptr) return nullptr;
	return this->scene->engine;
}


void GameObject::addComponent(Component* component) {
	assert(component != nullptr);
	assert(component->gameObject == nullptr);
	this->components.push_back(component);
	component->gameObject = this;
	component->addedToGameObject();
}


void GameObject::removeComponent(Component* component) {
	assert(component != nullptr);
	assert(component->gameObject == this);
	std::vector<Component*>::iterator it = std::find(this->components.begin(), this->components.end(), component);
	assert(it != this->components.end());
	this->components.erase(it);
	component->gameObject = nullptr;
	component->removedFromGameObject();
}

void GameObject::deleteComponentLater(Component* component) {
	assert(component != nullptr);
	assert(component->gameObject == this);

	// assert that component exists in our list of attached components
	std::vector<Component*>::iterator it1 = std::find(this->components.begin(), this->components.end(), component);
	assert(it1 != this->components.end());

	// check if component does NOT exist in our list of components to remove later
	std::vector<Component*>::iterator it2 = std::find(this->components.begin(), this->components.end(), component);
	if (it2 == this->components.end()) return;

	this->toRemoveLater.push_back(component);
}

void GameObject::earlyUpdate() {
	for (Component* component : this->components) {
		component->earlyUpdate();
	}
}

void GameObject::update() {
	for (Component* component : this->components) {
		component->update();
	}
}

void GameObject::lateUpdate() {
	for (Component* component : this->components) {
		component->lateUpdate();
	}

	for (Component* component : this->toRemoveLater) {
		std::vector<Component*>::iterator it1 = std::find(this->components.begin(), this->components.end(), component);
		if (it1 == this->components.end()) return;

		std::vector<Component*>::iterator it2 = std::find(this->toRemoveLater.begin(), this->toRemoveLater.end(), component);
		assert(it2 != this->toRemoveLater.end());
		this->toRemoveLater.erase(it2);

		this->removeComponent(component);
		delete component;
	}
}

void GameObject::addedToEngine() {
	for (Component* component : this->components) {
		component->addedToEngine();
	}
}

void GameObject::removedFromEngine() {
	for (Component* component : this->components) {
		component->removedFromEngine();
	}
}

void GameObject::addedToScene() {
	for (Component* component : this->components) {
		component->addedToScene();
	}
}

void GameObject::removedFromScene() {
	for (Component* component : this->components) {
		component->removedFromScene();
	}
}

void GameObject::started() {
	for (Component* component : this->components) {
		component->started();
	}
}

void GameObject::stopped() {
	for (Component* component : this->components) {
		component->stopped();
	}
}