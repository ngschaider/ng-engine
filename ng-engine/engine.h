#pragma once

#include "game_object.h"
#include "graphics.h"

class Engine {
private:
	std::vector<GameObject*> gameObjects;
public:
	Engine();
	~Engine();

	void addGameObject(GameObject*);
	void removeGameObject(GameObject*);
};