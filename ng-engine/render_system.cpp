#include "render_system.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "game_object.h"
#include <vector>
#include <algorithm>
#include "scene.h"
#include "renderer.h"
#include "debug.h"

void errorCallback(int error, const char* msg) {
	std::string s;
	s = " [" + std::to_string(error) + "] " + msg + '\n';
	std::cerr << s << std::endl;
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void debugMessageCallback(GLenum source, GLenum type, unsigned int id, GLenum severity, GLsizei length, const char* message, const void* userParam) {
	// ignore non-significant error/warning codes
	if (id == 131169 || id == 131185 || id == 131218 || id == 131204) return;

	std::cout << "---------------" << std::endl;
	std::cout << "Debug message (" << id << "): " << message << std::endl;

	if (source == GL_DEBUG_SOURCE_API) {
		std::cout << "Source: API" << std::endl;
	}
	else if (source == GL_DEBUG_SOURCE_WINDOW_SYSTEM) {
		std::cout << "Source: Window System" << std::endl;
	}
	else if (source == GL_DEBUG_SOURCE_SHADER_COMPILER) {
		std::cout << "Source: Shader Compiler" << std::endl;
	}
	else if (source == GL_DEBUG_SOURCE_THIRD_PARTY) {
		std::cout << "Source: Third Party" << std::endl;
	}
	else if (source == GL_DEBUG_SOURCE_APPLICATION) {
		std::cout << "Source: Application" << std::endl;
	}
	else if (source == GL_DEBUG_SOURCE_OTHER) {
		std::cout << "Source: Other" << std::endl;
	}
	else {
		std::cout << "Source: Unknown" << std::endl;
	}

	if (type == GL_DEBUG_TYPE_ERROR) {
		std::cout << "Type: Error" << std::endl;
	}
	else if (type == GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR) {
		std::cout << "Type: Deprecated Behavior" << std::endl;
	}
	else if (type == GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR) {
		std::cout << "Type: Undefined Behavior" << std::endl;
	}
	else if (type == GL_DEBUG_TYPE_PORTABILITY) {
		std::cout << "Type: Portability" << std::endl;
	}
	else if (type == GL_DEBUG_TYPE_PERFORMANCE) {
		std::cout << "Type: Performance" << std::endl;
	}
	else if (type == GL_DEBUG_TYPE_MARKER) {
		std::cout << "Type: Marker" << std::endl;
	}
	else if (type == GL_DEBUG_TYPE_PUSH_GROUP) {
		std::cout << "Type: Push Group" << std::endl;
	}
	else if (type == GL_DEBUG_TYPE_POP_GROUP) {
		std::cout << "Type: Pop Group" << std::endl;
	}
	else if (type == GL_DEBUG_TYPE_OTHER) {
		std::cout << "Type: Other" << std::endl;
	}
	else {
		std::cout << "Type: Unknown" << std::endl;
	}

	if (severity == GL_DEBUG_SEVERITY_HIGH) {
		std::cout << "Severity: High" << std::endl;
	}
	else if (severity == GL_DEBUG_SEVERITY_MEDIUM) {
		std::cout << "Severity: Medium" << std::endl;
	}
	else if (severity == GL_DEBUG_SEVERITY_LOW) {
		std::cout << "Severity: Low" << std::endl;
	}
	else if (severity == GL_DEBUG_SEVERITY_NOTIFICATION) {
		std::cout << "Severity: Notification" << std::endl;
	}
	else {
		std::cout << "Severity: Unknown" << std::endl;
	}

	return;
}

RenderSystem::RenderSystem() {
	glfwSetErrorCallback(errorCallback);

	if (!glfwInit()) {
		throw std::exception("Could not initialize GLFW");
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true); // this makes everything significantly slower !!!

	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	this->window = glfwCreateWindow(1840, 900, "NG-ENGINE", nullptr, nullptr);
	if (this->window == nullptr) {
		throw std::exception("Failed to create GLFW window");
	}
	glfwMakeContextCurrent(this->window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		throw std::exception("Failed to initialize GLAD");
	}

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	int flags = 0;
	glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
	if (flags & GL_CONTEXT_FLAG_DEBUG_BIT) {
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(debugMessageCallback, nullptr);
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
	}

	Vector2i size = this->size();
	glViewport(0, 0, size.x(), size.y());
	glfwSetFramebufferSizeCallback(this->window, framebufferSizeCallback);

	glfwSetWindowPos(this->window, 40, 100);
}

RenderSystem::~RenderSystem() {
	glfwTerminate();
}

Vector2i RenderSystem::size() {
	int width, height;
	glfwGetWindowSize(this->window, &width, &height);
	return Vector2i(width, height);
}

float RenderSystem::ratio() {
	Vector2i size = this->size();
	return (float) size.x() / size.y();
}

void RenderSystem::lateUpdate() {
	glfwPollEvents();

	glClearColor(this->backgroundColor.r() / 255.0f, this->backgroundColor.g() / 255.0f, this->backgroundColor.b() / 255.0f, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	std::vector<Renderer*> renderers = this->gameObject->scene->getComponents<Renderer>();
	/*std::sort(renderers.begin(), renderers.end(), [](Renderer* const& r1, Renderer* const& r2) {
		return r1->renderingOrder < r2->renderingOrder;
	});*/
	for (Renderer* renderer : renderers) {
		renderer->beforeRender();
	}
	for (Renderer* renderer : renderers) {
		renderer->render();
	}
	for (Renderer* renderer : renderers) {
		renderer->afterRender();
	}

	glfwSwapBuffers(this->window);
}

Matrix4x4 RenderSystem::getScreenToClipMatrix() {
	return this->getClipToScreenMatrix().invert();
}

Matrix4x4 RenderSystem::getClipToScreenMatrix() {
	Vector2i size = this->size();

	Vector3 translate = Vector3((float) size.x() / 2, (float) size.y() / 2, 0);
	Vector3 scale = Vector3((float)size.x() / 2, (float)size.y() / 2, 1);
	return Matrix4x4::TRS(translate, Quaternion::identity(), scale);
}

Vector2 RenderSystem::screenToClip(Vector2 screen) {
	return (this->getScreenToClipMatrix() * screen.toVector4(1, 1)).xy();
}

Vector2 RenderSystem::clipToScreen(Vector2 clip) {
	return (this->getClipToScreenMatrix() * clip.toVector4(1, 1)).xy();
}