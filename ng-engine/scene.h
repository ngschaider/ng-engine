#pragma once

#include <vector>
#include "game_object.h"
#include "camera.h"

// forward declare Engine to avoid circular references (Engine is importing Scene)
class Engine;

/**
* The scene is attached to the engine and contains multiple game objects.
*/
class Scene {
public:
	/**
	*  The engine this scene is attached to, this should only be written to by the engine
	*/
	Engine* engine = nullptr;

	/**
	* Destructs the scene and it's game objects.
	*/
	virtual ~Scene();

	/**
	* The game objects contained in the scene. This should only be modified by the scene.
	*/
	std::vector<GameObject*> gameObjects;

	/**
	* Adds the specified GameObject to the scene.
	* The scene takes ownership of the game object.
	*/
	void addGameObject(GameObject*);

	/**
	* Removes the specified game object from the scene.
	* The ownership of the game object is returned to the caller.
	*/
	void removeGameObject(GameObject*);
		
	/**
	* Returns the first active camera component in the scene
	*/
	Camera* getActiveCamera();

	/**
	* Called when the scene gets attached to an engine, this should only be called by the engine
	*/
	void addedToEngine();

	/**
	* Called when the scene gets removed from an engine, this should only be called by the engine
	*/
	void removedFromEngine();

	/**
	* Called when this->engine() gets started, this should only be called by the engine
	*/
	void started();

	/**
	* Called when this->engine() gets stopped, this should only be called by the engine
	*/
	void stopped();


	/**
	* Returns all components of a given type in the scene.
	* because of some weird c++ shit we have to implement the function in the header
	*/
	template<class T>
	std::vector<T*> getComponents() {
		std::vector<T*> ret;

		for (GameObject* gameObjects : this->gameObjects) {
			std::vector<T*> components = gameObjects->getComponents<T>();
			for (T* component : components) {
				ret.push_back(component);
			}
		}

		return ret;
	}


	/**
	* Returns the first component of a given type in the scene.
	* because of some weird c++ shit we have to implement the function in the header
	*/
	template<class T>
	T* getComponent() {
		std::vector<T*> components = this->getComponents<T>();
		if (components.empty()) return nullptr;
		return components.front();
	}

	/**
	* The early update signal of the engine.
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