#pragma once
#include "scene.h"

/**
* The main class for the engine.
* This class can hold a reference to a scene and runs the game loop when started.
* The game loop calls a fixed update method at a fixed interval and an update method as often as possible.
*/
class Engine {
private:
	/**
	* A reference to the currently active scene.
	* This can be NULL.
	*/
	Scene* scene;

	/**
	* Returns a UNIX epoch timestamp in seconds.
	*/
	double getTimestamp();

	/**
	* The fixed update signal. Useful for physical simulations. This method is not called every game loop iteration but 
	* instead only when needed not reach an invocation interval of approximately Engine::FIXED_UPDATE_INTERVAL.
	* If this method is called it is called at the beginning of the main game loop, before earlyUpdate.
	*/
	void fixedUpdate();

	/**
	* The early update signal. This is called after fixedUpdate may have been called.
	* This signal is propagated to the scene (and therefore all game objects and components) if they are enabled.
	*/
	void earlyUpdate();

	/**
	* The update signal. This is called after earlyUpdate.
	* This signal is propagated to the scene (and therefore all game objects and components) if they are enabled.
	*/
	void update();

	/**
	* The late update signal. This is called after update.
	* This signal is propagated to the scene (and therefore all game objects and components) if they are enabled.
	*/
	void lateUpdate();

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
	double elapsed() const;

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

