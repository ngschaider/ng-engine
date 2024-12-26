#pragma once

#include "component.h"
#include "rigid_body.h"
#include "input_system.h"

class ControlVelocity : public Component {
public:
	ControlVelocity();
	void fixedUpdate() override;
};