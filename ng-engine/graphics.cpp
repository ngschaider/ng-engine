#include "graphics.h"
#include "matrix4x4.h"
#include <exception>

Graphics::Graphics() {
}

void Graphics::clear() {
	throw new std::exception();
}

void Graphics::setTransformationMatrix(Matrix4x4 m) {
	throw new std::exception();
}

void Graphics::startOfFrame() {
	throw new std::exception();
}

void Graphics::endOfFrame() {
	throw new std::exception();
}

void Graphics::triangle() {
	throw new std::exception();
}

void Graphics::rectangle() {
	throw new std::exception();
}