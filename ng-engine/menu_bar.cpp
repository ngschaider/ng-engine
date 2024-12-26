#include "menu_bar.h"
#include "imgui.h"
#include "inspector_window.h"
#include "hierarchy_window.h"
#include "imgui_renderer.h"
#include "scene.h"
#include "engine.h"

void MenuBar::render() {
	if (ImGui::BeginMainMenuBar()) {
		if (ImGui::MenuItem("Exit")) {
			this->engine()->stop();
		}

		char buffer[120];
		sprintf_s(buffer, "FPS: %f", 1.0f / this->engine()->elapsed());
		ImGui::Text(buffer);

		ImGui::EndMainMenuBar();
	}
}