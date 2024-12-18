#pragma once

#include <vector>
#include "component.h"
#include "transform.h"
#include <string>

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
	std::string name = "Unnamed GameObject"; // Name of the game object
	Scene* scene; // the scene this game object is attached to, this should only be written to by the scene
	GameObject();
	GameObject(const char*);
	virtual ~GameObject(); // always define destructors as virtual
	void addComponent(Component*);
	void removeComponent(Component*);

	// quick access including null-checks
	Engine* engine() const;

	// events
	void addedToScene(); // called when the game objects gets attached to a scene, this should only be called by the scene
	void removedFromScene(); // called when the game objects gets removed from a scene, this should only be called by the scene
	void addedToEngine(); // called when this->engine() changes from NULL to an engine instance, this should only be called by the scene
	void removedFromEngine(); // called when this->engine() changes from an engine instance to NULL, this should only be called by the scene
	void started(); // Called when this->engine() gets started, this should only be called by the scene
	void stopped(); // Called when this->engine() gets stopped, this should only be called by the scene

	// because of some weird c++ shit we have to implement the function in the header
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
	template<class T>
	T* getComponent() {
		std::vector<T*> components = this->getComponents<T>();
		if (components.empty()) return nullptr;
		return components.front();
	}

	void update();
};