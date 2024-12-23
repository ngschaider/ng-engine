#pragma once

#include "component.h"
#include "collision_2d.h"
#include "line_renderer.h"
#include <map>

class CollisionVisualizer : public Component {
	std::map<Collision2D*, LineRenderer*> normals;
public:
	CollisionVisualizer();
	void update();
};