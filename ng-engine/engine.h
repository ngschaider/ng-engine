#pragma once

#include "game_object.h"
#include "scene.h"
#include <assert.h>


/**
* The main class for the engine.
* This class can hold a reference to a scene and runs the game loop when started.
* The game loop calls a fixed update method at a fixed interval and an update method as often as possible.
*/
class Engine {
private:
	Scene* scene;

	/**
	* Returns a UNIX epoch timestamp in seconds.
	*/
	double getTimestamp();

	void earlyUpdate();
	void lateUpdate();
	void update();
	void fixedUpdate();

	/**
	* Wether or not the main game loop should be stopped.
	* When this is true, the current iteration of the game loop will finish and the loop will exit.
	*/
	bool shouldStop = false;

	/**
	* During an update cycle, this variable holds the time that has passed since the last update.
	*/
	double _elapsed = 0;
public:
	/**
	* During an update cycle, returns the time that has passed since the last update.
	* This method should only be called from within the update cycle.
	*/
	double elapsed();

	/**
	* Defines how often the fixed update method should be called.
	*/
	constexpr static double FIXED_UPDATE_INTERVAL = 0.02;

	/**
	* Starts the engine and the game loop. 
	* This method will not return until the engine is stopped.
	*/
	void start();

	/**
	* Call this to notify the engine that it should stop.
	* The engine will stop after the current iteration of the game loop has finished.
	*/
	void stop();

	/**
	* Constructs a new engine instance.
	* Multiple engine instances can be created and run in parallel (in different threads).
	*/
	Engine();

	/**
	* Destructs the engine instance and all objects it owns.
	*/
	virtual ~Engine();

	/**
	* Sets the specified scene as the engine's current scene.
	* The engine takes ownership of the new scene and returns ownership of the old scene.
	*/
	Scene* setScene(Scene*);
};

