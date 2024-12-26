#include "console_window.h"
#include "imgui.h"
#include "imgui_internal.h"
#include "scene.h"
#include "inspector_window.h"
#include <vector>
#include <iostream>

ConsoleWindow::ConsoleWindow() {
	this->oldCout = std::cout.rdbuf();
	std::cout.rdbuf(this->strCout.rdbuf());
}

ConsoleWindow::~ConsoleWindow() {
	std::cout.rdbuf(this->oldCout);
}

void ConsoleWindow::update() {
	std::string message = this->strCout.str();
	if (message == "") return;

	this->oldCout->sputn(message.c_str(), message.size()); // send message to usual console output
	this->messages.push_back(message); // also store message in internal array for later rendering

	this->strCout.str(""); // set to empty string
	this->strCout.clear(); // clear error flags
}

void ConsoleWindow::render() {
	ImGui::Begin("Console");

	//ImGui::Text(this->strCout.str().c_str());

	if (ImGui::BeginListBox("##console_messages", ImVec2(-1, -1))) {
		for (std::string str : this->messages) {
			ImGui::Text(str.c_str());
		}
		ImGui::SetScrollHereY();
		ImGui::EndListBox();
	}

	ImGui::End();
}