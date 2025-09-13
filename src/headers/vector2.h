#pragma once

#include <cmath>

class Vector2 {
	public:
		float x, y;

		Vector2(): x(0.0f), y(0.0f) {}
		Vector2(float n): x(n), y(n) {}
		Vector2(float x, float y): x(x), y(y) {}

		inline float magnitude() const { return sqrt(x * x + y * y); };

		Vector2 normalized() const;
		void normalize();

		Vector2& operator*=(const float n);
		Vector2& operator/=(const float n);
		Vector2& operator+=(const Vector2& v);
		Vector2& operator-=(const Vector2& v);

		Vector2 operator*(const Vector2& v);
		Vector2 operator/(const Vector2& v);
		Vector2 operator-(const Vector2& v);
		Vector2 operator+(const Vector2& v);

		Vector2 operator*(const float n);
};
