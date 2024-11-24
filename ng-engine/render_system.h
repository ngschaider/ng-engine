#pragma once

#include "component.h"
#include "graphics.h"

class RenderSystem : public Component {
public:
	Graphics* graphics;
	RenderSystem();
	void update();
};