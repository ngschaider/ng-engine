#pragma once

#include "vector3.h"
#include "quaternion.h"
#include "matrix3x3.h"
#include <array>
#include <vector>
#include <exception>

class Matrix4x4 {
private:
	std::array<float, 16> values;

	// keep this private as we do not want to modify the matrix after instantiation and
	// this is the only way we can make sure nobody modifies it from the outside!
	void setValue(unsigned int x, unsigned int y, float value) {
		if (x > 3 || y > 3) throw new std::exception();

		unsigned int index = y * 4 + x;
		values[index] = value;
	}
public:
	static Matrix4x4 identity() {
		return Matrix4x4(
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1
		);
	}

	static Matrix4x4 translate(Vector3 pos) {
		return Matrix4x4(
			1, 0, 0, pos.x(),
			0, 1, 0, pos.y(),
			0, 0, 1, pos.z(),
			0, 0, 0, 1
		);
	}

	static Matrix4x4 rotateX(float rotation) {
		float c = cosf(rotation / 180 * PI);
		float s = sinf(rotation / 180 * PI);
		return Matrix4x4(
			1, 0, 0, 0,
			0, c, -s, 0,
			0, s, c, 0,
			0, 0, 0, 1
		);
	}

	static Matrix4x4 rotateY(float rotation) {
		float c = cosf(rotation / 180 * PI);
		float s = sinf(rotation / 180 * PI);
		return Matrix4x4(
			c, 0, s, 0,
			0, 1, 0, 0,
			-s, 0, c, 0,
			0, 0, 0, 1
		);
	}

	static Matrix4x4 rotateZ(float rotation) {
		float c = cosf(rotation / 180 * PI);
		float s = sinf(rotation / 180 * PI);
		return Matrix4x4(
			c, -s, 0, 0,
			s, c, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1
		);
	}

	static Matrix4x4 rotate(Quaternion q) {
		float x2 = powf(q.x(), 2);
		float y2 = powf(q.y(), 2);
		float z2 = powf(q.z(), 2);
		float w2 = powf(q.w(), 2);
		return Matrix4x4(
			w2 + x2 - y2 - z2, -2 * q.w() * q.z() + 2 * q.x() * q.y(), 2 * q.w() * q.x() + 2 * q.x() * q.y(), 0,
			2 * q.w() * q.z() + 2 * q.x() * q.y(), w2 - x2 + y2 - z2, -2 * q.w() * q.x() + 2 * q.y() * q.z(), 0,
			-2 * q.w() * q.y() + 2 * q.x() * q.z(), 2 * q.w() * q.x() + 2 * q.y() * q.z(), w2 - x2 - y2 + z2, 0,
			0, 0, 0, 1
		);
	}

	static Matrix4x4 scale(Vector3 scale) {
		return Matrix4x4(
			scale.x(), 0, 0, 0,
			0, scale.y(), 0, 0,
			0, 0, scale.z(), 0,
			0, 0, 0, 1
		);
	}

	static Matrix4x4 orthographic(Vector3 pos, Vector3 size, float near, float far) {
		return Matrix4x4(
			2 / size.x(), 0, 0, pos.x(),
			0, 2 / size.y(), 0, pos.y(),
			0, 0, 2 / (near - far), pos.z(),
			0, 0, 0, 1
		);
	}

	static Matrix4x4 TRS(Vector3 pos, Quaternion rotation, Vector3 scaling) {
		Vector3 euler = rotation.eulerAngles();

		return Matrix4x4::translate(pos)
			// * Matrix4x4::rotate(rotation)
			* Matrix4x4::rotateZ(euler.z())
			* Matrix4x4::rotateY(euler.y())
			* Matrix4x4::rotateX(euler.x())
			* Matrix4x4::scale(scaling);
	}

	Matrix4x4(float a, float b, float c, float d, 
		float e, float f, float g, float h, 
		float i, float j, float k, float l, 
		float m, float n, float o, float p) {
		this->values = {
			a, b, c, d,
			e, f, g, h,
			i, j, k, l,
			m, n, o, p
		};
	}

	Matrix4x4(std::array<float, 16> values) {
		this->values = values;
	}

	Matrix4x4(std::vector<float> values) {
		if (values.size() != 16) throw new std::exception("Invalid size.");
		std::copy_n(values.begin(), 16, this->values.begin());
	}

	std::array<float, 16> getValues() {
		return this->values;
	}

	float getValue(unsigned int x, unsigned int y) {
		if (x > 3 || y > 3) throw new std::exception();

		unsigned int index = y * 4 + x;
		float value = this->values[index];

		return value;
	}

	float a() { return this->getValue(0, 0); }
	float b() { return this->getValue(1, 0); }
	float c() { return this->getValue(2, 0); }
	float d() { return this->getValue(3, 0); }
	float e() { return this->getValue(0, 1); }
	float f() { return this->getValue(1, 1); }
	float g() { return this->getValue(2, 1); }
	float h() { return this->getValue(3, 1); }
	float i() { return this->getValue(0, 2); }
	float j() { return this->getValue(1, 2); }
	float k() { return this->getValue(2, 2); }
	float l() { return this->getValue(3, 2); }
	float m() { return this->getValue(0, 3); }
	float n() { return this->getValue(1, 3); }
	float o() { return this->getValue(2, 3); }
	float p() { return this->getValue(3, 3); }

	Matrix4x4 operator*(float f) {
		std::array<float, 16> retValues;

		for (unsigned int row = 0; row < 4; row++) {
			for (unsigned int column = 0; column < 4; column++) {
				retValues[column + row * 4] = this->getValue(column, row) * f;
			}
		}

		return Matrix4x4(retValues);
	}

	Matrix4x4 operator/(float f) {
		return (*this) * (1 / f);
	}

	Matrix4x4 operator*(Matrix4x4 m) {
		std::array<float, 16> retValues;

		for (unsigned int row = 0; row < 4; row++) {
			for (unsigned int column = 0; column < 4; column++) {
				float sum = 0;
				for (int i = 0; i < 4; i++) {					
					sum += this->getValue(i, row) * m.getValue(column, i);
				}

				retValues[column + row * 4] = sum;
			}
		}

		return Matrix4x4(retValues);
	}

	float det() {
		// this is probably more efficient when not generalized,
		// but this can be reused for other matrix sizes as well
		float ret = 0;
		for (unsigned int i = 0; i < 4; i++) {
			float product = 1;
			for (unsigned int j = 0; j < 4; j++) {
				product *= this->getValue(j, (i + j) % 4);
			}
			ret += product;
		}

		return ret;
	}

	Matrix4x4 adj() {
		std::array<float, 16> retValues;
		int retIndex = 0;
		for (unsigned int row = 0; row < 4; row++) {
			for (unsigned int column = 0; column < 4; column++) {
				// get the minor for the given (column, row) of the "this" matrix
				std::array<float, 9> minorValues = {};
				int minorIndex = 0;
				for (unsigned int y = 0; y < 4; y++) {
					for (unsigned int x = 0; x < 4; x++) {
						if (x == row || y == column) continue;
						minorValues[minorIndex] = this->getValue(x, y);
						minorIndex++;
					}
				}
				Matrix3x3 minor = Matrix3x3(minorValues);

				// calculate the cofactor
				float exponent = (row + column) * 1.0f;
				float cofactor = powf(-1, exponent) * minor.det();

				retValues[retIndex] = cofactor;
				retIndex++;
			}
		}

		return Matrix4x4(retValues);
	}

	Matrix4x4 invert() {
		return this->adj() / this->det();
	}
};