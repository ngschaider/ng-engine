#pragma once

#include "renderer.h"

class HierarchyWindow : public Renderer {
private:
	void renderGameObject(GameObject*);
public:
	HierarchyWindow();
	void render() override;
};