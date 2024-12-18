#include "imgui_renderer.h"
#include "render_system.h"
#include "scene.h"
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

ImGuiRenderer::ImGuiRenderer() {
	// this->renderingOrder = 10;
}

ImGuiRenderer::~ImGuiRenderer() {
}

void ImGuiRenderer::started() {
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

	RenderSystem* renderSystem = this->scene()->getComponent<RenderSystem>();
	if (renderSystem == nullptr) throw new std::exception("ImGuiRenderer requires a RenderSystem to be present in the scene.");
	ImGui_ImplGlfw_InitForOpenGL(renderSystem->window, true);
	ImGui_ImplOpenGL3_Init();
}

void ImGuiRenderer::stopped() {
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void ImGuiRenderer::beforeRender() {
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void ImGuiRenderer::render() {
}

void ImGuiRenderer::afterRender() {
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}