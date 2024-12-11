#pragma once

#include <vector>
#include "game_object.h"
#include "camera.h"

// forward declare Engine to avoid circular references (Engine is importing Scene)
class Engine;

class Scene {
private:
	std::vector<GameObject*> gameObjects;
public:
	Engine* engine; // this should only be written to by the engine
	Scene();
	virtual ~Scene(); // always define destructors as virtual

	void addGameObject(GameObject*);
	void removeGameObject(GameObject*);
		
	Camera* getActiveCamera();


	// because of some weird c++ shit we have to implement the function in the header (we dont have to, but it is more portable this way)
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


	// because of some weird c++ shit we have to implement the function in the header (we dont have to, but it is more portable this way)
	template<class T>
	T* getComponent() {
		std::vector<T*> components = this->getComponents<T>();
		if (components.empty()) return nullptr;
		return components.front();
	}

	void update();
};