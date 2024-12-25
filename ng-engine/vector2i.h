#pragma once

#include "vector2.h"

class Vector2i {
private:
	int _x;
	int _y;
public:
	Vector2i(int x, int y);

	int x() const;
	int y() const;

	/**
	* Negates the vector
	*/
	Vector2i operator-();

	Vector2 toVector2();
};