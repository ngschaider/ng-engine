#pragma once

#include "game_object.h"
#include "renderer.h"

class InspectorWindow : public Renderer {
private:
	GameObject* inspectedGameObject;
public:
	InspectorWindow();
	void setInspectedGameObject(GameObject*);
	void render();
};