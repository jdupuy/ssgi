#include <cassert>
#include <cmath>

#include "Algebra.hpp"

////////////////////////////////////////////////////////////////////////////////
// Constants
const Matrix3x3 Matrix3x3::IDENTITY(1,0,0,
                                    0,1,0,
                                    0,0,1);


////////////////////////////////////////////////////////////////////////////////
// Factories
Matrix3x3 Matrix3x3::CompMult(const Matrix3x3& m1,
                              const Matrix3x3& m2)
{
	return Matrix3x3(Vector3::CompMult(m1[0], m2[0]),
	                 Vector3::CompMult(m1[1], m2[1]),
	                 Vector3::CompMult(m1[2], m2[2]));
}

Matrix3x3 Matrix3x3::CompDiv(const Matrix3x3& m1,
                             const Matrix3x3& m2)
{
	return Matrix3x3(Vector3::CompDiv(m1[0], m2[0]),
	                 Vector3::CompDiv(m1[1], m2[1]),
	                 Vector3::CompDiv(m1[2], m2[2]));
}

Matrix3x3 Matrix3x3::CompPow(const Matrix3x3& base,
                             const Matrix3x3& exponent)
{
	return Matrix3x3(Vector3::CompPow(base[0], exponent[0]),
	                 Vector3::CompPow(base[1], exponent[1]),
	                 Vector3::CompPow(base[2], exponent[2]));
}

Matrix3x3 Matrix3x3::CompMin(const Matrix3x3& m1,
                             const Matrix3x3& m2)
{
	return Matrix3x3(Vector3::CompMin(m1[0], m2[0]),
	                 Vector3::CompMin(m1[1], m2[1]),
	                 Vector3::CompMin(m1[2], m2[2]));
}

Matrix3x3 Matrix3x3::CompMax(const Matrix3x3& m1,
                             const Matrix3x3& m2)
{
	return Matrix3x3(Vector3::CompMax(m1[0], m2[0]),
	                 Vector3::CompMax(m1[1], m2[1]),
	                 Vector3::CompMax(m1[2], m2[2]));
}

Matrix3x3 Matrix3x3::CompClamp(const Matrix3x3& m,
                               const Matrix3x3& min,
                               const Matrix3x3& max)
{
	return Matrix3x3(Vector3::CompClamp(m[0], min[0], max[0]),
	                 Vector3::CompClamp(m[1], min[1], max[1]),
	                 Vector3::CompClamp(m[2], min[2], max[2]));
}


////////////////////////////////////////////////////////////////////////////////
// Factories (continued)
Matrix3x3 Matrix3x3::OuterProduct(const Vector3& c,
                                  const Vector3& r)
{
	return Matrix3x3(r[0]*c, r[1]*c, r[2]*c);
}

Matrix3x3 Matrix3x3::Diagonal(const float& m00,
                              const float& m11,
                              const float& m22)
{
	return Matrix3x3(m00,  0 , 0 ,
	                  0 , m11, 0 ,
	                  0 ,  0 , m22);
}

Matrix3x3 Matrix3x3::RotationAboutX(const float& radians)
{
	// do some precomputations
	float c = std::cos(radians);
	float s = std::sin(radians);
	return Matrix3x3(1, 0,  0,
	                 0, c, -s,
	                 0, s,  c);
}

Matrix3x3 Matrix3x3::RotationAboutY(const float& radians)
{
	// do some precomputations
	float c = std::cos(radians);
	float s = std::sin(radians);
	return Matrix3x3( c, 0, s,
	                  0, 1, 0,
	                 -s, 0, c);
}

Matrix3x3 Matrix3x3::RotationAboutZ(const float& radians)
{
	// do some precomputations
	float c = std::cos(radians);
	float s = std::sin(radians);
	return Matrix3x3(c, -s, 0,
	                 s,  c, 0,
	                 0,  0, 1);
}

Matrix3x3 Matrix3x3::Rotation(const float& yaw,
                              const float& pitch,
                              const float& roll)
{
	return RotationAboutX(yaw) * RotationAboutY(pitch) * RotationAboutZ(roll);
}

Matrix3x3 Matrix3x3::RotationAboutAxis(const Vector3& unitAxis,
                                       const float& radians)
{
	// precompute stuff
	Vector3 axisSquared(Vector3::CompMult(unitAxis, unitAxis));
	float c = std::cos(radians);
	float s = std::sin(radians);
	float oneMinusC = 1.0f - c;
	float axay = unitAxis[0] * unitAxis[1];
	float axaz = unitAxis[0] * unitAxis[2];
	float ayaz = unitAxis[1] * unitAxis[2];

	return Matrix3x3( axisSquared[0] * oneMinusC + c,
	                  axay * oneMinusC - unitAxis[2] * s,
	                  axaz * oneMinusC + unitAxis[1] * s,
	                  axay * oneMinusC + unitAxis[2] * s,
	                  axisSquared[1] * oneMinusC + c,
	                  ayaz * oneMinusC - unitAxis[0] * s,
	                  axaz * oneMinusC - unitAxis[1] * s,
	                  ayaz * oneMinusC + unitAxis[0] * s,
	                  axisSquared[2] * oneMinusC + c );
}

Matrix3x3 Matrix3x3::VectorRotation(const Vector3& unitFrom,
                                    const Vector3& unitTo)
{
	// compute the unit rotation axis
	Vector3 v   = Vector3::CrossProduct(unitFrom, unitTo);
	float e     = Vector3::DotProduct(unitFrom, unitTo);
	float h     = 1.0f / (1.0f + e); 
	Vector3 hv  = h*v;

	// return the matrix
	return Matrix3x3(e + hv[0]*v[0], hv[0]*v[1] - v[2], hv[0]*v[2] + v[1],
	                 hv[0]*v[1] + v[2], e + hv[1]*v[1], hv[1]*v[2] - v[0],
	                 hv[0]*v[2] - v[1], hv[1]*v[2] + v[0], e + hv[2]*v[2]);
}

Matrix3x3 Matrix3x3::LookAtRotation(const Vector3& eyePos,
                                    const Vector3& targetPos,
                                    const Vector3& unitUpVector)
{
#ifndef NDEBUG
	assert(eyePos != targetPos && unitUpVector != Vector3::ZERO);
#endif
	// using OpenGL2.1 SDK (gluLookAt)
	Vector3 f((targetPos - eyePos).Normalize());
	Vector3 s(Vector3::CrossProduct(f, unitUpVector));
	Vector3 u(Vector3::CrossProduct(s, f));

	return Matrix3x3(s[0], u[0], -f[0],
	                 s[1], u[1], -f[1],
	                 s[2], u[2], -f[2] );
}

Matrix3x3 Matrix3x3::Scale(const float& x,
                           const float& y,
                           const float& z)
{
	return Diagonal(x, y, z);
}


////////////////////////////////////////////////////////////////////////////////
// Column Constructor
Matrix3x3::Matrix3x3(const Vector3& c0,
                     const Vector3& c1,
                     const Vector3& c2):
	mC0(c0), mC1(c1), mC2(c2)
{

}


////////////////////////////////////////////////////////////////////////////////
// Scalar Constructor
Matrix3x3::Matrix3x3(const float& m00, const float& m10, const float& m20,
                     const float& m01, const float& m11, const float& m21,
                     const float& m02, const float& m12, const float& m22):
	mC0(Vector3(m00,m01,m02)), 
	mC1(Vector3(m10,m11,m12)), 
	mC2(Vector3(m20,m21,m22))
{

}


////////////////////////////////////////////////////////////////////////////////
// Access operators
const Vector3& Matrix3x3::operator[](size_t column) const
{
#ifndef NDEBUG
	assert(column < 3);
#endif
	return (&mC0)[column];
}

Vector3& Matrix3x3::operator[](size_t column)
{
	return const_cast< Vector3& >
	       ((static_cast< const Matrix3x3& >(*this))[column]);
}


////////////////////////////////////////////////////////////////////////////////
// Arithmetic operators
Matrix3x3 Matrix3x3::operator+(const Matrix3x3& m) const
{ return Matrix3x3(mC0+m.mC0, mC1+m.mC1, mC2+m.mC2); }

Matrix3x3 Matrix3x3::operator-(const Matrix3x3& m) const
{ return Matrix3x3(mC0-m.mC0, mC1-m.mC1, mC2-m.mC2); }

Matrix3x3 Matrix3x3::operator+() const
{ return (*this); }

Matrix3x3 Matrix3x3::operator-() const
{ return Matrix3x3(-mC0, -mC1, -mC2); }

Matrix3x3 Matrix3x3::operator*(const Matrix3x3& m) const
{
	return Matrix3x3(  (*this)[0][0]*m[0][0]
	                 + (*this)[1][0]*m[0][1]
	                 + (*this)[2][0]*m[0][2],
	                   (*this)[0][0]*m[1][0]
	                 + (*this)[1][0]*m[1][1]
	                 + (*this)[2][0]*m[1][2],
	                   (*this)[0][0]*m[2][0]
	                 + (*this)[1][0]*m[2][1]
	                 + (*this)[2][0]*m[2][2],
	                   (*this)[0][1]*m[0][0]
	                 + (*this)[1][1]*m[0][1]
	                 + (*this)[2][1]*m[0][2],
	                   (*this)[0][1]*m[1][0]
	                 + (*this)[1][1]*m[1][1]
	                 + (*this)[2][1]*m[1][2],
	                   (*this)[0][1]*m[2][0]
	                 + (*this)[1][1]*m[2][1]
	                 + (*this)[2][1]*m[2][2],
	                   (*this)[0][2]*m[0][0]
	                 + (*this)[1][2]*m[0][1]
	                 + (*this)[2][2]*m[0][2],
	                   (*this)[0][2]*m[1][0]
	                 + (*this)[1][2]*m[1][1]
	                 + (*this)[2][2]*m[1][2],
	                   (*this)[0][2]*m[2][0]
	                 + (*this)[1][2]*m[2][1]
	                 + (*this)[2][2]*m[2][2] );
}

Vector3 Matrix3x3::operator*(const Vector3& v) const
{
	return Vector3((*this)[0][0]*v[0]+(*this)[1][0]*v[1]+(*this)[2][0]*v[2],
	               (*this)[0][1]*v[0]+(*this)[1][1]*v[1]+(*this)[2][1]*v[2],
	               (*this)[0][2]*v[0]+(*this)[1][2]*v[1]+(*this)[2][2]*v[2]);
}


////////////////////////////////////////////////////////////////////////////////
// Assignment operators
Matrix3x3& Matrix3x3::operator+=(const Matrix3x3& m)
{
	mC0 += m.mC0;
	mC1 += m.mC1;
	mC2 += m.mC2;
	return (*this);
}

Matrix3x3& Matrix3x3::operator-=(const Matrix3x3& m)
{
	mC0 -= m.mC0;
	mC1 -= m.mC1;
	mC2 -= m.mC2;
	return (*this);
}

Matrix3x3& Matrix3x3::operator*=(const Matrix3x3& m)
{
	return ((*this) = (*this) * m);
}


////////////////////////////////////////////////////////////////////////////////
// Comparison operators
bool Matrix3x3::operator==(const Matrix3x3& m) const
{ return !((*this) != m); }

bool Matrix3x3::operator!=(const Matrix3x3& m) const
{ return (mC0 != m.mC0 || mC1 != m.mC1 || mC2 != m.mC2); }


////////////////////////////////////////////////////////////////////////////////
// Is Invertible ?
bool Matrix3x3::IsInvertible() const
{
	return (Determinant() != 0.0f);
}


////////////////////////////////////////////////////////////////////////////////
// Determinant
float Matrix3x3::Determinant() const
{
	return (  (*this)[0][0]*( (*this)[1][1]*(*this)[2][2]
	                         -(*this)[2][1]*(*this)[1][2] )
	        - (*this)[1][0]*( (*this)[2][1]*(*this)[0][2]
	                         -(*this)[0][1]*(*this)[2][2] )
	        + (*this)[2][0]*( (*this)[0][1]*(*this)[1][2]
	                         -(*this)[1][1]*(*this)[0][2] ) );
}


////////////////////////////////////////////////////////////////////////////////
// Inverse
Matrix3x3 Matrix3x3::Inverse() const
{
#ifndef NDEBUG
	assert(IsInvertible());
#endif
	return 1.0f/Determinant() * Adjugate();
}


////////////////////////////////////////////////////////////////////////////////
// Transpose
Matrix3x3 Matrix3x3::Transpose() const
{
	return Matrix3x3((*this)[0][0], (*this)[0][1], (*this)[0][2],
	                 (*this)[1][0], (*this)[1][1], (*this)[1][2],
	                 (*this)[2][0], (*this)[2][1], (*this)[2][2] );
}


////////////////////////////////////////////////////////////////////////////////
// Adjugate
Matrix3x3 Matrix3x3::Adjugate() const
{
	// compute cofactors
	float c00 = (*this)[1][1] * (*this)[2][2] - (*this)[1][2] * (*this)[2][1];
	float c10 = (*this)[0][2] * (*this)[2][2] - (*this)[0][1] * (*this)[2][2];
	float c20 = (*this)[0][1] * (*this)[1][2] - (*this)[1][1] * (*this)[0][2];
	float c01 = (*this)[1][2] * (*this)[2][0] - (*this)[1][0] * (*this)[2][2];
	float c11 = (*this)[0][0] * (*this)[2][2] - (*this)[0][2] * (*this)[2][0];
	float c21 = (*this)[1][0] * (*this)[0][2] - (*this)[0][0] * (*this)[1][2];
	float c02 = (*this)[1][0] * (*this)[2][1] - (*this)[1][1] * (*this)[2][0];
	float c12 = (*this)[2][0] * (*this)[0][1] - (*this)[0][0] * (*this)[2][1];
	float c22 = (*this)[0][0] * (*this)[1][1] - (*this)[0][1] * (*this)[1][0];

	// return transpose of cofactors
	return Matrix3x3(c00, c01, c02,
	                 c10, c11, c12, 
	                 c20, c21, c22);
}


////////////////////////////////////////////////////////////////////////////////
// Queries
Matrix3x3 Matrix3x3::Sign() const
{ return Matrix3x3(mC0.Sign(),
                   mC1.Sign(),
                   mC2.Sign()); }

Matrix3x3 Matrix3x3::Abs() const
{ return Matrix3x3(mC0.Abs(),
                   mC1.Abs(),
                   mC2.Abs()); }

Matrix3x3 Matrix3x3::Sqr() const
{ return Matrix3x3(mC0.Sqr(),
                   mC1.Sqr(),
                   mC2.Sqr()); }

Matrix3x3 Matrix3x3::Sqrt() const
{ return Matrix3x3(mC0.Sqrt(),
                   mC1.Sqrt(),
                   mC2.Sqrt()); }

Matrix3x3 Matrix3x3::Exp() const
{ return Matrix3x3(mC0.Exp(),
                   mC1.Exp(),
                   mC2.Exp()); }

Matrix3x3 Matrix3x3::Log() const
{ return Matrix3x3(mC0.Log(),
                   mC1.Log(),
                   mC2.Log()); }

Matrix3x3 Matrix3x3::Log10() const
{ return Matrix3x3(mC0.Log10(),
                   mC1.Log10(),
                   mC2.Log10()); }

Matrix3x3 Matrix3x3::Ceil() const
{ return Matrix3x3(mC0.Ceil(),
                   mC1.Ceil(),
                   mC2.Ceil()); }

Matrix3x3 Matrix3x3::Floor() const
{ return Matrix3x3(mC0.Floor(),
                   mC1.Floor(),
                   mC2.Floor()); }

Matrix3x3 Matrix3x3::Frac() const
{ return Matrix3x3(mC0.Frac(),
                   mC1.Frac(),
                   mC2.Frac()); }


////////////////////////////////////////////////////////////////////////////////
// Additionnal operators
Matrix3x3 operator*(const float& s, const Matrix3x3& m)
{
	return Matrix3x3(s*m[0], s*m[1], s*m[2]);
}


#if 0

int main(int argc, char **argv)
{
	Matrix3x3 m = Matrix3x3::IDENTITY;

}
#endif

