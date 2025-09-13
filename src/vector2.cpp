#include "headers/vector2.h"

Vector2 Vector2::normalized() const {
	if (magnitude() == 0.0f) return Vector2();
	return Vector2(x / magnitude(), y / magnitude());
}

void Vector2::normalize() {
	x /= magnitude();
	y /= magnitude();
}

Vector2& Vector2::operator*=(const float n) {
	x *= n;
	y *= n;
	return *this;
}

Vector2& Vector2::operator/=(const float n) {
	x /= n;
	y /= n;
	return *this;
}

Vector2& Vector2::operator+=(const Vector2& v) {
	x += v.x;
	y += v.y;
	return *this;
}

Vector2& Vector2::operator-=(const Vector2& v) {
	x -= v.x;
	y -= v.y;
	return *this;
}

Vector2 Vector2::operator*(const Vector2& v) {
	return Vector2(x*v.x, y*v.y);
}

Vector2 Vector2::operator/(const Vector2& v) {
	return Vector2(x/v.x, y/v.y);
}

Vector2 Vector2::operator+(const Vector2& v) {
	return Vector2(x+v.x, y+v.y);
}

Vector2 Vector2::operator-(const Vector2& v) {
	return Vector2(x-v.x, y-v.y);
}

Vector2 Vector2::operator*(const float n) {
	return Vector2(x*n, y*n);
}
