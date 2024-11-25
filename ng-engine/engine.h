#pragma once

#include "game_object.h"
#include "graphics.h"
#include "scene.h"

class Engine {
private:
	Scene* scene;
public:
	Engine();
	~Engine();
	void setScene(Scene*);
	void update();
};