#include "vector2i.h"

Vector2i::Vector2i(int x, int y) {
	this->_x = x;
	this->_y = y;
}

Vector2i Vector2i::operator-() {
	return Vector2i(-this->x(), -this->y());
}

int Vector2i::x() const { 
	return this->_x; 
}

int Vector2i::y() const { 
	return this->_y; 
}