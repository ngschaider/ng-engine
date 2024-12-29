#pragma once

#include "game_object.h"
#include "renderer.h"

/**
* The inspector window allows for inspection of game objects and certain components.
* It further allows changing their properties during runtime. 
*/
class InspectorWindow : public Renderer {
private:
public:
	/**
	* The game object currently being inspected.
	*/
	GameObject* inspectedGameObject = nullptr;

	/**
	* The render signal of the render system. Renders the window.
	*/
	void render() override;
};