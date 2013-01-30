////////////////////////////////////////////////////////////////////////////////
// \file    Algebra.hpp
// \author  Jonathan Dupuy (onrendering@gmail.com)
// \brief   Simple algebra library.
//          List of classes
//          - Vector2: 2d column vector
//          - Vector3: 3d column vector
//          - Vector4: 4d column vector
//          - Matrix2x2: 2x2 square, column major matrix
//          - Matrix3x3: 3x3 square, column major matrix
//          - Matrix4x4: 4x4 square, column major matrix
//          Notes:
//          - angles must be provided in radians
//
////////////////////////////////////////////////////////////////////////////////

#ifndef ALGEBRA_HPP
#define ALGEBRA_HPP

#include <cstring>

////////////////////////////////////////////////////////////////////////////////
// Vector2 definition
class Vector2 {
public:
	// Factories
	static Vector2 CompMult(const Vector2& u,
	                        const Vector2& v);
	static Vector2 CompDiv(const Vector2& u,
	                       const Vector2& v);
	static Vector2 CompPow(const Vector2& base,
	                       const Vector2& exponent);
	static Vector2 CompMin(const Vector2& u,
	                       const Vector2& v);
	static Vector2 CompMax(const Vector2& u,
	                       const Vector2& v);
	static Vector2 CompClamp(const Vector2& v,
	                         const Vector2& min,
	                         const Vector2& max);

	// Factories (continued)
	static Vector2 Reflect(const Vector2& incident,
	                       const Vector2& unitNormal);
	static Vector2 Refract(const Vector2& unitIncident,
	                       const Vector2& unitNormal,
	                       const float& eta);

	// Static manipulation
	static float DotProduct(const Vector2& u, const Vector2& v);

	// Constructors
	Vector2(const float& x =0,
	        const float& y =0);

	// Access operators
	const float& operator[](size_t row) const;
	float& operator[](size_t row);

	// Arithmetic operators
	Vector2 operator+(const Vector2& v) const;
	Vector2 operator-(const Vector2& v) const;
	Vector2 operator*(const float& s)   const;
	Vector2 operator/(const float& s)   const;
	Vector2 operator+() const;
	Vector2 operator-() const;

	// Assignment operators
	Vector2& operator*=(const float& s);
	Vector2& operator+=(const Vector2& v);
	Vector2& operator-=(const Vector2& v);
	Vector2& operator/=(const float& s);

	// Comparison operators
	bool operator==(const Vector2& m) const;
	bool operator!=(const Vector2& m) const;

	// Queries
	float Length()        const;
	float LengthSquared() const;
	Vector2 Normalize()   const;

	// Per component queries
	Vector2 Sign()        const;
	Vector2 Abs()         const;
	Vector2 Sqr()         const;
	Vector2 Sqrt()        const;
	Vector2 Exp()         const;
	Vector2 Log()         const;
	Vector2 Log10()       const;
	Vector2 Ceil()        const;
	Vector2 Floor()       const;
	Vector2 Frac()        const;

	// Constants
	static const Vector2 ZERO;

private:
	// Members
	float mX, mY;
};


////////////////////////////////////////////////////////////////////////////////
// Vector3 definition
class Vector3 {
public:
	// Factories
	static Vector3 CrossProduct(const Vector3& u,
	                            const Vector3& v);
	static Vector3 CompMult(const Vector3& u,
	                        const Vector3& v);
	static Vector3 CompDiv(const Vector3& u,
	                       const Vector3& v);
	static Vector3 CompPow(const Vector3& base,
	                       const Vector3& exponent);
	static Vector3 CompMin(const Vector3& u,
	                       const Vector3& v);
	static Vector3 CompMax(const Vector3& u,
	                       const Vector3& v);
	static Vector3 CompClamp(const Vector3& v,
	                         const Vector3& min,
	                         const Vector3& max);

	// Factories (continued)
	static Vector3 Reflect(const Vector3& incident,
	                       const Vector3& unitNormal);
	static Vector3 Refract(const Vector3& unitIncident,
	                       const Vector3& unitNormal,
	                       const float& eta);

	// Static manipulation
	static float DotProduct(const Vector3& u, const Vector3& v);

	// Constructors
	Vector3(const float& x =0,
	        const float& y =0,
	        const float& z =0);

	// Access operators
	const float& operator[](size_t row) const;
	float& operator[](size_t row);

	// Arithmetic operators
	Vector3 operator+(const Vector3& v) const;
	Vector3 operator-(const Vector3& v) const;
	Vector3 operator*(const float& s)   const;
	Vector3 operator/(const float& s)   const;
	Vector3 operator+() const;
	Vector3 operator-() const;

	// Assignment operators
	Vector3& operator+=(const Vector3& v);
	Vector3& operator-=(const Vector3& v);
	Vector3& operator*=(const float& s);
	Vector3& operator/=(const float& s);

	// Comparison operators
	bool operator==(const Vector3& m) const;
	bool operator!=(const Vector3& m) const;

	// Queries
	float Length()        const;
	float LengthSquared() const;
	Vector3 Normalize()   const;

	// Per component queries
	Vector3 Sign()        const;
	Vector3 Abs()         const;
	Vector3 Sqr()         const;
	Vector3 Sqrt()        const;
	Vector3 Exp()         const;
	Vector3 Log()         const;
	Vector3 Log10()       const;
	Vector3 Ceil()        const;
	Vector3 Floor()       const;
	Vector3 Frac()        const;

	// Constants
	static const Vector3 ZERO;

private:
	// Members
	float mX, mY, mZ;
};


////////////////////////////////////////////////////////////////////////////////
// Vector4 definition
class Vector4 {
public:
	// Factories
	static Vector4 CompMult(const Vector4& u,
	                        const Vector4& v);
	static Vector4 CompDiv(const Vector4& u,
	                       const Vector4& v);
	static Vector4 CompPow(const Vector4& base,
	                       const Vector4& exponent);
	static Vector4 CompMin(const Vector4& u,
	                       const Vector4& v);
	static Vector4 CompMax(const Vector4& u,
	                       const Vector4& v);
	static Vector4 CompClamp(const Vector4& v,
	                         const Vector4& min,
	                         const Vector4& max);

	// Static manipulation
	static float DotProduct(const Vector4& u, const Vector4& v);

	// Constructors
	Vector4(const float& x =0,
	        const float& y =0,
	        const float& z =0,
	        const float& w =0);

	// Access operators
	const float&  operator[](size_t row) const;
	float& operator[](size_t row);

	// Arithmetic operators
	Vector4 operator+(const Vector4& v) const;
	Vector4 operator-(const Vector4& v) const;
	Vector4 operator*(const float& s)   const;
	Vector4 operator/(const float& s)   const;
	Vector4 operator+() const;
	Vector4 operator-() const;

	// Assignment operators
	Vector4& operator+=(const Vector4& v);
	Vector4& operator-=(const Vector4& v);
	Vector4& operator*=(const float& s);
	Vector4& operator/=(const float& s);

	// Comparison operators
	bool operator==(const Vector4& m) const;
	bool operator!=(const Vector4& m) const;

	// Queries
	float Length()        const;
	float LengthSquared() const;
	Vector4 Normalize()   const;

	// Per component queries
	Vector4 Sign()        const;
	Vector4 Abs()         const;
	Vector4 Sqr()         const;
	Vector4 Sqrt()        const;
	Vector4 Exp()         const;
	Vector4 Log()         const;
	Vector4 Log10()       const;
	Vector4 Ceil()        const;
	Vector4 Floor()       const;
	Vector4 Frac()        const;

	// Constants
	static const Vector4 ZERO;

private:
	// Members
	float mX, mY, mZ, mW;
};


////////////////////////////////////////////////////////////////////////////////
// Matrix2x2 definition
class Matrix2x2 {
public:
	// Factories
	static Matrix2x2 CompMult(const Matrix2x2& m1,
	                          const Matrix2x2& m2);
	static Matrix2x2 CompDiv(const Matrix2x2& m1,
	                         const Matrix2x2& m2);
	static Matrix2x2 CompPow(const Matrix2x2& base,
	                         const Matrix2x2& exponent);
	static Matrix2x2 CompMin(const Matrix2x2& m1,
	                         const Matrix2x2& m2);
	static Matrix2x2 CompMax(const Matrix2x2& m1,
	                         const Matrix2x2& m2);
	static Matrix2x2 CompClamp(const Matrix2x2& m,
	                           const Matrix2x2& min,
	                           const Matrix2x2& max);

	// Factories (continued)
	static Matrix2x2 OuterProduct(const Vector2& c, 
	                              const Vector2& r);
	static Matrix2x2 Diagonal(const float& m00,
	                          const float& m11);
	static Matrix2x2 Rotation(const float& radians);
	static Matrix2x2 Scale(const float& x,
	                       const float& y);

	// Constructors
	Matrix2x2(const Vector2& c0,
	          const Vector2& c1);
	Matrix2x2(const float& m00 =0, const float& m10 =0,
	          const float& m01 =0, const float& m11 =0);

	// Access operators
	const Vector2& operator[](size_t column) const;
	Vector2& operator[](size_t column);

	// Arithmetic operators
	Matrix2x2 operator+(const Matrix2x2& m)  const;
	Matrix2x2 operator-(const Matrix2x2& m)  const;
	Matrix2x2 operator+()                    const;
	Matrix2x2 operator-()                    const;
	Matrix2x2 operator*(const Matrix2x2& m)  const;
	Vector2   operator*(const Vector2& v)    const;

	// Assignment operators
	Matrix2x2& operator+=(const Matrix2x2& m);
	Matrix2x2& operator-=(const Matrix2x2& m);
	Matrix2x2& operator*=(const Matrix2x2& m);

	// Comparison operators
	bool operator==(const Matrix2x2& m) const;
	bool operator!=(const Matrix2x2& m) const;

	// Queries
	bool IsInvertible()   const;
	float Determinant()   const;
	Matrix2x2 Inverse()   const;
	Matrix2x2 Transpose() const;
	Matrix2x2 Adjugate()  const;

	// Per component queries
	Matrix2x2 Sign()   const;
	Matrix2x2 Abs()    const;
	Matrix2x2 Sqr()    const;
	Matrix2x2 Sqrt()   const;
	Matrix2x2 Exp()    const;
	Matrix2x2 Log()    const;
	Matrix2x2 Log10()  const;
	Matrix2x2 Ceil()   const;
	Matrix2x2 Floor()  const;
	Matrix2x2 Frac()   const;

	// Constants
	static const Matrix2x2 IDENTITY;

private:
	// Members
	Vector2 mC0, mC1; // columns
};


////////////////////////////////////////////////////////////////////////////////
// Matrix3x3 definition
class Matrix3x3 {
public:
	// Factories
	static Matrix3x3 CompMult(const Matrix3x3& m1,
	                          const Matrix3x3& m2);
	static Matrix3x3 CompDiv(const Matrix3x3& m1,
	                         const Matrix3x3& m2);
	static Matrix3x3 CompPow(const Matrix3x3& base,
	                         const Matrix3x3& exponent);
	static Matrix3x3 CompMin(const Matrix3x3& m1,
	                         const Matrix3x3& m2);
	static Matrix3x3 CompMax(const Matrix3x3& m1,
	                         const Matrix3x3& m2);
	static Matrix3x3 CompClamp(const Matrix3x3& m,
	                           const Matrix3x3& min,
	                           const Matrix3x3& max);

	// Factories (continued)
	static Matrix3x3 OuterProduct(const Vector3& c, 
	                              const Vector3& r);
	static Matrix3x3 Diagonal(const float& m00,
	                          const float& m11,
	                          const float& m22);
	static Matrix3x3 RotationAboutX(const float& radians);
	static Matrix3x3 RotationAboutY(const float& radians);
	static Matrix3x3 RotationAboutZ(const float& radians);
	static Matrix3x3 Rotation(const float& yaw,
	                          const float& pitch,
	                          const float& roll);
	static Matrix3x3 RotationAboutAxis(const Vector3& unitAxis,
	                                   const float& radians);
	static Matrix3x3 VectorRotation(const Vector3& unitFrom,
	                                const Vector3& unitTo);
	static Matrix3x3 LookAtRotation(const Vector3& eyePos,
	                                const Vector3& targetPos,
	                                const Vector3& unitUpVector);
	static Matrix3x3 Scale(const float& x,
	                       const float& y,
	                       const float& z);

	// Constructors
	Matrix3x3(const Vector3& c0,
	          const Vector3& c1,
	          const Vector3& c2);
	Matrix3x3(const float& m00 =0, const float& m10 =0, const float& m20 =0,
	          const float& m01 =0, const float& m11 =0, const float& m21 =0,
	          const float& m02 =0, const float& m12 =0, const float& m22 =0);

	// Access operators
	const Vector3& operator[](size_t column) const;
	Vector3& operator[](size_t column);

	// Arithmetic operators
	Matrix3x3 operator+(const Matrix3x3& m)  const;
	Matrix3x3 operator-(const Matrix3x3& m)  const;
	Matrix3x3 operator+()                    const;
	Matrix3x3 operator-()                    const;
	Matrix3x3 operator*(const Matrix3x3& m)  const;
	Vector3   operator*(const Vector3& v)    const;

	// Assignment operators
	Matrix3x3& operator+=(const Matrix3x3& m);
	Matrix3x3& operator-=(const Matrix3x3& m);
	Matrix3x3& operator*=(const Matrix3x3& m);

	// Comparison operators
	bool operator==(const Matrix3x3& m) const;
	bool operator!=(const Matrix3x3& m) const;

	// Queries
	bool IsInvertible()   const;
	float Determinant()   const;
	Matrix3x3 Inverse()   const;
	Matrix3x3 Transpose() const;
	Matrix3x3 Adjugate()  const;

	// Per component queries
	Matrix3x3 Sign()   const;
	Matrix3x3 Abs()    const;
	Matrix3x3 Sqr()    const;
	Matrix3x3 Sqrt()   const;
	Matrix3x3 Exp()    const;
	Matrix3x3 Log()    const;
	Matrix3x3 Log10()  const;
	Matrix3x3 Ceil()   const;
	Matrix3x3 Floor()  const;
	Matrix3x3 Frac()   const;

	// Constants
	static const Matrix3x3 IDENTITY;

private:
	// Members
	Vector3 mC0, mC1, mC2; // columns
};


////////////////////////////////////////////////////////////////////////////////
// Matrix4x4 definition
class Matrix4x4 {
public:
	// Factories
	static Matrix4x4 CompMult(const Matrix4x4& m1,
	                          const Matrix4x4& m2);
	static Matrix4x4 CompDiv(const Matrix4x4& m1,
	                         const Matrix4x4& m2);
	static Matrix4x4 CompPow(const Matrix4x4& base,
	                         const Matrix4x4& exponent);
	static Matrix4x4 CompMin(const Matrix4x4& m1,
	                         const Matrix4x4& m2);
	static Matrix4x4 CompMax(const Matrix4x4& m1,
	                         const Matrix4x4& m2);
	static Matrix4x4 CompClamp(const Matrix4x4& m,
	                           const Matrix4x4& min,
	                           const Matrix4x4& max);

	// Factories (continued)
	static Matrix4x4 OuterProduct(const Vector4& c,
	                              const Vector4& r);
	static Matrix4x4 Diagonal(const float& m00,
	                          const float& m11,
	                          const float& m22,
	                          const float& m33);
	static Matrix4x4 RotationAboutX(const float& radians);
	static Matrix4x4 RotationAboutY(const float& radians);
	static Matrix4x4 RotationAboutZ(const float& radians);
	static Matrix4x4 Rotation(const float& yaw,
	                          const float& pitch,
	                          const float& roll);
	static Matrix4x4 RotationAboutAxis(const Vector3& unitAxis,
	                                   const float& radians);
	static Matrix4x4 VectorRotation(const Vector3& unitFrom,
	                                const Vector3& unitTo);
	static Matrix4x4 LookAtRotation(const Vector3& eyePos,
	                                const Vector3& targetPos,
	                                const Vector3& unitUpVector);
	static Matrix4x4 Scale(const float& x,
	                       const float& y,
	                       const float& z);
	static Matrix4x4 Translation(const Vector3& direction);
	static Matrix4x4 LookAt(const Vector3& eyePos,
	                        const Vector3& targetPos,
	                        const Vector3& unitUpVector);

	// Factories (continued)
	static Matrix4x4 Ortho(const float& left,
	                       const float& right,
	                       const float& bottom,
	                       const float& top,
	                       const float& near,
	                       const float& far);
	static Matrix4x4 Frustum(const float& left,
	                         const float& right,
	                         const float& bottom,
	                         const float& top,
	                         const float& near,
	                         const float& far);
	static Matrix4x4 Perspective(const float& fovyRadians,
	                             const float& aspect,
	                             const float& near,
	                             const float& far);

	// Constructors
	Matrix4x4(const Vector4& c0,
	          const Vector4& c1,
	          const Vector4& c2,
	          const Vector4& c3);
	Matrix4x4(const float& m00 =0,
	          const float& m10 =0,
	          const float& m20 =0,
	          const float& m30 =0,
	          const float& m01 =0,
	          const float& m11 =0,
	          const float& m21 =0,
	          const float& m31 =0,
	          const float& m02 =0,
	          const float& m12 =0,
	          const float& m22 =0,
	          const float& m32 =0,
	          const float& m03 =0,
	          const float& m13 =0,
	          const float& m23 =0,
	          const float& m33 =0);

	// Access operators
	const Vector4& operator[](size_t column) const;
	Vector4& operator[](size_t column);

	// Arithmetic operators
	Matrix4x4 operator+(const Matrix4x4& m)  const;
	Matrix4x4 operator-(const Matrix4x4& m)  const;
	Matrix4x4 operator+()                    const;
	Matrix4x4 operator-()                    const;
	Matrix4x4 operator*(const Matrix4x4& m)  const;
	Vector4   operator*(const Vector4& v)    const;

	// Assignment operators
	Matrix4x4& operator+=(const Matrix4x4& m);
	Matrix4x4& operator-=(const Matrix4x4& m);
	Matrix4x4& operator*=(const Matrix4x4& m);

	// Comparison operators
	bool operator==(const Matrix4x4& m) const;
	bool operator!=(const Matrix4x4& m) const;

	// Queries
	bool IsInvertible()   const;
	float Determinant()   const;
	Matrix4x4 Inverse()   const;
	Matrix4x4 Transpose() const;
	Matrix4x4 Adjugate()  const;

	// Per component queries
	Matrix4x4 Sign()   const;
	Matrix4x4 Abs()    const;
	Matrix4x4 Sqr()    const;
	Matrix4x4 Sqrt()   const;
	Matrix4x4 Exp()    const;
	Matrix4x4 Log()    const;
	Matrix4x4 Log10()  const;
	Matrix4x4 Ceil()   const;
	Matrix4x4 Floor()  const;
	Matrix4x4 Frac()   const;

	// Constants
	static const Matrix4x4 IDENTITY;

private:
	// Hidden constructors
	explicit Matrix4x4(const Matrix3x3& m);

	// Members
	Vector4 mC0, mC1, mC2, mC3;
};


////////////////////////////////////////////////////////////////////////////////
// Additionnal operators
Vector2 operator*(const float& s, const Vector2& v);
Vector3 operator*(const float& s, const Vector3& v);
Vector4 operator*(const float& s, const Vector4& v);
Matrix2x2 operator*(const float& s, const Matrix2x2& m);
Matrix3x3 operator*(const float& s, const Matrix3x3& m);
Matrix4x4 operator*(const float& s, const Matrix4x4& m);

#endif

