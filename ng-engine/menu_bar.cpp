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

		ImGui::EndMainMenuBar();
	}
}