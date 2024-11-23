#pragma once

#include "vector2.h"

/**
* Represents a 3x3 matrix
*/
class Matrix3x3 {
private:
	float _a;
	float _b;
	float _c;
	float _d;
	float _e;
	float _f;
	float _g;
	float _h;
	float _i;

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

	float a() const { return this->_a; }
	float b() const { return this->_b; }
	float c() const { return this->_c; }
	float d() const { return this->_d; }
	float e() const { return this->_e; }
	float f() const { return this->_f; }
	float g() const { return this->_g; }
	float h() const { return this->_h; }
	float i() const { return this->_i; }

	Matrix3x3(float a, float b, float c, float d, float e, float f, float g, float h, float i) {
		this->_a = a;
		this->_b = b;
		this->_c = c;
		this->_d = d;
		this->_e = e;
		this->_f = f;
		this->_g = g;
		this->_h = h;
		this->_i = i;
	}

	Matrix3x3 transpose() {
		return Matrix3x3(this->a(), this->d(), this->g(), this->b(), this->e(), this->h(), this->c(), this->f(), this->i());
	}

	Matrix3x3 operator*(Matrix3x3* m) {
		// column 1: a, d, g
		// column 2: b, e, h
		// column 3: c, f, i
		// row 1: a, b, c
		// row 2: d, e, f
		// row 3: g, h, i
		return Matrix3x3(
			this->a() * m->a() + this->b() * m->d() + this->c() * m->g(), // row 1, column 1
			this->a() * m->b() + this->b() * m->e() + this->c() * m->h(), // row 1, column 2
			this->a() * m->c() + this->b() * m->f() + this->c() * m->i(), // row 1, column 3
			this->d() * m->a() + this->e() * m->d() + this->f() * m->g(), // row 2, column 1
			this->d() * m->b() + this->e() * m->e() + this->f() * m->h(), // row 2, column 2
			this->d() * m->c() + this->e() * m->f() + this->f() * m->i(), // row 2, column 3
			this->g() * m->a() + this->h() * m->d() + this->i() * m->d(), // row 3, column 1
			this->g() * m->b() + this->h() * m->e() + this->i() * m->h(), // row 3, column 2
			this->g() * m->c() + this->h() * m->f() + this->i() * m->i()  // row 3, column 3
		);
	}
	Matrix3x3 operator*(Matrix3x3 m) {
		return (*this) * &m;
	}

	Vector2 operator*(Vector2* v) {
		return Vector2(
			this->a() * v->x() + this->b() * v->y() + this->c() * 1,
			this->d() * v->x() + this->e() * v->y() + this->f() * 1
		);
	}
};