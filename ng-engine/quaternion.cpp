#include "quaternion.h"

#include "math.h"
#include "vector3.h"
#include "numbers.h"

Quaternion Quaternion::identity() {
	return Quaternion(0, 0, 0, 1);
}
Quaternion Quaternion::fromAngleAxis(float deg, Vector3 axis) {
	float rad = deg * PI / 180;
	Vector3 vec = axis * sinf(rad / 2);
	float scalar = cosf(rad / 2);

	return Quaternion(vec.x(), vec.y(), vec.z(), scalar);
}

Quaternion Quaternion::fromEulerAngles(float pitch, float roll, float yaw) {
	return Quaternion::fromEulerAngles(Vector3(yaw, roll, pitch));
}

Quaternion Quaternion::fromEulerAngles(Vector3 deg) {
	Vector3 rad = deg * PI / 180;
	float cx = cosf(rad.x() / 2);
	float sx = sinf(rad.x() / 2);
	float cy = cosf(rad.y() / 2);
	float sy = sinf(rad.y() / 2);
	float cz = cosf(rad.z() / 2);
	float sz = sinf(rad.z() / 2);

	return Quaternion(
		sx * sy * sz + cx * sy * cz,
		sx * sy * cz - cx * sy * sz,
		sx * cy * cz + cx * cy * sz,
		cx * cy * cz + sx * sy * sz
	);
}

Quaternion Quaternion::Lerp(Quaternion a, Quaternion b, float t) {
	Vector3 vector = a.vector() * (1 - t) + b.vector() * t;
	float scalar = a.w() * (1 - t) + b.w() * t;

	float factor = sqrtf(vector.magnitudeSquared() + scalar * scalar);

	Vector3 v = vector / factor;
	float w = scalar / factor;

	return Quaternion(v.x(), v.y(), v.z(), w);
}

Quaternion::Quaternion(float x, float y, float z, float w) : _x(x), _y(y), _z(z), _w(w) {
}

float Quaternion::x() const { 
	return this->_x; 
}

float Quaternion::y() const { 
	return this->_y; 
}

float Quaternion::z() const { 
	return this->_z; 
}

float Quaternion::w() const { 
	return this->_w; 
}

Vector3 Quaternion::eulerAngles() const {
	float sx_cy = 2 * (this->w() * this->x() + this->y() * this->z());
	float cx_cy = 1 - 2 * (this->x() * this->x() + this->y() * this->y());
	float sy = sqrtf(1 + 2 * (this->w() * this->y() - this->x() * this->z()));
	float cy = sqrtf(1 - 2 * (this->w() * this->y() - this->x() * this->z()));
	float sz_cy = 2 * (this->w() * this->z() + this->x() * this->y());
	float cz_cy = 1 - 2 * (this->y() * this->y() + this->z() * this->z());

	return Vector3(
		atan2f(sx_cy, cx_cy) * 180 / PI,
		(2 * atan2f(sy, cy) - PI / 2) * 180 / PI,
		atan2f(sz_cy, cz_cy) * 180 / PI
	);
}

Vector3 Quaternion::vector() const {
	return Vector3(this->x(), this->y(), this->z());
}

Quaternion Quaternion::operator*(Quaternion q) {
	Vector3 vector = q.vector() * this->w() + this->vector() * q.w();
	float scalar = this->w() * q.w() - this->vector().dot(q.vector());

	return Quaternion(vector.x(), vector.y(), vector.z(), scalar);
}
