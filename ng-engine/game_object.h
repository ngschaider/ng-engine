#pragma once

#include <vector>
#include "component.h"
#include "transform.h"
#include <string>

// forward declare Engine to avoid circular references (Engine is importing GameObject)
class Engine;

// forward declare Scene to avoid circular references (Scene is importing GameObject)
class Scene;

/**
* Game objects can be added to scenes and can hold multiple components.
* Each game object MUST contain a transform component.
*/
class GameObject {
private:
	/**
	* A reference to the mandatory transform component.
	*/
	Transform* _transform;
	std::vector<Component*> toRemoveLater;
public:
	/**
	* getEnabled() returns true when the "isEnabled" property of this instance and all of it's parents' "isEnabled" properties are true.
	*/
	bool isEnabledSelf = true;

	/**
	* Setter for isEnabled
	*/
	void setEnabled(bool enabled);

	/**
	* Returns wether this game object should be updated.
	*/
	bool getEnabled();

	/**
	* The components attached to this game object, this should only be written to by the game object.
	*/
	std::vector<Component*> components;

	/**
	* Returns a reference to the transform component of the game object.
	*/
	Transform* transform() const;

	/**
	* The name of the game object. Mainly used for identifying the game object during debuggging.
	*/
	std::string name = "Unnamed GameObject"; 

	/**
	* The scene this game object is attached to, this should only be written to by the scene
	*/
	Scene* scene;

	/**
	* Constructs a new game object
	*/
	GameObject();

	/**
	* Construct a new game object with the given name
	*/
	GameObject(std::string name);

	/**
	* Construct a new game object with the given name
	*/
	GameObject(const char* name);

	/**
	* Destructs the game object and it's components
	*/
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

	/**
	* Quick access to the scene's engine
	*/
	Engine* engine() const;

	/**
	* Called when the game objects gets attached to a scene, this should only be called by the scene
	*/
	void addedToScene();

	/**
	* Called when the game objects gets removed from a scene, this should only be called by the scene
	*/
	void removedFromScene();

	/**
	* Called when this->engine() changes from NULL to an engine instance, this should only be called by the scene
	*/
	void addedToEngine();

	/**
	* Called when this->engine() changes from an engine instance to NULL, this should only be called by the scene
	*/
	void removedFromEngine();

	/**
	* Called when this->engine() gets started, this should only be called by the scene
	*/
	void started();

	/**
	* Called when this->engine() gets stopped, this should only be called by the scene
	*/
	void stopped();

	/**
	* Returns a list containing references to all components of the specified type that are attached to this game object.
	* Because of some weird c++ shit we have to implement the function in the header.
	*/
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

	/**
	* Returns a reference to the first component of the specified type attached to this game object.
	* Because of some weird c++ shit we have to implement the function in the header.
	*/
	template<class T>
	T* getComponent() {
		std::vector<T*> components = this->getComponents<T>();
		if (components.empty()) return nullptr;
		return components.front();
	}

	/**
	* The earlyUpdate signal of the engine.
	*/
	void earlyUpdate();

	/**
	* The update signal of the engine.
	*/
	void update();

	/**
	* The late update signal of the engine.
	*/
	void lateUpdate();

	/**
	* The fixed update signal of the engine.
	*/
	void fixedUpdate();
};