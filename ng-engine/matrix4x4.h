#pragma once

#include "vector3.h"

class Matrix4x4 {
private:
	float _a; float _b; float _c; float _d;
	float _e; float _f; float _g; float _h;
	float _i; float _j; float _k; float _l;
	float _m; float _n; float _o; float _p;
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
		float c = cos(rotation);
		float s = sin(rotation);
		return Matrix4x4(
			1, 0, 0, 0,
			0, c, -s, 0,
			0, s, c, 0,
			0, 0, 0, 1
		);
	}

	static Matrix4x4 rotateY(float rotation) {
		const c = cos(rotation);
		const s = sin(rotation);
		return Matrix4x4(
			c, 0, s, 0,
			0, 1, 0, 0,
			-s, 0, c, 0,
			0, 0, 0, 1
		);
	}

	static Matrix4x4 rotateZ(float rotation) {
		float c = cos(rotation);
		float s = sin(rotation);
		return Matrix4x4(
			c, -s, 0, 0,
			s, c, 0, 0,
			0, 0, 1, 0,
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
			* Matrix4x4::rotateZ(euler.z())
			* Matrix4x4::rotateY(euler.y())
			* Matrix4x4::rotateX(euler.x())
			* Matrix4x4::scale(scaling);
	}

	Matrix4x4(float a, float b, float c, float d,
		float e, float f, float g, float h,
		float i, float j, float k, float l,
		float m, float n, float o, float p) {
		this->_a = a; this->_b = b; this->_c = c; this->_d = d;
		this->_e = e; this->_f = f; this->_g = g; this->_h = h;
		this->_i = i; this->_j = j; this->_k = k; this->_l = l;
		this->_m = m; this->_n = n; this->_o = o; this->_p = p;
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
	float j() const { return this->_j; }
	float k() const { return this->_k; }
	float l() const { return this->_l; }
	float m() const { return this->_m; }
	float n() const { return this->_n; }
	float o() const { return this->_o; }
	float p() const { return this->_p; }

	Matrix4x4 operator*(Matrix4x4 m) {
		return Matrix4x4(
			this->a() * m.a() + this->b() * m.e() + this->c() * m.i() + this->d() * m.m(), // row 1, column 1
			this->a() * m.b() + this->b() * m.f() + this->c() * m.j() + this->d() * m.n(), // row 1, column 2
			this->a() * m.c() + this->b() * m.g() + this->c() * m.k() + this->d() * m.o(), // row 1, column 3
			this->a() * m.d() + this->b() * m.h() + this->c() * m.l() + this->d() * m.p(), // row 1, column 4
			this->e() * m.a() + this->f() * m.e() + this->g() * m.i() + this->h() * m.m(), // row 2, column 1
			this->e() * m.b() + this->f() * m.f() + this->g() * m.j() + this->h() * m.n(), // row 2, column 2
			this->e() * m.c() + this->f() * m.g() + this->g() * m.k() + this->h() * m.o(), // row 2, column 3
			this->e() * m.d() + this->f() * m.h() + this->g() * m.l() + this->h() * m.p(), // row 2, column 4
			this->i() * m.a() + this->j() * m.e() + this->k() * m.i() + this->k() * m.m(), // row 3, column 1
			this->i() * m.b() + this->j() * m.f() + this->k() * m.j() + this->k() * m.n(), // row 3, column 2
			this->i() * m.c() + this->j() * m.g() + this->k() * m.k() + this->k() * m.o(), // row 3, column 3
			this->i() * m.d() + this->j() * m.h() + this->k() * m.l() + this->k() * m.p(), // row 3, column 4
			this->m() * m.a() + this->n() * m.e() + this->o() * m.i() + this->p() * m.m(), // row 4, column 1
			this->m() * m.b() + this->n() * m.f() + this->o() * m.j() + this->p() * m.n(), // row 4, column 2
			this->m() * m.c() + this->n() * m.g() + this->o() * m.k() + this->p() * m.o(), // row 4, column 3
			this->m() * m.d() + this->n() * m.h() + this->o() * m.l() + this->p() * m.p() // row 4, column 4
		);
	}
};