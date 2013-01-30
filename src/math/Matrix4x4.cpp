#include <cassert>
#include <cmath>

#include "Algebra.hpp"

////////////////////////////////////////////////////////////////////////////////
// Constants
const Matrix4x4 Matrix4x4::IDENTITY(1,0,0,0,
                                    0,1,0,0,
                                    0,0,1,0,
                                    0,0,0,1);


////////////////////////////////////////////////////////////////////////////////
// Factories
Matrix4x4 Matrix4x4::CompMult(const Matrix4x4& m1,
                              const Matrix4x4& m2)
{
	return Matrix4x4(Vector4::CompMult(m1[0], m2[0]),
	                 Vector4::CompMult(m1[1], m2[1]),
	                 Vector4::CompMult(m1[2], m2[2]),
	                 Vector4::CompMult(m1[3], m2[3]));
}

Matrix4x4 Matrix4x4::CompDiv(const Matrix4x4& m1,
                             const Matrix4x4& m2)
{
	return Matrix4x4(Vector4::CompDiv(m1[0], m2[0]),
	                 Vector4::CompDiv(m1[1], m2[1]),
	                 Vector4::CompDiv(m1[2], m2[2]),
	                 Vector4::CompDiv(m1[3], m2[3]));
}

Matrix4x4 Matrix4x4::CompPow(const Matrix4x4& base,
                             const Matrix4x4& exponent)
{
	return Matrix4x4(Vector4::CompPow(base[0], exponent[0]),
	                 Vector4::CompPow(base[1], exponent[1]),
	                 Vector4::CompPow(base[2], exponent[2]),
	                 Vector4::CompPow(base[3], exponent[3]));
}

Matrix4x4 Matrix4x4::CompMin(const Matrix4x4& m1,
                             const Matrix4x4& m2)
{
	return Matrix4x4(Vector4::CompMin(m1[0], m2[0]),
	                 Vector4::CompMin(m1[1], m2[1]),
	                 Vector4::CompMin(m1[2], m2[2]),
	                 Vector4::CompMin(m1[3], m2[3]));
}

Matrix4x4 Matrix4x4::CompMax(const Matrix4x4& m1,
                             const Matrix4x4& m2)
{
	return Matrix4x4(Vector4::CompMax(m1[0], m2[0]),
	                 Vector4::CompMax(m1[1], m2[1]),
	                 Vector4::CompMax(m1[2], m2[2]),
	                 Vector4::CompMax(m1[3], m2[3]));
}

Matrix4x4 Matrix4x4::CompClamp(const Matrix4x4& m,
                               const Matrix4x4& min,
                               const Matrix4x4& max)
{
	return Matrix4x4(Vector4::CompClamp(m[0], min[0], max[0]),
	                 Vector4::CompClamp(m[1], min[1], max[1]),
	                 Vector4::CompClamp(m[2], min[2], max[2]),
	                 Vector4::CompClamp(m[3], min[3], max[3]));
}


////////////////////////////////////////////////////////////////////////////////
// Factories (continued)
Matrix4x4 Matrix4x4::OuterProduct(const Vector4& c,
                                  const Vector4& r)
{
	return Matrix4x4(r[0]*c, r[1]*c, r[2]*c, r[3]*c);
}

Matrix4x4 Matrix4x4::Diagonal(const float& m00,
                              const float& m11,
                              const float& m22,
                              const float& m33)
{
	return Matrix4x4(m00,  0 , 0 ,   0 ,
	                  0 , m11, 0 ,   0 ,
	                  0 ,  0 , m22,  0 ,
	                  0 ,  0 ,  0 , m33);
}

Matrix4x4 Matrix4x4::RotationAboutX(const float& radians)
{
	// do some precomputations
	float c = std::cos(radians);
	float s = std::sin(radians);
	return Matrix4x4(1,  0,  0,  0 ,
	                 0,  c, -s,  0 ,
	                 0,  s,  c,  0 ,
	                 0,  0,  0,  1);
}

Matrix4x4 Matrix4x4::RotationAboutY(const float& radians)
{
	// do some precomputations
	float c = std::cos(radians);
	float s = std::sin(radians);
	return Matrix4x4( c, 0, s, 0,
	                  0, 1, 0, 0,
	                 -s, 0, c, 0,
	                  0, 0, 0, 1);
}

Matrix4x4 Matrix4x4::RotationAboutZ(const float& radians)
{
	// do some precomputations
	float c = std::cos(radians);
	float s = std::sin(radians);
	return Matrix4x4(c, -s, 0, 0,
	                 s,  c, 0, 0,
	                 0,  0, 1, 0,
	                 0,  0, 0, 1);
}

Matrix4x4 Matrix4x4::Rotation(const float& yaw,
                              const float& pitch,
                              const float& roll)
{
	// save a few computations by using Matrix3x3
	Matrix3x3 r  = Matrix3x3::RotationAboutX(yaw);
	          r *= Matrix3x3::RotationAboutY(pitch);
	          r *= Matrix3x3::RotationAboutZ(roll);

	return Matrix4x4(r);
}

Matrix4x4 Matrix4x4::RotationAboutAxis(const Vector3& unitAxis,
                                       const float& radians)
{
	return Matrix4x4(Matrix3x3::RotationAboutAxis(unitAxis, radians));
}

Matrix4x4 Matrix4x4::VectorRotation(const Vector3& unitFrom,
                                    const Vector3& unitTo)
{
	return Matrix4x4(Matrix3x3::VectorRotation(unitFrom, unitTo));
}

Matrix4x4 Matrix4x4::LookAtRotation(const Vector3& eyePos,
	                                const Vector3& targetPos,
	                                const Vector3& unitUpVector)
{
	return Matrix4x4(Matrix3x3::LookAtRotation(eyePos,
	                                           targetPos,
	                                           unitUpVector));
}

Matrix4x4 Matrix4x4::Scale(const float& x,
                           const float& y,
                           const float& z)
{
	return Diagonal(x, y, z, 1);
}

Matrix4x4 Matrix4x4::Translation(const Vector3& direction)
{
	return Matrix4x4(1,0,0,direction[0],
	                 0,1,0,direction[1],
	                 0,0,1,direction[2],
	                 0,0,0,1);
}

Matrix4x4 Matrix4x4::LookAt(const Vector3& eyePos,
	                        const Vector3& targetPos,
	                        const Vector3& unitUpVector)
{
	// from OpenGL2.1 SDK (gluLookAt)
	return Matrix4x4(Matrix3x3::LookAtRotation(eyePos,
	                                           targetPos,
	                                           unitUpVector).Transpose())
	       * Translation(-eyePos);
}

////////////////////////////////////////////////////////////////////////////////
// Factories (continued)
Matrix4x4 Matrix4x4::Ortho(const float& left,
                           const float& right,
                           const float& bottom,
                           const float& top,
                           const float& near,
                           const float& far)
{
#ifndef NDEBUG
	assert(left != right && bottom != top && near != bottom);
#endif
	// do some precomputations
	float oneOverRightMinusLeft = 1.0f/(right - left);
	float oneOverTopMinusBottom = 1.0f/(top   - bottom);
	float oneOverFarMinusNear   = 1.0f/(far   - near);

	// from OpenGL2.1 SDK (glOrtho)
	return Matrix4x4(2.0f * oneOverRightMinusLeft,
	                 0,
	                 0,
	                 -(right + left) * oneOverRightMinusLeft,
	                 0,
	                 2.0f * oneOverTopMinusBottom,
	                 0,
	                 -(top + bottom) * oneOverTopMinusBottom,
	                 0,
	                 0,
	                 -2.0f * oneOverFarMinusNear,
	                 -(far + near) * oneOverFarMinusNear,
	                 0,0,0,1 );
}


Matrix4x4 Matrix4x4::Frustum(const float& left,
                             const float& right,
                             const float& bottom,
                             const float& top,
                             const float& near,
                             const float& far)
{
#ifndef NDEBUG
	assert(   left != right
	       && bottom != top
	       && near < far
	       && near > 0.0f);
#endif
	// do some precomputations
	float oneOverRightMinusLeft = 1.0f/(right - left);
	float oneOverTopMinusBottom = 1.0f/(top   - bottom);
	float oneOverFarMinusNear   = 1.0f/(far   - near);
	float twoNearVal            = 2.0f * near;

	// from OpenGL2.1 SDK (glFrustum)
	return Matrix4x4(twoNearVal * oneOverRightMinusLeft,
	                 0,
	                 (right + left) * oneOverRightMinusLeft,
	                 0,

	                 0,
	                 twoNearVal * oneOverTopMinusBottom,
	                 (top + bottom) * oneOverTopMinusBottom,
	                 0,

	                 0,
	                 0,
	                 -(far + near) * oneOverFarMinusNear,
	                 -(twoNearVal*far) * oneOverFarMinusNear,
	                 0,0,-1,0 );
}


Matrix4x4 Matrix4x4::Perspective(const float& fovyRadians,
                                 const float& aspect,
                                 const float& near,
                                 const float& far)
{
#ifndef NDEBUG
	assert(   fovyRadians > 0.0f
	       && aspect > 0.0f
	       && near < far
	       && near > 0.0f);
#endif
	// from OpenGL2.1 SDK (gluPerspective)
	float f = 1.0f/tan(fovyRadians*0.5f);
	float invNearMinusFar = 1.0f/(near-far);
	return Matrix4x4(f/aspect, 0, 0, 0,
	                 0 , f, 0, 0,
	                 0, 0, (far+near)*invNearMinusFar,
	                 2.0f*near*far*invNearMinusFar,
	                 0, 0, -1.0f, 0);

}


////////////////////////////////////////////////////////////////////////////////
// Column Constructor
Matrix4x4::Matrix4x4(const Vector4& c0,
                     const Vector4& c1,
                     const Vector4& c2,
                     const Vector4& c3):
	mC0(c0), mC1(c1), mC2(c2), mC3(c3)
{

}


////////////////////////////////////////////////////////////////////////////////
// Scalar Constructor
Matrix4x4::Matrix4x4(const float& m00,
                     const float& m10,
                     const float& m20,
                     const float& m30,
                     const float& m01,
                     const float& m11,
                     const float& m21,
                     const float& m31,
                     const float& m02,
                     const float& m12,
                     const float& m22,
                     const float& m32,
                     const float& m03,
                     const float& m13,
                     const float& m23,
                     const float& m33):
	mC0(Vector4(m00,m01,m02,m03)),
	mC1(Vector4(m10,m11,m12,m13)),
	mC2(Vector4(m20,m21,m22,m23)),
	mC3(Vector4(m30,m31,m32,m33))
{

}


////////////////////////////////////////////////////////////////////////////////
// Access operators
const Vector4& Matrix4x4::operator[](size_t column) const
{
#ifndef NDEBUG
	assert(column < 4);
#endif
	return (&mC0)[column];
}

Vector4& Matrix4x4::operator[](size_t column)
{
	return const_cast< Vector4& >
	       ((static_cast< const Matrix4x4& >(*this))[column]);
}


////////////////////////////////////////////////////////////////////////////////
// Arithmetic operators
Matrix4x4 Matrix4x4::operator+(const Matrix4x4& m) const
{ return Matrix4x4(mC0+m.mC0, mC1+m.mC1, mC2+m.mC2, mC3+m.mC3); }

Matrix4x4 Matrix4x4::operator-(const Matrix4x4& m) const
{ return Matrix4x4(mC0-m.mC0, mC1-m.mC1, mC2-m.mC2, mC3-m.mC3); }

Matrix4x4 Matrix4x4::operator+() const
{ return (*this); }

Matrix4x4 Matrix4x4::operator-() const
{ return Matrix4x4(-mC0, -mC1, -mC2, -mC3); }

Matrix4x4 Matrix4x4::operator*(const Matrix4x4& m) const
{
	return Matrix4x4(  (*this)[0][0]*m[0][0]+(*this)[1][0]*m[0][1]
	                  +(*this)[2][0]*m[0][2]+(*this)[3][0]*m[0][3],
	                   (*this)[0][0]*m[1][0]+(*this)[1][0]*m[1][1]
	                  +(*this)[2][0]*m[1][2]+(*this)[3][0]*m[1][3],
	                   (*this)[0][0]*m[2][0]+(*this)[1][0]*m[2][1]
	                  +(*this)[2][0]*m[2][2]+(*this)[3][0]*m[2][3],
	                   (*this)[0][0]*m[3][0]+(*this)[1][0]*m[3][1]
	                  +(*this)[2][0]*m[3][2]+(*this)[3][0]*m[3][3],
	                   (*this)[0][1]*m[0][0]+(*this)[1][1]*m[0][1]
	                  +(*this)[2][1]*m[0][2]+(*this)[3][1]*m[0][3],
	                   (*this)[0][1]*m[1][0]+(*this)[1][1]*m[1][1]
	                  +(*this)[2][1]*m[1][2]+(*this)[3][1]*m[1][3],
	                   (*this)[0][1]*m[2][0]+(*this)[1][1]*m[2][1]
	                  +(*this)[2][1]*m[2][2]+(*this)[3][1]*m[2][3],
	                   (*this)[0][1]*m[3][0]+(*this)[1][1]*m[3][1]
	                  +(*this)[2][1]*m[3][2]+(*this)[3][1]*m[3][3],
	                   (*this)[0][2]*m[0][0]+(*this)[1][2]*m[0][1]
	                  +(*this)[2][2]*m[0][2]+(*this)[3][2]*m[0][3],
	                   (*this)[0][2]*m[1][0]+(*this)[1][2]*m[1][1]
	                  +(*this)[2][2]*m[1][2]+(*this)[3][2]*m[1][3],
	                   (*this)[0][2]*m[2][0]+(*this)[1][2]*m[2][1]
	                  +(*this)[2][2]*m[2][2]+(*this)[3][2]*m[2][3],
	                   (*this)[0][2]*m[3][0]+(*this)[1][2]*m[3][1]
	                  +(*this)[2][2]*m[3][2]+(*this)[3][2]*m[3][3],
	                   (*this)[0][3]*m[0][0]+(*this)[1][3]*m[0][1]
	                  +(*this)[2][3]*m[0][2]+(*this)[3][3]*m[0][3],
	                   (*this)[0][3]*m[1][0]+(*this)[1][3]*m[1][1]
	                  +(*this)[2][3]*m[1][2]+(*this)[3][3]*m[1][3],
	                   (*this)[0][3]*m[2][0]+(*this)[1][3]*m[2][1]
	                  +(*this)[2][3]*m[2][2]+(*this)[3][3]*m[2][3],
	                   (*this)[0][3]*m[3][0]+(*this)[1][3]*m[2][1]
	                  +(*this)[2][3]*m[3][2]+(*this)[3][3]*m[3][3]  );
}

Vector4 Matrix4x4::operator*(const Vector4& v) const
{
	return Vector4(  (*this)[0][0]*v[0]+(*this)[1][0]*v[1]
	                +(*this)[2][0]*v[2]+(*this)[3][0]*v[3],
	                 (*this)[0][1]*v[0]+(*this)[1][1]*v[1]
	                +(*this)[2][1]*v[2]+(*this)[3][1]*v[3],
	                 (*this)[0][2]*v[0]+(*this)[1][2]*v[1]
	                +(*this)[2][2]*v[2]+(*this)[3][2]*v[3],
	                 (*this)[0][3]*v[0]+(*this)[1][3]*v[1]
	                +(*this)[2][3]*v[2]+(*this)[3][3]*v[3]  );
}


////////////////////////////////////////////////////////////////////////////////
// Assignment operators
Matrix4x4& Matrix4x4::operator+=(const Matrix4x4& m)
{
	mC0 += m.mC0;
	mC1 += m.mC1;
	mC2 += m.mC2;
	mC3 += m.mC3;
	return (*this);
}

Matrix4x4& Matrix4x4::operator-=(const Matrix4x4& m)
{
	mC0 -= m.mC0;
	mC1 -= m.mC1;
	mC2 -= m.mC2;
	mC3 -= m.mC3;
	return (*this);
}

Matrix4x4& Matrix4x4::operator*=(const Matrix4x4& m)
{
	return ((*this) = (*this) * m);
}


////////////////////////////////////////////////////////////////////////////////
// Comparison operators
bool Matrix4x4::operator==(const Matrix4x4& m) const
{ return !((*this) != m); }

bool Matrix4x4::operator!=(const Matrix4x4& m) const
{ return (mC0 != m.mC0 || mC1 != m.mC1 || mC2 != m.mC2 || mC3 != m.mC3); }


////////////////////////////////////////////////////////////////////////////////
// Is Invertible ?
bool Matrix4x4::IsInvertible() const
{
	return (Determinant() != 0.0f);
}


////////////////////////////////////////////////////////////////////////////////
// Determinant
float Matrix4x4::Determinant() const
{
	return (  ((*this)[0][0]*(*this)[1][1] - (*this)[1][0]*(*this)[0][1])
	         *((*this)[2][2]*(*this)[3][3] - (*this)[3][2]*(*this)[2][3])
	         -((*this)[0][0]*(*this)[2][1] - (*this)[2][0]*(*this)[1][0])
	         *((*this)[1][2]*(*this)[3][3] - (*this)[3][2]*(*this)[1][3])
	         +((*this)[0][0]*(*this)[3][1] - (*this)[3][0]*(*this)[0][1])
	         *((*this)[1][2]*(*this)[2][3] - (*this)[2][2]*(*this)[1][3])
	         +((*this)[1][0]*(*this)[2][1] - (*this)[2][0]*(*this)[1][1])
	         *((*this)[0][2]*(*this)[3][3] - (*this)[3][2]*(*this)[0][3])
	         -((*this)[1][0]*(*this)[3][1] - (*this)[3][0]*(*this)[1][1])
	         *((*this)[0][2]*(*this)[2][3] - (*this)[2][2]*(*this)[0][3])
	         +((*this)[2][0]*(*this)[3][1] - (*this)[3][0]*(*this)[2][1])
	         *((*this)[0][2]*(*this)[1][3] - (*this)[1][2]*(*this)[0][3])  );
}


////////////////////////////////////////////////////////////////////////////////
// Inverse
Matrix4x4 Matrix4x4::Inverse() const
{
#ifndef NDEBUG
	assert(IsInvertible());
#endif
	// use laplace expansion theorem
	float s0 = (*this)[0][0] * (*this)[1][1] - (*this)[1][0] * (*this)[0][1];
	float s1 = (*this)[0][0] * (*this)[2][1] - (*this)[2][0] * (*this)[0][1];
	float s2 = (*this)[0][0] * (*this)[3][1] - (*this)[3][0] * (*this)[0][1];
	float s3 = (*this)[1][0] * (*this)[2][1] - (*this)[2][0] * (*this)[1][1];
	float s4 = (*this)[1][0] * (*this)[3][1] - (*this)[3][0] * (*this)[1][1];
	float s5 = (*this)[2][0] * (*this)[3][1] - (*this)[3][0] * (*this)[2][1];

	float c5 = (*this)[2][2] * (*this)[3][3] - (*this)[3][2] * (*this)[2][3];
	float c4 = (*this)[1][2] * (*this)[3][3] - (*this)[3][2] * (*this)[1][3];
	float c3 = (*this)[1][2] * (*this)[2][3] - (*this)[2][2] * (*this)[1][3];
	float c2 = (*this)[0][2] * (*this)[3][3] - (*this)[3][2] * (*this)[0][3];
	float c1 = (*this)[0][2] * (*this)[2][3] - (*this)[2][2] * (*this)[0][3];
	float c0 = (*this)[0][2] * (*this)[1][3] - (*this)[1][2] * (*this)[0][3];

	// compute inverse of determinant
	float invDet = 1.0f/(s0*c5 -s1*c4 + s2*c3 + s3*c2 - s4*c1 + s5*c0);

	// return transpose of cofactors
	return
	invDet*Matrix4x4( + (*this)[1][1]*c5 - (*this)[2][1]*c4 + (*this)[3][1]*c3,
	                  - (*this)[1][0]*c5 + (*this)[2][0]*c4 - (*this)[3][0]*c3,
	                  + (*this)[1][3]*s5 - (*this)[2][3]*s4 + (*this)[3][3]*s3,
	                  - (*this)[1][2]*s5 + (*this)[2][2]*s4 - (*this)[3][2]*s3,

	                  - (*this)[0][1]*c5 + (*this)[2][1]*c2 - (*this)[3][1]*c1,
	                  + (*this)[0][0]*c5 - (*this)[2][0]*c2 + (*this)[3][0]*c1,
	                  - (*this)[0][3]*s5 + (*this)[2][3]*s2 - (*this)[3][3]*s1,
	                  + (*this)[0][2]*s5 - (*this)[2][2]*s2 + (*this)[3][2]*s1,

	                  + (*this)[0][1]*c4 - (*this)[1][1]*c2 + (*this)[3][1]*c0,
	                  - (*this)[0][0]*c4 + (*this)[1][0]*c2 - (*this)[3][0]*c0,
	                  + (*this)[0][3]*s4 - (*this)[1][3]*s2 + (*this)[3][3]*s0,
	                  - (*this)[0][2]*s4 + (*this)[1][2]*s2 - (*this)[3][2]*s0,

	                  - (*this)[0][1]*c3 + (*this)[1][1]*c1 - (*this)[2][1]*c0,
	                  + (*this)[0][0]*c3 - (*this)[1][0]*c1 + (*this)[2][0]*c0,
	                  - (*this)[0][3]*s3 + (*this)[1][3]*s1 - (*this)[2][3]*s0,
	                  + (*this)[0][2]*s3 - (*this)[1][2]*s1 + (*this)[2][2]*s0);
}


////////////////////////////////////////////////////////////////////////////////
// Transpose
Matrix4x4 Matrix4x4::Transpose() const
{
	return Matrix4x4((*this)[0][0], (*this)[0][1], (*this)[0][2], (*this)[0][3],
	                 (*this)[1][0], (*this)[1][1], (*this)[1][2], (*this)[1][3],
	                 (*this)[2][0], (*this)[2][1], (*this)[2][2], (*this)[2][3],
	                 (*this)[3][0], (*this)[3][1], (*this)[3][2], (*this)[3][3]
	                );
}


////////////////////////////////////////////////////////////////////////////////
// Adjugate
Matrix4x4 Matrix4x4::Adjugate() const
{
	// use laplace expansion theorem
	float s0 = (*this)[0][0] * (*this)[1][1] - (*this)[1][0] * (*this)[0][1];
	float s1 = (*this)[0][0] * (*this)[2][1] - (*this)[2][0] * (*this)[0][1];
	float s2 = (*this)[0][0] * (*this)[3][1] - (*this)[3][0] * (*this)[0][1];
	float s3 = (*this)[1][0] * (*this)[2][1] - (*this)[2][0] * (*this)[1][1];
	float s4 = (*this)[1][0] * (*this)[3][1] - (*this)[3][0] * (*this)[1][1];
	float s5 = (*this)[2][0] * (*this)[3][1] - (*this)[3][0] * (*this)[2][1];

	float c5 = (*this)[2][2] * (*this)[3][3] - (*this)[3][2] * (*this)[2][3];
	float c4 = (*this)[1][2] * (*this)[3][3] - (*this)[3][2] * (*this)[1][3];
	float c3 = (*this)[1][2] * (*this)[2][3] - (*this)[2][2] * (*this)[1][3];
	float c2 = (*this)[0][2] * (*this)[3][3] - (*this)[3][2] * (*this)[0][3];
	float c1 = (*this)[0][2] * (*this)[2][3] - (*this)[2][2] * (*this)[0][3];
	float c0 = (*this)[0][2] * (*this)[1][3] - (*this)[1][2] * (*this)[0][3];

	// return transpose of cofactors
	return Matrix4x4( + (*this)[1][1]*c5 - (*this)[2][1]*c4 + (*this)[3][1]*c3,
	                  - (*this)[1][0]*c5 + (*this)[2][0]*c4 - (*this)[3][0]*c3,
	                  + (*this)[1][3]*s5 - (*this)[2][3]*s4 + (*this)[3][3]*s3,
	                  - (*this)[1][2]*s5 + (*this)[2][2]*s4 - (*this)[3][2]*s3,

	                  - (*this)[0][1]*c5 + (*this)[2][1]*c2 - (*this)[3][1]*c1,
	                  + (*this)[0][0]*c5 - (*this)[2][0]*c2 + (*this)[3][0]*c1,
	                  - (*this)[0][3]*s5 + (*this)[2][3]*s2 - (*this)[3][3]*s1,
	                  + (*this)[0][2]*s5 - (*this)[2][2]*s2 + (*this)[3][2]*s1,

	                  + (*this)[0][1]*c4 - (*this)[1][1]*c2 + (*this)[3][1]*c0,
	                  - (*this)[0][0]*c4 + (*this)[1][0]*c2 - (*this)[3][0]*c0,
	                  + (*this)[0][3]*s4 - (*this)[1][3]*s2 + (*this)[3][3]*s0,
	                  - (*this)[0][2]*s4 + (*this)[1][2]*s2 - (*this)[3][2]*s0,

	                  - (*this)[0][1]*c3 + (*this)[1][1]*c1 - (*this)[2][1]*c0,
	                  + (*this)[0][0]*c3 - (*this)[1][0]*c1 + (*this)[2][0]*c0,
	                  - (*this)[0][3]*s3 + (*this)[1][3]*s1 - (*this)[2][3]*s0,
	                  + (*this)[0][2]*s3 - (*this)[1][2]*s1 + (*this)[2][2]*s0);
}


////////////////////////////////////////////////////////////////////////////////
// Queries
Matrix4x4 Matrix4x4::Sign() const
{ return Matrix4x4(mC0.Sign(),
                   mC1.Sign(),
                   mC2.Sign(),
                   mC3.Sign()); }

Matrix4x4 Matrix4x4::Abs() const
{ return Matrix4x4(mC0.Abs(),
                   mC1.Abs(),
                   mC2.Abs(),
                   mC3.Abs()); }

Matrix4x4 Matrix4x4::Sqr() const
{ return Matrix4x4(mC0.Sqr(),
                   mC1.Sqr(),
                   mC2.Sqr(),
                   mC3.Sqr()); }

Matrix4x4 Matrix4x4::Sqrt() const
{ return Matrix4x4(mC0.Sqrt(),
                   mC1.Sqrt(),
                   mC2.Sqrt(),
                   mC3.Sqrt()); }

Matrix4x4 Matrix4x4::Exp() const
{ return Matrix4x4(mC0.Exp(),
                   mC1.Exp(),
                   mC2.Exp(),
                   mC3.Exp()); }

Matrix4x4 Matrix4x4::Log() const
{ return Matrix4x4(mC0.Log(),
                   mC1.Log(),
                   mC2.Log(),
                   mC3.Log()); }

Matrix4x4 Matrix4x4::Log10() const
{ return Matrix4x4(mC0.Log10(),
                   mC1.Log10(),
                   mC2.Log10(),
                   mC3.Log10()); }

Matrix4x4 Matrix4x4::Ceil() const
{ return Matrix4x4(mC0.Ceil(),
                   mC1.Ceil(),
                   mC2.Ceil(),
                   mC3.Ceil()); }

Matrix4x4 Matrix4x4::Floor() const
{ return Matrix4x4(mC0.Floor(),
                   mC1.Floor(),
                   mC2.Floor(),
                   mC3.Floor()); }

Matrix4x4 Matrix4x4::Frac() const
{ return Matrix4x4(mC0.Frac(),
                   mC1.Frac(),
                   mC2.Frac(),
                   mC3.Frac()); }

////////////////////////////////////////////////////////////////////////////////
// Mat3 construtor
Matrix4x4::Matrix4x4(const Matrix3x3& m) : 
mC0(m[0][0], m[0][1], m[0][2], 0),
mC1(m[1][0], m[1][1], m[1][2], 0),
mC2(m[2][0], m[2][1], m[2][2], 0),
mC3(   0   ,    0   ,    0   , 1)
{
}


////////////////////////////////////////////////////////////////////////////////
// Additionnal operators
Matrix4x4 operator*(const float& s, const Matrix4x4& m)
{
	return Matrix4x4(s*m[0], s*m[1], s*m[2], s*m[3]);
}


#if 0

int main(int argc, char **argv)
{
	Matrix4x4 m = Matrix4x4::IDENTITY;

}
#endif

