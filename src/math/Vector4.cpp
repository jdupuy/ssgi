#include <cmath>
#include <algorithm>
#include <cassert>

#include "Algebra.hpp"

////////////////////////////////////////////////////////////////////////////////
// Constants
const Vector4 Vector4::ZERO(0.0f,0.0f,0.0f,0.0f);


////////////////////////////////////////////////////////////////////////////////
// Factories
Vector4 Vector4::CompMult(const Vector4& u,
                          const Vector4& v)
{ return Vector4(u[0]*v[0], u[1]*v[1], u[2]*v[2], u[3]*v[3]); }

Vector4 Vector4::CompDiv(const Vector4& u,
                         const Vector4& v)
{ return Vector4(u[0]/v[0], u[1]/v[1], u[2]/v[2], u[3]/v[3]); }

Vector4 Vector4::CompPow(const Vector4& base,
                         const Vector4& exponent)
{ return Vector4(std::pow(base[0],exponent[0]),
                 std::pow(base[1],exponent[1]),
                 std::pow(base[2],exponent[2]),
                 std::pow(base[3],exponent[3])); }

Vector4 Vector4::CompMin(const Vector4& u,
                         const Vector4& v)
{ return Vector4(std::min(u[0],v[0]),
                 std::min(u[1],v[1]),
                 std::min(u[2],v[2]),
                 std::min(u[3],v[3])); }

Vector4 Vector4::CompMax(const Vector4& u,
                         const Vector4& v)
{ return Vector4(std::max(u[0],v[0]),
                 std::max(u[1],v[1]),
                 std::max(u[2],v[2]),
                 std::max(u[3],v[3])); }

Vector4 Vector4::CompClamp(const Vector4& v,
                           const Vector4& min,
                           const Vector4& max)
{ return CompMin(CompMax(v, min), max); }


////////////////////////////////////////////////////////////////////////////////
// Constructor
Vector4::Vector4(const float& x,
                 const float& y,
                 const float& z,
                 const float& w) :
	mX(x), mY(y), mZ(z), mW(w)
{
}


////////////////////////////////////////////////////////////////////////////////
// Length
float Vector4::Length() const
{
	return std::sqrt(LengthSquared());
}


////////////////////////////////////////////////////////////////////////////////
// Length Squared
float Vector4::LengthSquared() const
{
	return mX*mX + mY*mY + mZ*mZ + mW*mW;
}


////////////////////////////////////////////////////////////////////////////////
// Normalize
Vector4 Vector4::Normalize() const
{
	float invLength = 1.0f/Length();
	return invLength*(*this);
}


////////////////////////////////////////////////////////////////////////////////
// Bracket operators
const float& Vector4::operator[](size_t row) const
{
#ifndef NDEBUG
	assert(row < 4);
#endif
	return (&mX)[row];
}

float& Vector4::operator[](size_t row)
{
	return const_cast< float& >((static_cast< const Vector4& >(*this))[row]);
}


////////////////////////////////////////////////////////////////////////////////
// Arithmetic operators
Vector4 Vector4::operator+(const Vector4& v) const
{return Vector4(mX+v.mX, mY+v.mY, mZ+v.mZ, mW+v.mW);}

Vector4 Vector4::operator-(const Vector4& v) const
{return Vector4(mX-v.mX, mY-v.mY, mZ-v.mZ, mW-v.mW);}

Vector4 Vector4::operator*(const float& s) const
{return Vector4(mX*s, mY*s, mZ*s, mW*s);}

Vector4 Vector4::operator/(const float& s) const
{
#ifndef NDEBUG
	assert(s != 0.0f);
#endif
	return (1.0f/s) * (*this);
}

Vector4 Vector4::operator+() const
{return Vector4(+mX, +mY, +mZ, +mW);}

Vector4 Vector4::operator-() const
{return Vector4(-mX, -mY, -mZ, -mW);}

////////////////////////////////////////////////////////////////////////////////
// Assignment operators
Vector4& Vector4::operator+=(const Vector4& v)
{mX+=v.mX; mY+=v.mY; mZ+=v.mZ; mW+=v.mW; return (*this);}

Vector4& Vector4::operator-=(const Vector4& v)
{mX-=v.mX; mY-=v.mY; mZ-=v.mZ; mW-=v.mW; return (*this);}

Vector4& Vector4::operator*=(const float& s)
{mX*=s; mY*=s; mZ*=s; mW*=s; return (*this);}

Vector4& Vector4::operator/=(const float& s)
{
#ifndef NDEBUG
	assert(s != 0.0f);
#endif
	float invS = 1.0f/s;
	mX *= invS;
	mY *= invS;
	mZ *= invS;
	mW *= invS;
	return (*this);
}

////////////////////////////////////////////////////////////////////////////////
// Comparison operators
bool Vector4::operator==(const Vector4& v) const
{ return (v.mX == mX && v.mY == mY && v.mZ == mZ && v.mW == mW); }

bool Vector4::operator!=(const Vector4& v) const
{ return !(v == *this); }


////////////////////////////////////////////////////////////////////////////////
// Additionnal operators
Vector4 operator*(const float& s, const Vector4& v)
{
	return Vector4(s*v[0], s*v[1], s*v[2], s*v[3]);
}


////////////////////////////////////////////////////////////////////////////////
// Per component queries
Vector4 Vector4::Sign() const
{ return Vector4(float((mX > 0) - (mX < 0)),
                 float((mY > 0) - (mY < 0)),
                 float((mZ > 0) - (mZ < 0)),
                 float((mW > 0) - (mW < 0))); }

Vector4 Vector4::Abs() const
{return Vector4(std::abs(mX), std::abs(mY), std::abs(mZ), std::abs(mW));}

Vector4 Vector4::Sqr() const
{return Vector4(mX*mX, mY*mY, mZ*mZ, mW*mW);}

Vector4 Vector4::Sqrt() const
{return Vector4(std::sqrt(mX), std::sqrt(mY), std::sqrt(mZ), std::sqrt(mW));}

Vector4 Vector4::Exp() const
{return Vector4(std::exp(mX), std::exp(mY), std::exp(mZ), std::exp(mW));}

Vector4 Vector4::Log() const
{return Vector4(std::log(mX), std::log(mY), std::log(mZ), std::log(mW));}

Vector4 Vector4::Log10() const
{return Vector4(std::log10(mX),
                std::log10(mY),
                std::log10(mZ),
                std::log10(mW));}

Vector4 Vector4::Ceil() const
{return Vector4(std::ceil(mX), std::ceil(mY), std::ceil(mZ), std::ceil(mW));}

Vector4 Vector4::Floor() const
{return Vector4(std::floor(mX),
                std::floor(mY),
                std::floor(mZ),
                std::floor(mW));}

Vector4 Vector4::Frac() const
{return (*this) - Floor();}


////////////////////////////////////////////////////////////////////////////////
// Dot product
float Vector4::DotProduct(const Vector4& u, const Vector4& v)
{
	return u[0]*v[0]+u[1]*v[1]+u[2]*v[2]+u[3]*v[3];
}


#if 0
#include <iostream>
int main(int argc, char** argv)
{
	Vector4 x = Vector4(1,8,0,8);
	std::cout << x.GetX() << " "
	          << x.GetY() << " "
	          << x.GetZ() << " "
	          << x.GetW() << std::endl;
	std::cout << x[0] << " " << x[1] << " " << x[2] << " " << x[3] << std::endl;
	x[0]+= 4;
	x[1] = 9 - x[1];
	x[2] -= x.GetY();
	x[3] = x.GetW()-1;
	std::cout << x[0] << " " << x[1] << " " << x[2] << " " << x[3] << std::endl;

	x = Vector4(-98,0,56,-0).Sign();
	std::cout << x[0] << " " << x[1] << " " << x[2] << " " << x[3] << std::endl;

	x = 2.0f*x;

	x /= 2.0f;
	std::cout << x[0] << " " << x[1] << " " << x[2] << " " << x[3] << std::endl;

	Vector4 a(1,0,0,1);
	a = a.Abs();
	a = a.Exp();
	a = -Vector4(1,0,0,0);
	Vector4 b(-1,0,0,0);
	b = -Vector4::CompMult(a,b);
	std::cout << Vector4::DotProduct(a.Normalize(),b) << std::endl;
	std::cout << a.Length() << " " << a.LengthSquared() << std::endl;
}
#endif

