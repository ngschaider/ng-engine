#pragma once

#include "vector2.h"

/**
* A vector of length 2 consisting of integer values
*/
class Vector2i {
private:
	/**
	* The x-value of the vector
	*/
	int _x;

	/**
	* The y-value of the vector
	*/
	int _y;
public:
	/**
	* Constructs a new vector using the given x-value and y-value.
	*/
	Vector2i(int x, int y);

	/**
	* Returns the x-value of the vector.
	*/
	int x() const;

	/**
	* Returns the y-value of the vector.
	*/
	int y() const;

	/**
	* Negates the vector
	*/
	Vector2i operator-();

	/**
	* Converts the vector to a floating-point vector.
	*/
	Vector2 toVector2();
};