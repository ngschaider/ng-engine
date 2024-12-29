#pragma once

#include "renderer.h"

/**
* The hierarchy window displays the game object hierarchy inside the currently active scene.
*/
class HierarchyWindow : public Renderer {
private:
	/**
	* Renders the entry for a single game object.
	*/
	void renderGameObject(GameObject*);
public:
	/**
	* The render signal of the render system. Renders the hierarchy.
	*/
	void render() override;
};