#include <cassert>
#include <cmath>

#include "Algebra.hpp"

////////////////////////////////////////////////////////////////////////////////
// Constants
const Matrix2x2 Matrix2x2::IDENTITY(1,0,
                                    0,1);


////////////////////////////////////////////////////////////////////////////////
// Factories
Matrix2x2 Matrix2x2::CompMult(const Matrix2x2& m1,
                              const Matrix2x2& m2)
{
	return Matrix2x2(Vector2::CompMult(m1[0], m2[0]),
	                 Vector2::CompMult(m1[1], m2[1]));
}

Matrix2x2 Matrix2x2::CompDiv(const Matrix2x2& m1,
                             const Matrix2x2& m2)
{
	return Matrix2x2(Vector2::CompDiv(m1[0], m2[0]),
	                 Vector2::CompDiv(m1[1], m2[1]));
}

Matrix2x2 Matrix2x2::CompPow(const Matrix2x2& base,
                             const Matrix2x2& exponent)
{
	return Matrix2x2(Vector2::CompPow(base[0], exponent[0]),
	                 Vector2::CompPow(base[1], exponent[1]));
}

Matrix2x2 Matrix2x2::CompMin(const Matrix2x2& m1,
                             const Matrix2x2& m2)
{
	return Matrix2x2(Vector2::CompMin(m1[0], m2[0]),
	                 Vector2::CompMin(m1[1], m2[1]));
}

Matrix2x2 Matrix2x2::CompMax(const Matrix2x2& m1,
                             const Matrix2x2& m2)
{
	return Matrix2x2(Vector2::CompMax(m1[0], m2[0]),
	                 Vector2::CompMax(m1[1], m2[1]));
}

Matrix2x2 Matrix2x2::CompClamp(const Matrix2x2& m,
                               const Matrix2x2& min,
                               const Matrix2x2& max)
{
	return Matrix2x2(Vector2::CompClamp(m[0], min[0], max[0]),
	                 Vector2::CompClamp(m[1], min[1], max[1]));
}


////////////////////////////////////////////////////////////////////////////////
// Factories (continued)
Matrix2x2 Matrix2x2::OuterProduct(const Vector2& c,
                                  const Vector2& r)
{
	return Matrix2x2(r[0]*c, r[1]*c);
}

Matrix2x2 Matrix2x2::Diagonal(const float& m00, const float& m11)
{
	return Matrix2x2(m00,  0,
	                  0 , m11);
}

Matrix2x2 Matrix2x2::Rotation(const float& radians)
{
	// do some precomputations
	float c = std::cos(radians);
	float s = std::sin(radians);
	return Matrix2x2( c, -s,
	                  s,  c);
}

Matrix2x2 Matrix2x2::Scale(const float& x,
                           const float& y)
{
	return Diagonal(x, y);
}


////////////////////////////////////////////////////////////////////////////////
// Column Constructor
Matrix2x2::Matrix2x2(const Vector2& c0,
                     const Vector2& c1):
	mC0(c0), mC1(c1)
{

}


////////////////////////////////////////////////////////////////////////////////
// Scalar Constructor
Matrix2x2::Matrix2x2(const float& m00, const float& m10,
                     const float& m01, const float& m11):
	mC0(Vector2(m00,m01)),
	mC1(Vector2(m10,m11))
{

}


////////////////////////////////////////////////////////////////////////////////
// Access operators
const Vector2& Matrix2x2::operator[](size_t column) const
{
#ifndef NDEBUG
	assert(column < 2);
#endif
	return (&mC0)[column];
}

Vector2& Matrix2x2::operator[](size_t column)
{
	return const_cast< Vector2& >
	       ((static_cast< const Matrix2x2& >(*this))[column]);
}


////////////////////////////////////////////////////////////////////////////////
// Arithmetic operators
Matrix2x2 Matrix2x2::operator+(const Matrix2x2& m) const
{ return Matrix2x2(mC0+m.mC0, mC1+m.mC1); }

Matrix2x2 Matrix2x2::operator-(const Matrix2x2& m) const
{ return Matrix2x2(mC0-m.mC0, mC1-m.mC1); }

Matrix2x2 Matrix2x2::operator+() const
{ return (*this); }

Matrix2x2 Matrix2x2::operator-() const
{ return Matrix2x2(-mC0, -mC1); }

Matrix2x2 Matrix2x2::operator*(const Matrix2x2& m) const
{
	return Matrix2x2(  (*this)[0][0]*m[0][0]
	                 + (*this)[1][0]*m[0][1],
	                   (*this)[0][0]*m[1][0]
	                 + (*this)[1][0]*m[1][1],
	                   (*this)[0][1]*m[0][0]
	                 + (*this)[1][1]*m[0][1],
	                   (*this)[0][1]*m[1][0]
	                 + (*this)[1][1]*m[1][1]);
}

Vector2 Matrix2x2::operator*(const Vector2& v) const
{
	return Vector2((*this)[0][0]*v[0]+(*this)[1][0]*v[1],
	               (*this)[0][1]*v[0]+(*this)[1][1]*v[1]);
}


////////////////////////////////////////////////////////////////////////////////
// Assignment operators
Matrix2x2& Matrix2x2::operator+=(const Matrix2x2& m)
{
	mC0 += m.mC0;
	mC1 += m.mC1;
	return (*this);
}

Matrix2x2& Matrix2x2::operator-=(const Matrix2x2& m)
{
	mC0 -= m.mC0;
	mC1 -= m.mC1;
	return (*this);
}

Matrix2x2& Matrix2x2::operator*=(const Matrix2x2& m)
{
	return (*this) = (*this) * m;
}


////////////////////////////////////////////////////////////////////////////////
// Comparison operators
bool Matrix2x2::operator==(const Matrix2x2& m) const
{ return !((*this) != m); }

bool Matrix2x2::operator!=(const Matrix2x2& m) const
{ return (mC0 != m.mC0 || mC1 != m.mC1); }


////////////////////////////////////////////////////////////////////////////////
// Is Invertible ?
bool Matrix2x2::IsInvertible() const
{
	return (Determinant() != 0.0f);
}


////////////////////////////////////////////////////////////////////////////////
// Determinant
float Matrix2x2::Determinant() const
{
	return ( (*this)[0][0]*(*this)[1][1] - (*this)[1][0]*(*this)[0][1] );
}


////////////////////////////////////////////////////////////////////////////////
// Inverse
Matrix2x2 Matrix2x2::Inverse() const
{
#ifndef NDEBUG
	assert(IsInvertible());
#endif
	return 1.0f/Determinant() * Adjugate();
}


////////////////////////////////////////////////////////////////////////////////
// Transpose
Matrix2x2 Matrix2x2::Transpose() const
{
	return Matrix2x2( (*this)[0][0], (*this)[0][1],
	                  (*this)[1][0], (*this)[1][1] );
}


////////////////////////////////////////////////////////////////////////////////
// Adjugate
Matrix2x2 Matrix2x2::Adjugate() const
{
	// return transpose of cofactors
	return Matrix2x2( (*this)[1][1], -(*this)[0][1],
	                 -(*this)[1][0],  (*this)[0][0]);
}


////////////////////////////////////////////////////////////////////////////////
// Queries
Matrix2x2 Matrix2x2::Sign() const
{ return Matrix2x2(mC0.Sign(),
                   mC1.Sign()); }

Matrix2x2 Matrix2x2::Abs() const
{ return Matrix2x2(mC0.Abs(),
                   mC1.Abs()); }

Matrix2x2 Matrix2x2::Sqr() const
{ return Matrix2x2(mC0.Sqr(),
                   mC1.Sqr()); }

Matrix2x2 Matrix2x2::Sqrt() const
{ return Matrix2x2(mC0.Sqrt(),
                   mC1.Sqrt()); }

Matrix2x2 Matrix2x2::Exp() const
{ return Matrix2x2(mC0.Exp(),
                   mC1.Exp()); }

Matrix2x2 Matrix2x2::Log() const
{ return Matrix2x2(mC0.Log(),
                   mC1.Log()); }

Matrix2x2 Matrix2x2::Log10() const
{ return Matrix2x2(mC0.Log10(),
                   mC1.Log10()); }

Matrix2x2 Matrix2x2::Ceil() const
{ return Matrix2x2(mC0.Ceil(),
                   mC1.Ceil()); }

Matrix2x2 Matrix2x2::Floor() const
{ return Matrix2x2(mC0.Floor(),
                   mC1.Floor()); }

Matrix2x2 Matrix2x2::Frac() const
{ return Matrix2x2(mC0.Frac(),
                   mC1.Frac()); }


////////////////////////////////////////////////////////////////////////////////
// Additionnal operators
Matrix2x2 operator*(const float& s, const Matrix2x2& m)
{
	return Matrix2x2(s*m[0], s*m[1]);
}


#if 0

int main(int argc, char **argv)
{
	Matrix2x2 m = Matrix2x2::IDENTITY;

}
#endif

