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
	Transform* _transform;
	std::vector<Component*> toRemoveLater;
public:
	std::vector<Component*> components; // The components attached to this game object, this should only be written to by the game object

	/**
	* The transform component attached to this game object.
	*/
	Transform* transform() const { return this->_transform; }

	/**
	* The name of the game object
	*/
	std::string name = "Unnamed GameObject"; 

	/**
	* The scene this game object is attached to, this should only be written to by the scene
	*/
	Scene* scene;

	GameObject();
	GameObject(const char*);
	virtual ~GameObject();


	/**
	* Adds the specified Component to the GameEngine.
	* The GameObject takes ownership of the Component.
	*/
	void addComponent(Component*);

	/**
	* Removes the specified Component from the GameObject.
	* The ownership of the Component is returned to the caller.
	*/
	void removeComponent(Component*);

	/**
	* Queues the component to get deleted in the next lateUpdate cycle.
	* Component will be removed from the game object and subsequently deleted.
	*/
	void deleteComponentLater(Component*);

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

	void earlyUpdate();
	void update();
	void lateUpdate();
	void fixedUpdate();
};