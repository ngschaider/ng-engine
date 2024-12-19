#include "inspector_window.h"
#include "imgui.h"
#include "hierarchy_window.h"
#include <typeinfo>
#include "misc/cpp/imgui_stdlib.h"

InspectorWindow::InspectorWindow() {
	this->inspectedGameObject = nullptr;
}

void InspectorWindow::setInspectedGameObject(GameObject* gameObject) {
	this->inspectedGameObject = gameObject;
}

void InspectorWindow::render() {
	ImGui::Begin("Inspector");

	if (this->inspectedGameObject == nullptr) {
		ImGui::Text("No game object selected.");
		ImGui::Text("Select a game object in the Hierarchy to show details here.");
	}
	else {
		ImGui::InputText("##name", &this->inspectedGameObject->name);

		for (Component* component : this->inspectedGameObject->components) {
			ImGui::PushID(component);

			std::string name = std::string(typeid(*component).name());
			ImGui::CollapsingHeader(name.substr(6).c_str());
			ImGui::PopID();
		}
	}

	ImGui::End();
}