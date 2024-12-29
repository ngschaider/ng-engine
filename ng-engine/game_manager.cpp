#include <cassert>
#include <string>
#include "collider_2d.h"
#include "game_manager.h"
#include "game_object.h"
#include "GLFW/glfw3.h"
#include "input_system.h"
#include "numbers.h"
#include "rigid_body.h"
#include "scene.h"
#include "text_renderer.h"
#include "vector2.h"
#include "vector3.h"

void GameManager::setScore(unsigned int newScore) {
	this->score = newScore;
	this->scoreText->getComponent<TextRenderer>()->text = "Score: " + std::to_string(newScore);
}

void GameManager::started() {
	this->gameOver->setEnabled(false);
	this->scoreText->setEnabled(false);
	this->start->setEnabled(true);

	leftBar->getComponent<Collider2D>()->onCollisionStart.on([this](Collider2D* other) {
		if (other == this->ball->getComponent<Collider2D>()) {
			this->setScore(this->score + 1);
		}
		});

	leftBounds->getComponent<Collider2D>()->onCollisionStart.on([this](Collider2D* other) {
		if (other == this->ball->getComponent<Collider2D>()) {
			// Running -> GameOver
			this->gameState = GameState::GameOver;
			this->gameOver->setEnabled(true);
			this->scoreText->setEnabled(true);
			this->start->setEnabled(false);
			this->ball->getComponent<RigidBody>()->linearVelocity = Vector3(0, 0, 0);
		}
		});
}

void GameManager::update() {
	assert(this->gameOver != nullptr);
	assert(this->ball != nullptr);
	assert(this->start != nullptr);
	assert(this->scoreText != nullptr);

	InputSystem* inputSystem = this->scene()->getComponent<InputSystem>();
	assert(inputSystem != nullptr);

	if (this->gameState == GameState::GameOver) {
		if (inputSystem->isButtonJustPressed(GLFW_KEY_SPACE)) {
			this->gameState = GameState::Start;
			// GameOver -> Start

			this->ball->transform()->position = Vector3(0, 0, 0);
			this->gameOver->setEnabled(false);
			this->start->setEnabled(true);
			this->scoreText->setEnabled(false);
			this->setScore(0);
		}
	} else if (this->gameState == GameState::Start) {
		if (inputSystem->isButtonJustPressed(GLFW_KEY_SPACE)) {
			this->gameState = GameState::Running;
			// Start -> Running

			Vector3 startVelocity = Vector2::fromPolar(0.3f, Random::rand(-30, 30)).toVector3(0);
			this->ball->getComponent<RigidBody>()->linearVelocity = startVelocity;
			this->start->setEnabled(false);
			this->gameOver->setEnabled(false);
			this->scoreText->setEnabled(true);
		}
	}
}