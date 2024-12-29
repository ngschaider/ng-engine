#pragma once

#include "vector3.h"
#include "vector4.h"
#include "quaternion.h"
#include "matrix3x3.h"
#include <array>
#include <vector>

class Matrix4x4 {
private:
	/**
	* The values of the matrix in row-major format
	*/
	std::array<float, 16> values;

	/**
	* Sets the matrix' cell at the specified column and row to the specified value 
	* This is private as we do not want to modify the matrix after instantiation and this is the only way we can make sure nobody modifies it from the outside!
	* We still have to be careful to only modify the matrix using this immediately after instantiation. Once we return the matrix to the user we cannot modify it safely anymore!
	*/
	void setValue(unsigned int column, unsigned int row, float value);
public:
	/**
	* Returns a 4x4 identity matrix
	*/
	static Matrix4x4 identity();

	/**
	* Returns a 4x4 transformation matrix that can be used to translate any vector by the given position
	*/
	static Matrix4x4 translate(Vector3 pos);

	/**
	* Returns a 4x4 transformation matrix that can be used to rotate any vector around the x-axis by the given rotation
	*/
	static Matrix4x4 rotateX(float rotation);

	/**
	* Returns a 4x4 transformation matrix that can be used to rotate any vector around the y-axis by the given rotation
	*/
	static Matrix4x4 rotateY(float rotation);

	/**
	* Returns a 4x4 transformation matrix that can be used to rotate any vector around the z-axis by the given rotation
	*/
	static Matrix4x4 rotateZ(float rotation);

	/**
	* Returns a 4x4 transformation matrix that can be used to rotate any vector by the given quaternion
	*/
	static Matrix4x4 rotate(Quaternion q);

	/**
	* Returns a 4x4 transformation matrix that can be used to scale any vector by the given factors
	*/
	static Matrix4x4 scale(Vector3 scale);

	/**
	* Returns a 4x4 orthographics projections matrix
	*/
	static Matrix4x4 orthographic(Vector3 pos, Vector3 size, float near, float far);

	/**
	* Returns a 4x4 transformation matrix that can be used to translate, rotate and scale any vector by the given vectors.
	*/
	static Matrix4x4 TRS(Vector3 pos, Quaternion rotation, Vector3 scaling);

	/**
	* Constructs a new Matrix4x4 instance using the specified values
	*/
	Matrix4x4(float a, float b, float c, float d, 
		float e, float f, float g, float h, 
		float i, float j, float k, float l, 
		float m, float n, float o, float p);

	/**
	* Constructs a new Matrix4x4 instance using the specified values
	*/
	Matrix4x4(std::array<float, 16> values);

	/**
	* Constructs a new Matrix4x4 instance using the specified values.
	* The given vector must have a length of exactly 16.
	*/
	Matrix4x4(std::vector<float> values);

	/**
	* Returns an array of all 16 elements of the array sorted in row major format
	*/
	std::array<float, 16> getValues();

	/**
	* Returns the value of the matrix at row `y` and column `x`
	*/
	float getValue(unsigned int x, unsigned int y);

	/**
	* Returns the matrix' value at column 0, row 0
	*/
	float a();

	/**
	* Returns the matrix' value at column 1, row 0
	*/
	float b();

	/**
	* Returns the matrix' value at column 2, row 0
	*/
	float c();

	/**
	* Returns the matrix' value at column 3, row 0
	*/
	float d();

	/**
	* Returns the matrix' value at column 0, row 1
	*/
	float e();

	/**
	* Returns the matrix' value at column 1, row 1
	*/
	float f();

	/**
	* Returns the matrix' value at column 2, row 1
	*/
	float g();

	/**
	* Returns the matrix' value at column 3, row 1
	*/
	float h();

	/**
	* Returns the matrix' value at column 0, row 2
	*/
	float i();

	/**
	* Returns the matrix' value at column 1, row 2
	*/
	float j();

	/**
	* Returns the matrix' value at column 2, row 2
	*/
	float k();

	/**
	* Returns the matrix' value at column 3, row 2
	*/
	float l();

	/**
	* Returns the matrix' value at column 0, row 3
	*/
	float m();

	/**
	* Returns the matrix' value at column 1, row 3
	*/
	float n();

	/**
	* Returns the matrix' value at column 2, row 3
	*/
	float o();

	/**
	* Returns the matrix' value at column 3, row 3
	*/
	float p();

	/**
	* Multiplies the Matrix4x4 with the given value (element-wise) and returns the result in a new Matrix4x4.
	*/
	Matrix4x4 operator*(float f);

	/**
	* Divides the matrix by the given value (element-wise) and returns the result in a new Matrix4x4.
	*/
	Matrix4x4 operator/(float f);

	/**
	* Multiplies the matrix with another matrix using standard mathematics and returns the result in a new Matrix4x4.
	*/
	Matrix4x4 operator*(Matrix4x4 m);

	/**
	* Multiplies the matrix with a vector of length 4 and returns the result in a new Vector4.
	* One could also call this "applying" the matrix to the vector.
	*/
	Vector4 operator*(Vector4 v);

	/**
	* Returns the determinant of the matrix
	*/
	float det();

	/**
	* Returns the adjugate of this matrix
	*/
	Matrix4x4 adj();

	/**
	* Returns the inverse of this matrix
	*/
	Matrix4x4 invert();
};