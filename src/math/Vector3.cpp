#include <cmath>
#include <algorithm>
#include <cassert>

#include "Algebra.hpp"

////////////////////////////////////////////////////////////////////////////////
// Constants
const Vector3 Vector3::ZERO(0.0f,0.0f,0.0f);


////////////////////////////////////////////////////////////////////////////////
// Factories
Vector3 Vector3::CompMult(const Vector3& u,
                          const Vector3& v)
{ return Vector3(u[0]*v[0], u[1]*v[1], u[2]*v[2]); }

Vector3 Vector3::CompDiv(const Vector3& u,
                         const Vector3& v)
{ return Vector3(u[0]/v[0], u[1]/v[1], u[2]/v[2]); }

Vector3 Vector3::CompPow(const Vector3& base,
                         const Vector3& exponent)
{ return Vector3(std::pow(base[0],exponent[0]),
                 std::pow(base[1],exponent[1]),
                 std::pow(base[2],exponent[2])); }

Vector3 Vector3::CompMin(const Vector3& u,
                         const Vector3& v)
{ return Vector3(std::min(u[0],v[0]),
                 std::min(u[1],v[1]),
                 std::min(u[2],v[2])); }

Vector3 Vector3::CompMax(const Vector3& u,
                         const Vector3& v)
{ return Vector3(std::max(u[0],v[0]),
                 std::max(u[1],v[1]),
                 std::max(u[2],v[2])); }

Vector3 Vector3::CompClamp(const Vector3& v,
                           const Vector3& min,
                           const Vector3& max)
{ return CompMin(CompMax(v, min), max); }


////////////////////////////////////////////////////////////////////////////////
// Factories (continued)
Vector3 Vector3::Reflect(const Vector3& incident,
                         const Vector3& unitNormal)
{
	return incident - 2.0f*DotProduct(unitNormal, incident)*unitNormal;
}

Vector3 Vector3::Refract(const Vector3& unitIncident,
                         const Vector3& unitNormal,
                         const float& eta)
{
	float nDotI = DotProduct(unitIncident, unitNormal);
	float k     = 1.0f - eta * eta * (1.0f - nDotI * nDotI);
	if(k < 0.0f)
		return Vector3(0.0f, 0.0f, 0.0f);
	else
		return eta * unitIncident - (eta * nDotI + std::sqrt(k)) * unitNormal;
}


////////////////////////////////////////////////////////////////////////////////
// Constructor
Vector3::Vector3(const float& x, const float& y, const float& z) :
	mX(x), mY(y), mZ(z)
{
}


////////////////////////////////////////////////////////////////////////////////
// Length
float Vector3::Length() const
{
	return std::sqrt(LengthSquared());
}


////////////////////////////////////////////////////////////////////////////////
// Length Squared
float Vector3::LengthSquared() const
{
	return mX*mX + mY*mY + mZ*mZ;
}


////////////////////////////////////////////////////////////////////////////////
// Normalize
Vector3 Vector3::Normalize() const
{
	float invLength = 1.0f/Length();
	return invLength*(*this);
}


////////////////////////////////////////////////////////////////////////////////
// Bracket operators
const float& Vector3::operator[](size_t row) const
{
#ifndef NDEBUG
	assert(row < 3);
#endif
	return (&mX)[row];
}

float& Vector3::operator[](size_t row)
{
	return const_cast< float& >((static_cast< const Vector3& >(*this))[row]);
}


////////////////////////////////////////////////////////////////////////////////
// Arithmetic operators
Vector3 Vector3::operator+(const Vector3& v) const
{return Vector3(mX+v.mX, mY+v.mY, mZ+v.mZ);}

Vector3 Vector3::operator-(const Vector3& v) const
{return Vector3(mX-v.mX, mY-v.mY, mZ-v.mZ);}

Vector3 Vector3::operator*(const float& s) const
{return Vector3(mX*s, mY*s, mZ*s);}

Vector3 Vector3::operator/(const float& s) const
{
#ifndef NDEBUG
	assert(s != 0.0f);
#endif
	return (1.0f/s) * (*this);
}

Vector3 Vector3::operator+() const
{return Vector3(+mX, +mY, +mZ);}

Vector3 Vector3::operator-() const
{return Vector3(-mX, -mY, -mZ);}

////////////////////////////////////////////////////////////////////////////////
// Assignment operators
Vector3& Vector3::operator+=(const Vector3& v)
{mX+=v.mX; mY+=v.mY; mZ+=v.mZ; return (*this);}

Vector3& Vector3::operator-=(const Vector3& v)
{mX-=v.mX; mY-=v.mY; mZ-=v.mZ; return (*this);}

Vector3& Vector3::operator*=(const float& s)
{mX*=s; mY*=s; mZ*=s; return (*this);}

Vector3& Vector3::operator/=(const float& s)
{
#ifndef NDEBUG
	assert(s != 0.0f);
#endif
	float invS = 1.0f/s;
	mX *= invS;
	mY *= invS;
	mZ *= invS;
	return (*this);
}

////////////////////////////////////////////////////////////////////////////////
// Comparison operators
bool Vector3::operator==(const Vector3& v) const
{ return (v.mX == mX && v.mY == mY && v.mZ == mZ); }

bool Vector3::operator!=(const Vector3& v) const
{ return !(v == *this); }


////////////////////////////////////////////////////////////////////////////////
// Additionnal operators
Vector3 operator*(const float& s, const Vector3& v)
{
	return Vector3(s*v[0], s*v[1], s*v[2]);
}


////////////////////////////////////////////////////////////////////////////////
// Per component queries
Vector3 Vector3::Sign() const
{ return Vector3(float((mX > 0) - (mX < 0)),
                 float((mY > 0) - (mY < 0)),
                 float((mZ > 0) - (mZ < 0))); }

Vector3 Vector3::Abs() const
{return Vector3(std::abs(mX), std::abs(mY), std::abs(mZ));}

Vector3 Vector3::Sqr() const
{return Vector3(mX*mX, mY*mY, mZ*mZ);}

Vector3 Vector3::Sqrt() const
{return Vector3(std::sqrt(mX), std::sqrt(mY), std::sqrt(mZ));}

Vector3 Vector3::Exp() const
{return Vector3(std::exp(mX), std::exp(mY), std::exp(mZ));}

Vector3 Vector3::Log() const
{return Vector3(std::log(mX), std::log(mY), std::log(mZ));}

Vector3 Vector3::Log10() const
{return Vector3(std::log10(mX), std::log10(mY), std::log10(mZ));}

Vector3 Vector3::Ceil() const
{return Vector3(std::ceil(mX), std::ceil(mY), std::ceil(mZ));}

Vector3 Vector3::Floor() const
{return Vector3(std::floor(mX), std::floor(mY), std::floor(mZ));}

Vector3 Vector3::Frac() const
{return (*this) - Floor();}


////////////////////////////////////////////////////////////////////////////////
// Dot product
float Vector3::DotProduct(const Vector3& u, const Vector3& v)
{
	return u[0]*v[0]+u[1]*v[1]+u[2]*v[2];
}


////////////////////////////////////////////////////////////////////////////////
// Cross product
Vector3 Vector3::CrossProduct(const Vector3& u, const Vector3& v)
{
	return Vector3(u[1]*v[2]-v[1]*u[2],
	               u[2]*v[0]-v[2]*u[0],
	               u[0]*v[1]-v[0]*u[1]);
}


#if 0
#include <iostream>
int main(int argc, char** argv)
{
	Vector3 x = Vector3(1,8,0);
	std::cout << x.GetX() << " " << x.GetY() << " " << x.GetZ() << " " << std::endl;
	std::cout << x[0] << " " << x[1] << " " << x[2] << " " << std::endl;
	x[0]+= 3;
	x[1] = 9 - x[1];
	x[2] -= x.GetY();
	std::cout << x[0] << " " << x[1] << " " << x[2] << " " << std::endl;

	x = Vector3(-98,0,56).Sign();
	std::cout << x[0] << " " << x[1] << " " << x[2] << " " << std::endl;

	Vector3 a(1,0,0);
	a = a.Abs();
	a = a.Exp();
	a = -Vector3(1,0,0);
	Vector3 b(1,0,0);
	b = -Vector3::CompMult(a,b);
	std::cout << Vector3::DotProduct(a.Normalize(),b) << std::endl;
	std::cout << a.Length() << " " << a.LengthSquared() << std::endl;
}
#endif

