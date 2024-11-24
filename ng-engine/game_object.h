#pragma once

#include <vector>
#include "component.h"
#include "transform.h"

// forward declare Engine to avoid circular references (Engine is importing GameObject)
class Engine;

class GameObject {
private:
	std::vector<Component*> components;
	Transform* _transform;
public:
	Transform* transform() const { return this->_transform; }
	Scene* scene; // this should only be written to by the scene
	GameObject();
	~GameObject();
	void addComponent(Component*);
	void removeComponent(Component*);
	void update();
};