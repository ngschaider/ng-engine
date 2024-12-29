#pragma once

#include "component.h"
#include "text_renderer.h"
#include "rigid_body.h"

/**
* The states of the GameManager
*/
enum class GameState {
	Start, // After "GameOver" (or at startup)
	Running, // After "Start"
	GameOver // After "Running"
};

/**
* The game manager is the central component of the "Pong" game.
* It is built like a finite state machine.
*/
class GameManager : public Component {
private:
	/**
	* Keep track of the player's score.
	*/
	unsigned int score = 0;

	/**
	* Sets the score and the score text.
	*/
	void setScore(unsigned int newScore);

public:
	/**
	* Reference to the game object shown on the game over screen.
	*/
	GameObject* gameOver = nullptr;

	/**
	* Reference to the game object shown on the start screen.
	*/
	GameObject* start = nullptr;

	/**
	* Reference to the ball game object.
	* This MUST contain a RigidBody component
	*/
	GameObject* ball = nullptr;

	/**
	* Reference to the game object representing the score text.
	* This game object MUST hold a TextRenderer component
	*/
	GameObject* scoreText = nullptr;

	/**
	* Reference to the game object representing the left boundary.
	* This should only be modified before the engine starts!
	*/
	GameObject* leftBounds = nullptr;

	/**
	* Reference to the game object representing the left bar.
	* This should only be modified before the engine starts!
	*/
	GameObject* leftBar = nullptr;

	/**
	* The game manager's (and therefore the game's) state.
	*/
	GameState gameState = GameState::Start;

	void update() override;
	void started() override;
};