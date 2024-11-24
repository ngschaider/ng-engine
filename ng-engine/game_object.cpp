#include "game_object.h"
#include "transform.h"
#include "component.h"
#include <cassert>
#include <vector>

GameObject::GameObject() {
	this->scene = nullptr;

	this->_transform = new Transform();
	this->addComponent(this->_transform);
}

GameObject::~GameObject() {
	for (Component* component : this->components) {
		delete component;
	}
}

/**
* Adds the specified Component to the GameEngine.
* The GameObject takes ownership of the Component.
*/
void GameObject::addComponent(Component* component) {
	assert(component->gameObject == nullptr);
	this->components.push_back(component);
	component->gameObject = this;
}

/**
* Removes the specified Component from the GameObject.
* The ownership of the Component is returned to the caller.
*/
void GameObject::removeComponent(Component* component) {
	assert(component->gameObject == this);
	std::vector<Component*>::iterator index = std::find(this->components.begin(), this->components.end(), component);
	assert(index != this->components.end());
	this->components.erase(index);
	component->gameObject = nullptr;
}

void GameObject::update() {
	for (Component* component : this->components) {
		component->update();
	}
}