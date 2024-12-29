#pragma once

#include "math.h"
#include "vector2.h"

// forward declare Vector4 to avoid circular references (Vector4 is importing Vector3)
class Vector4;

/**
* A vector of length 3
*/
class Vector3 {
private:
	/**
	* The x-value of the vector
	*/
	float _x;

	/**
	* The y-value of the vector
	*/
	float _y;

	/**
	* The z-value of the vector
	*/
	float _z;
public:
	/**
	* Construct a new Vector3 from the given values
	*/
	Vector3(float x, float y, float z);

	/**
	* Returns the x-component of the vector [x y]
	*/
	float x() const;

	/**
	* Returns the y-component of the vector [x y]
	*/
	float y() const;

	/**
	* Returns the z-component of the vector [x y z]
	*/
	float z() const;

	/**
	* Returns the squared magnitude (squared "length") of the vector
	* If performance is an issue use this instead of magnitude if possible
	*/
	float magnitudeSquared() const;

	/**
	* Returns the magnitude ("length") of the vector
	* If performance is an issue use magnitudeSquared if possible
	*/
	float magnitude() const;

	/**
	* Compares two vectors
	* Attention: This compares element-wise and is not safe due to floating-point inaccuracy
	*/
	bool operator==(Vector3 v);

	/**
	* Adds a vector and returns the result as a new vector
	*/
	Vector3 operator+(Vector3 v);

	/**
	* Multiplies this vector with a scalar value (element-wise) and returns the result as a new vector
	*/
	Vector3 operator*(float v);

	/**
	* Divides the vector through a scalar value (element-wise) and returns the result as a new vector
	*/
	Vector3 operator/(float v);

	/**
	* Negates the vector
	*/
	Vector3 operator-();

	/**
	* Subtracts a vector and returns the result as a new vector
	*/
	Vector3 operator-(Vector3 v);

	/**
	* Returns the dot product between this and another vector
	*/
	float dot(Vector3 v) const;

#pragma region Vector2 Conversion Methods
	/**
	* Returns a new vector based on this vector's x and x component
	*/
	Vector2 xx() const;

	/**
	* Returns a new vector based on this vector's x and y component
	*/
	Vector2 xy() const;

	/**
	* Returns a new vector based on this vector's x and z component
	*/
	Vector2 xz() const;

	/**
	* Returns a new vector based on this vector's y and x component
	*/
	Vector2 yx() const;

	/**
	* Returns a new vector based on this vector's y and y component
	*/
	Vector2 yy() const;

	/**
	* Returns a new vector based on this vector's y and z component
	*/
	Vector2 yz() const;

	/**
	* Returns a new vector based on this vector's z and x component
	*/
	Vector2 zx() const;

	/**
	* Returns a new vector based on this vector's z and y component
	*/
	Vector2 zy() const;

	/**
	* Returns a new vector based on this vector's z and z component
	*/
	Vector2 zz() const;
#pragma endregion

	/**
	* Returns a new vector constructed by this vector's x, y and z components and the provided w-component.
	*/
	Vector4 toVector4(float w) const;
};

/**
* Divides a scalar through a Vector3 (element-wise).
*/
Vector3 operator/(float scalar, Vector3 vec);