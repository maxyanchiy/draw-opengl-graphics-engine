#pragma once

#include "../gmath.h"

class vector3d {
public:
	vector3d(const float& in_x, const float& in_y, const float& in_z) {
		x = in_x;
		y = in_y;
		z = in_z;
	}

	vector3d(const vector3d& v) {
		x = v.x;
		y = v.y;
		z = v.z;
	}

	~vector3d() {}

	const vector3d operator + (const vector3d& v) const {
		return vector3d(x + v.x, y + v.y, z + v.z);
	}

	void operator += (const vector3d& v){
		x += v.x;
		y += v.y;
		z += v.z;
	}

	const vector3d operator - (const vector3d& v) const {
		return vector3d(x - v.x, y - v.y, z - v.z);
	}

	void operator -= (const vector3d& v) {
		x -= v.x;
		y -= v.y;
		z -= v.z;
	}

	void operator = (const vector3d& v) {
		x = v.x;
		y = v.y;
		z = v.z;
	}

	const vector3d operator * (const float& scalar) const {
		return vector3d(x * scalar, y * scalar, z * scalar);
	}

	void operator *= (const float& scalar) {
		x *= scalar;
		y *= scalar;
		z *= scalar;
	}

	const vector3d operator / (const float& scalar) const {
		return vector3d(x / scalar, y / scalar, z / scalar);
	}

	void operator /= (const float& scalar) {
		x /= scalar;
		y /= scalar;
		z /= scalar;
	}

	const float operator * (const vector3d& v) const {
		return x * v.x + y* v.y + z* v.z;
	}

	const float dot(const vector3d& v) const {
		return x * v.x + y* v.y + z* v.z;
	}

	const vector3d operator ^ (const vector3d& v) const{
		return vector3d(
			y * v.z - z * v.y,
			z * v.x - x * v.z,
			x * v.y - y * v.x
		);
	}

	const vector3d cross (const vector3d& v) {
		return vector3d(
			y * v.z - z * v.y,
			z * v.x - x * v.z,
			x * v.y - y * v.x
		);
	}

	const float magnitude() {
		return std::sqrt(x * x + y * y + z * z);
	}

	void normalize() {
		const float squaredCompSum = x * x + y * y + z * z;
		if (squaredCompSum > 0.f) {
			const float invSqr = GMath::fastInvSqrt(squaredCompSum);
			x *= invSqr;
			y *= invSqr;
			z *= invSqr;
		}
	}	

	static const float distance(const vector3d& v_a, const vector3d& v_b) {
		const float dx = v_b.x - v_a.x;
		const float dy = v_b.y - v_a.y;
		const float dz = v_b.z - v_a.z;

		return std::sqrt(dx * dx + dy * dy + dz * dz);
	}
	static const float distance_squared(const vector3d& v_a, const vector3d& v_b) {
		const float dx = v_b.x - v_a.x;
		const float dy = v_b.y - v_a.y;
		const float dz = v_b.z - v_a.z;

		return dx * dx + dy * dy + dz * dz;
	}


	float x;
	float y;
	float z;
};

class vector2d {

};
