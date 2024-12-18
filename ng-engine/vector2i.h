#pragma once

class Vector2i {
private:
	int _x;
	int _y;
public:
	Vector2i() : Vector2i(0, 0) {

	}

	Vector2i(int x, int y) {
		this->_x = x;
		this->_y = y;
	}

	int x() const { return this->_x; }
	int y() const { return this->_y; }
};