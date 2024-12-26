#pragma once

#include "renderer.h"
#include <vector>
#include <sstream>
#include <streambuf>

class ConsoleWindow : public Renderer {
private:
	std::streambuf* oldCout;
	std::ostringstream strCout;
	std::vector<std::string> messages;
public:
	ConsoleWindow();
	virtual ~ConsoleWindow();
	void update() override;
	void render() override;
};