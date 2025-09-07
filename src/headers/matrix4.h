#pragma once


class Matrix4 {
	public:
		Matrix4();
		Matrix4(const float src[16]);
		Matrix4(float m00, float m01, float m02, float m03, 
			float m04, float m05, float m06, float m07,
			float m08, float m09, float m10, float m11,
			float m12, float m13, float m14, float m15);

		const float *get() const;

		Matrix4& identity();

		Matrix4 operator+(const Matrix4& rhs) const;
		Matrix4 operator-(const Matrix4& rhs) const;
		// Matrix4 operator*(const Matrix4& rhs) const;
		// Matrix4& operator+=(const Matrix4& rhs);
		// Matrix4& operator-=(const Matrix4& rhs);
		// Matrix4& operator*=(const Matrix4& rhs);

		float operator[](int index) const;
		float& operator[](int index);

	private:
		float m[16];
};
