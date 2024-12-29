#pragma once

#include "renderer.h"
#include <vector>
#include <sstream>
#include <streambuf>

/**
* A window replacing the standard command-line.
* This intercepts the stream to std::cout and displays it.
*/
class ConsoleWindow : public Renderer {
private:
	/**
	* The old std::cout read buffer leading to the command-line window.
	*/
	std::streambuf* oldCout;

	/**
	* The new read buffer being read out during update.
	*/
	std::ostringstream strCout;

	/**
	* The messages being rendered in the window.
	*/
	std::vector<std::string> messages;
public:
	/**
	* Constructs a new object and intercepts std::cout.
	*/
	ConsoleWindow();

	/**
	* Reverts std::cout interception and destructs object.
	*/
	virtual ~ConsoleWindow();

	/**
	* The update signal of the engine. Reads out the new read buffer and saves the messages.
	*/
	void update() override;

	/**
	* The render signal of the render system. Renders the saved messages.
	*/
	void render() override;
};