#pragma once

#include <vector>
#include "game_object.h"
#include "camera.h"

// forward declare Engine to avoid circular references (Engine is importing Scene)
class Engine;

class Scene {
public:
	Engine* engine; // the engine this scene is attached to, this should only be written to by the engine
	Scene();
	virtual ~Scene(); // always define destructors as virtual

	std::vector<GameObject*> gameObjects;
	void addGameObject(GameObject*);
	void removeGameObject(GameObject*);
		
	Camera* getActiveCamera();

	// events
	void addedToEngine(); // Called when the scene gets attached to an engine, this should only be called by the engine
	void removedFromEngine(); // Called when the scene gets removed from an engine, this should only be called by the engine
	void started(); // Called when this->engine() gets started, this should only be called by the engine
	void stopped(); // Called when this->engine() gets stopped, this should only be called by the engine


	// because of some weird c++ shit we have to implement the function in the header
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
};