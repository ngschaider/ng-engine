#pragma once
#include "component.h"
#include "rect.h"

class Collider2D : public Component {
public:
	virtual Rect getLocalBounds();
	Rect getGlobalBounds();
};
