#include <exception>
#include <iostream>

#include "engine.h"
#include "opengl.h"

int main() {
	Engine engine = Engine();

	GameObject* go = new GameObject();
	engine.addGameObject(go);

	Graphics graphics = OpenGL();

	return EXIT_SUCCESS;
}