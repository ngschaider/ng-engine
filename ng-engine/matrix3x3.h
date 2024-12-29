#pragma once

#include "vector2.h"
#include <array>
#include <vector>
#include <exception>

/**
* Represents a 3x3 matrix
*/
class Matrix3x3 {
private:
	/**
	* The matrix' values in row-major format
	*/
	std::array<float, 9> values;
public:
	/**
	* returns a 3x3 identity matrix
	*/
	static Matrix3x3 identity();

	/**
	* returns a transformation matrix for translating by the given vector
	*/
	static Matrix3x3 translate(Vector2);

	/**
	* returns a transformation matrix for rotating by the given angle
	*/
	static Matrix3x3 rotate(float);

	/**
	* returns a transformation matrix for scaling by the given vector
	*/
	static Matrix3x3 scale(Vector2);

	/**
	* returns a transformation matrix for translating, rotating and scaling by the given
	*/
	static Matrix3x3 TRS(Vector2, float, Vector2);

	/**
	* Returns the matrix' value at column 0, row 0
	*/
	float a();

	/**
	* Returns the matrix' value at column 0, row 1
	*/
	float b();

	/**
	* Returns the matrix' value at column 0, row 2
	*/
	float c();

	/**
	* Returns the matrix' value at column 1, row 0
	*/
	float d();

	/**
	* Returns the matrix' value at column 1, row 1
	*/
	float e();

	/**
	* Returns the matrix' value at column 1, row 2
	*/
	float f();

	/**
	* Returns the matrix' value at column 2, row 0
	*/
	float g();

	/**
	* Returns the matrix' value at column 2, row 1
	*/
	float h();

	/**
	* Returns the matrix' value at column 2, row 2
	*/
	float i();

	/**
	* Constructs a new Matrix3x3 using nine float values
	*/
	Matrix3x3(float, float, float, float, float, float, float, float, float);

	/**
	* Constructs a new Matrix3x3 using array of size 9.
	*/
	Matrix3x3(std::array<float, 9>);

	/**
	* Constructs a new Matrix3x3 using a vector.
	* The vector's size MUST equal 9.
	*/
	Matrix3x3(std::vector<float>);

	/**
	* Returns the matrix' values in row-major format
	*/
	std::array<float, 9> getValues();

	/**
	* Returns the matrix' value at the specifiec column and row.
	*/
	float getValue(unsigned int column, unsigned int row);

	/**
	* Returns the transpose of this matrix.
	*/
	Matrix3x3 transpose();

	/**
	* Returns the determinant of this matrix.
	*/
	float det();

	/**
	* Multiplies this matrix with another matrix.
	*/
	Matrix3x3 operator*(Matrix3x3);

	/**
	* Multiplies this matrix with a scalar (element-wise).
	*/
	Matrix3x3 operator*(float);

	/**
	* Divides this matrix through a scalar (element-wise).
	*/
	Matrix3x3 operator/(float);

	/**
	* Multiplies this matrix with a vector3, resulting in a new vector3.
	* This efficively applies the matrix to the vector3.
	*/
	Vector3 operator*(Vector3*);
};