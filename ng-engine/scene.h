#pragma once

#include <vector>
#include "game_object.h"

// forward declare Engine to avoid circular references (Engine is importing Scene)
class Engine;


class Scene {
private:
	std::vector<GameObject*> gameObjects;
public:
	Engine* engine; // this should only be written to by the engine
	Scene();
	~Scene();

	void addGameObject(GameObject*);
	void removeGameObject(GameObject*);
	void update();
};