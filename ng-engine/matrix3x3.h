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
	std::array<float, 9> values;

public:
	/**
	* returns a 3x3 identity matrix
	*/
	static Matrix3x3 identity() {
		return Matrix3x3(1, 0, 0, 0, 1, 0, 0, 0, 1);
	}

	/**
	* returns a transformation matrix for translating by the given vector
	*/
	static Matrix3x3 translate(Vector2 pos) {
		return Matrix3x3(1, 0, pos.x(), 0, 0, pos.y(), 0, 0, 1);
	}

	/**
	* returns a transformation matrix for rotating by the given angle
	*/
	static Matrix3x3 rotate(float rotation) {
		// https://de.wikipedia.org/wiki/Drehmatrix
		float c = cosf(rotation);
		float s = sinf(rotation);
		return Matrix3x3(c, -s, 0, s, c, 0, 0, 0, 1);
	}

	/**
	* returns a transformation matrix for scaling by the given vector
	*/
	static Matrix3x3 scale(Vector2 scale) {
		return Matrix3x3(scale.x(), 0, 0, 0, scale.y(), 0, 0, 0, 1);
	}

	/**
	* returns a transformation matrix for translating, rotating and scaling by the given
	*/
	static Matrix3x3 TRS(Vector2 pos, float rotation, Vector2 scale) {
		return Matrix3x3::translate(pos)
			* Matrix3x3::rotate(rotation)
			* Matrix3x3::scale(scale);
	}

	float a() { return this->getValue(0, 0); }
	float b() { return this->getValue(0, 1); }
	float c() { return this->getValue(0, 2); }
	float d() { return this->getValue(1, 0); }
	float e() { return this->getValue(1, 1); }
	float f() { return this->getValue(1, 2); }
	float g() { return this->getValue(2, 0); }
	float h() { return this->getValue(2, 1); }
	float i() { return this->getValue(2, 2); }

	Matrix3x3(float a, float b, float c, float d, float e, float f, float g, float h, float i) {
		this->values = {
			a, b, c,
			d, e, f,
			g, h, i
		};
	}

	Matrix3x3(std::array<float, 9> values) {
		this->values = values;
	}

	Matrix3x3(std::vector<float> values) {
		if (values.size() != 9) throw std::exception("Invalid size.");
		std::copy_n(values.begin(), 9, this->values.begin());
	}

	std::array<float, 9> getValues() {
		return this->values;
	}

	float getValue(unsigned int x, unsigned int y) {
		if (x > 2 || y > 2) throw new std::exception();

		unsigned int index = y * 3 + x;
		float value = this->values[index];

		return value;
	}

	Matrix3x3 transpose() {
		std::vector<float> retValues;

		for (unsigned int row = 0; row < 3; row++) {
			for (unsigned int column = 0; column < 3; column++) {
				float value = this->getValue(row, column);
				retValues.push_back(value);
			}
		}

		return Matrix3x3(retValues);
	}

	float det() {
		// this is probably more efficient when not generalized,
		// but this can be reused for other matrix sizes as well
		float ret = 0;
		for (unsigned int i = 0; i < 3; i++) {
			float product = 1;
			for (unsigned int j = 0; j < 3; j++) {
				product *= this->getValue(j, (i + j) % 3);
			}
			ret += product;
		}

		return ret;
	}

	Matrix3x3 operator*(Matrix3x3 m) {
		std::array<float, 9> retValues;

		for (unsigned int row = 0; row < 3; row++) {
			for (unsigned int column = 0; column < 3; column++) {
				float sum = 0;
				for (int i = 0; i < 3; i++) {
					sum += this->getValue(i, row) * m.getValue(column, i);
				}

				retValues[column + row * 3] = sum;
			}
		}

		return Matrix3x3(retValues);
	}

	Matrix3x3 operator*(float f) {
		std::array<float, 9> retValues;

		for (unsigned int column = 0; column < 3; column++) {
			for (unsigned int row = 0; row < 3; row++) {
				retValues[column + row * 3] = this->getValue(column, row) * f;
			}
		}

		return Matrix3x3(retValues);
	}

	Matrix3x3 operator/(float f) {
		return (*this) * (1 / f);
	}

	Vector2 operator*(Vector2* v) {
		return Vector2(
			this->a() * v->x() + this->b() * v->y() + this->c() * 1,
			this->d() * v->x() + this->e() * v->y() + this->f() * 1
		);
	}
};