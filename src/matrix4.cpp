#include "headers/matrix4.h"

Matrix4::Matrix4() {
	identity();
}

Matrix4::Matrix4(const float src[16]) {
	m[0] = src[0]; m[1] = src[1]; m[2] = src[2]; m[3] = src[3];
	m[4] = src[4]; m[5] = src[5]; m[6] = src[6]; m[7] = src[7]; 
	m[8] = src[8]; m[9] = src[9]; m[10] = src[10]; m[11] = src[11];
	m[12] = src[12]; m[13] = src[13]; m[14] = src[14]; m[15] = src[15];
}

Matrix4::Matrix4(float m00, float m01, float m02, float m03,
			float m04, float m05, float m06, float m07,
			float m08, float m09, float m10, float m11,
			float m12, float m13, float m14, float m15) {
	m[0] = m00; m[1] = m01; m[2] = m02; m[3] = m03;
	m[4] = m04; m[5] = m05; m[6] = m06; m[7] = m07; 
	m[8] = m08; m[9] = m09; m[10] = m10; m[11] = m11;
	m[12] = m12; m[13] = m13; m[14] = m14; m[15] = m15;
}

const float *Matrix4::get() const {
	return m;
}

Matrix4& Matrix4::identity() {
	m[0] = m[5] = m[10] = m[15] = 1.0f;
	m[1] = m[2] = m[3] = m[4] = m[6] = m[7] = m[8] = m[9] = m[11] = m[12] = m[13] = m[14] = 0.0f;
	return *this;
}

Matrix4 Matrix4::operator+(const Matrix4& rhs) const {
	return Matrix4( m[0]+rhs[0], m[1]+rhs[1], m[2]+rhs[2], m[3]+rhs[3],
			m[4]+rhs[4], m[5]+rhs[5], m[6]+rhs[6], m[7]+rhs[7],
			m[8]+rhs[8], m[9]+rhs[9], m[10]+rhs[10], m[11]+rhs[11],
			m[12]+rhs[12], m[13]+rhs[13], m[14]+rhs[14], m[15]+rhs[15]);
}

Matrix4 Matrix4::operator-(const Matrix4& rhs) const {
	return Matrix4( m[0]-rhs[0], m[1]-rhs[1], m[2]-rhs[2], m[3]-rhs[3],
			m[4]-rhs[4], m[5]-rhs[5], m[6]-rhs[6], m[7]-rhs[7],
			m[8]-rhs[8], m[9]-rhs[9], m[10]-rhs[10], m[11]-rhs[11],
			m[12]-rhs[12], m[13]-rhs[13], m[14]-rhs[14], m[15]-rhs[15]);
}

Matrix4 Matrix4::operator*(const Matrix4& n) const {
	return Matrix4(
			m[0] * n[0]	+ m[4] * n[1] +	m[8] * n[2]	+ m[12]*n[3], 
			m[1] * n[0]	+ m[5] * n[1] +	m[9] * n[2]	+ m[13]*n[3],
		       	m[2] * n[0]	+ m[6] * n[1] +	m[10] * n[2]	+ m[14]*n[3],
		       	m[3] * n[0]	+ m[7] * n[1] +	m[11] * n[2]	+ m[15]*n[3],

		       	m[0] * n[4]	+ m[4] * n[5] +	m[8] * n[6]	+ m[12]*n[7],
			m[1] * n[4]	+ m[5] * n[5] +	m[9] * n[6]	+ m[13]*n[7],
			m[2] * n[4]	+ m[6] * n[5] +	m[10] * n[6]	+ m[14]*n[7],
			m[3] * n[4]	+ m[7] * n[5] +	m[11] * n[6]	+ m[15]*n[7],

			m[0] * n[8]	+ m[4] * n[9] +	m[8] * n[10]	+ m[12]*n[11],
			m[1] * n[8]	+ m[5] * n[9] +	m[9] * n[10]	+ m[13]*n[11],
			m[2] * n[8]	+ m[6] * n[9] +	m[10] * n[10]	+ m[14]*n[11],
			m[3] * n[8]	+ m[7] * n[9] +	m[11] * n[10]	+ m[15]*n[11],

			m[0] * n[12]	+ m[4] * n[13] +	m[8] * n[14]	+ m[12]*n[15],
			m[1] * n[12]	+ m[5] * n[13] +	m[9] * n[14]	+ m[13]*n[15],
			m[2] * n[12]	+ m[6] * n[13] +	m[10] * n[14]	+ m[14]*n[15],
			m[3] * n[12]	+ m[7] * n[13] +	m[11] * n[14]	+ m[15]*n[15]
	);
}

float Matrix4::operator[](int index) const {
	return m[index];
}

float& Matrix4::operator[](int index) {
	return m[index];
}
