#pragma once

#include "math.h"
#include "vector3.h"

#define PI 3.141592653f

class Quaternion {
private:
	float _x;
	float _y;
	float _z;
	float _w;
public:
	static Quaternion identity() {
		return Quaternion(0, 0, 0, 1);
	}

	static Quaternion fromAngleAxis(Vector3 ax) {
		float cx = cosf(ax.x() / 2);
		float sx = sinf(ax.x() / 2);
		float cy = cosf(ax.y() / 2);
		float sy = sinf(ax.y() / 2);
		float cz = cosf(ax.z() / 2);
		float sz = sinf(ax.z() / 2);

		return Quaternion(
			cx * cy * cz + sx * sy * sz,
			sx * cy * cz - cx * sy * sz,
			cx * cy * sz + sx * cy * sz,
			cx * cy * sz - sx * sy * cz
		);
	}

	static Quaternion Lerp(Quaternion a, Quaternion b, float t) {
		Vector3 vector = a.vector() * (1 - t) + b.vector() * t;
		float scalar = a.w() * (1 - t) + b.w() * t;

		float factor = sqrtf(vector.magnitudeSquared() + scalar * scalar);

		Vector3 v = vector / factor;
		float w = scalar / factor;

		return Quaternion(v.x(), v.y(), v.z(), w);
	}

	Quaternion(float x, float y, float z, float w) {
		this->_x = x;
		this->_y = y;
		this->_z = z;
		this->_w = w;
	}

	float x() const { return this->_x; }
	float y() const { return this->_y; }
	float z() const { return this->_z; }
	float w() const { return this->_w; }

	Vector3 eulerAngles() {
		float sx_cy = 2 * (this->w() * this->x() + this->y() * this->z());
		float cx_cy = 1 - 2 * (this->x() * this->x() + this->y() * this->y());
		float sy = sqrtf(1 + 2 * (this->w() * this->y() - this->x() * this->z()));
		float cy = sqrtf(1 - 2 * (this->w()* this->y() - this->x() * this->z()));
		float sz_cy = 2 * (this->w() * this->z() + this->x() * this->y());
		float cz_cy = 1 - 2 * (this->y() * this->y() + this->z() * this->z());

		return Vector3(
			atan2f(sx_cy, cx_cy) * 180 / PI,
			(2 * atan2f(sy, cy) - PI / 2) * 180 / PI,
			atan2f(sz_cy, cz_cy) * 180 / PI
		);
	}

	Vector3 vector() {
		return Vector3(this->x(), this->y(), this->z());
	}

	Quaternion operator*(Quaternion q) {
		Vector3 vector = q.vector() * this->w() + this->vector() * q.w();
		float scalar = this->w() * q.w() - this->vector().dot(q.vector());

		return Quaternion(vector.x(), vector.y(), vector.z(), scalar);
	}
};