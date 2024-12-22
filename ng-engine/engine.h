#pragma once

#include "game_object.h"
#include "scene.h"

class Engine {
private:
	Scene* scene;
public:
	bool shouldStop = false;
	void start();
	void stop();
	Engine();
	virtual ~Engine(); // always define destructors as virtual
	Scene* setScene(Scene*);
	void earlyUpdate();
	void lateUpdate();
	void update();
};