#pragma once

#include "component.h"
#include "text_renderer.h"
#include "rigid_body.h"

enum class GameState {
	Start,
	Running,
	GameOver
};

class GameManager : public Component {
private:
	unsigned int score = 0;
	void setScore(unsigned int newScore);

public:
	/**
	* Reference to the game object representing the text displayed during game over state.
	* This game object MUST hold at least one TextRenderer component
	*/
	GameObject* gameOver = nullptr;

	/**
	* Reference to the game object representing the text displayed during start state.
	* This game object MUST hold at least one TextRenderer component
	*/
	GameObject* start = nullptr;

	/**
	* Reference to the game object representing the score text.
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

	GameState gameState = GameState::Start;
	GameManager();
	void update() override;
	void started() override;
};