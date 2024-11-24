#pragma once

#include <vector>
#include "game_object.h"


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