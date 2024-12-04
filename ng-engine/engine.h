#pragma once

#include "game_object.h"
#include "graphics.h"
#include "scene.h"

class Engine {
private:
	Scene* scene;
public:
	Engine();
	virtual ~Engine(); // always define destructors as virtual
	void setScene(Scene*);
	void update();
};