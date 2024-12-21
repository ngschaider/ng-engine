#pragma once

#include "component.h"
#include "rect.h"
#include "event.h"

class Collider2D : public Component {
private:
public:
	Event onCollisionStart;
	Event onCollisionEnd;
	Event onColliding;
	virtual Rect getLocalBounds();
	Rect getGlobalBounds();
};
