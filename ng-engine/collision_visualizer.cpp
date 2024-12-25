#include "collision_visualizer.h"
#include <exception>
#include "collision_system.h"
#include "scene.h"
#include "line_renderer.h"
#include <vector>

CollisionVisualizer::CollisionVisualizer() {
	
}

void CollisionVisualizer::update() {
	CollisionSystem* collisionSystem = this->scene()->getComponent<CollisionSystem>();
	if (collisionSystem == nullptr) throw new std::exception();

	for (Collision2D* collision : collisionSystem->currentCollisions) {
		if (!this->normals.contains(collision)) {
			LineRenderer* renderer = new LineRenderer();
			this->gameObject->addComponent(renderer);
			this->normals[collision] = renderer;
		}

		LineRenderer* renderer = this->normals.find(collision)->second;
		renderer->start = collision->colliderA->transform()->position;
		renderer->end = renderer->start + collision->normal.normalized().toVector3(0) * 5;
	}

	std::vector<Collision2D*> keysToRemove;
	for (std::pair<Collision2D*, LineRenderer*> pair : this->normals) {
		std::vector<Collision2D*>::iterator it = std::find(collisionSystem->currentCollisions.begin(), collisionSystem->currentCollisions.end(), pair.first);
		if(it == collisionSystem->currentCollisions.end()) {
			this->gameObject->deleteComponentLater(pair.second);
			keysToRemove.push_back(pair.first);
		}
	}

	for (Collision2D* collision : keysToRemove) {
		this->normals.erase(collision);
	}
}