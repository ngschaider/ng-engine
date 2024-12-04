#pragma once

#include "component.h"
#include "graphics.h"

class RenderSystem : public Component {
public:
	Graphics* graphics;
	RenderSystem();
	virtual ~RenderSystem(); // always define destructors as virtual
	void update();
};