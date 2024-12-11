#pragma once

#include <vector>
#include "component.h"
#include "transform.h"
#include <vector>

// forward declare Engine to avoid circular references (Engine is importing GameObject)
class Engine;

// forward declare Scene to avoid circular references (Scene is importing GameObject)
class Scene;

class GameObject {
private:
	std::vector<Component*> components;
	Transform* _transform;
public:
	Transform* transform() const { return this->_transform; }
	Scene* scene; // this should only be written to by the scene
	GameObject();
	virtual ~GameObject(); // always define destructors as virtual
	void addComponent(Component*);
	void removeComponent(Component*);

	// because of some weird c++ shit we have to implement the function in the header
	// (we dont have to, but it is more portable this way)
	template<class T>
	std::vector<T*> getComponents() {
		std::vector<T*> ret;

		for (Component* component : this->components) {
			T* castedPointer = dynamic_cast<T*>(component);
			if (castedPointer == nullptr) continue;
			ret.push_back(castedPointer);
		}

		return ret;
	}

	// because of some weird c++ shit we have to implement the function in the header
	// (we dont have to, but it is more portable this way)
	template<class T>
	T* getComponent() {
		std::vector<T*> components = this->getComponents<T>();
		if (components.empty()) return nullptr;
		return components.front();
	}

	void update();
};