#include <cmath>
#include <algorithm>
#include <cassert>

#include "Algebra.hpp"

////////////////////////////////////////////////////////////////////////////////
// Constants
const Vector2 Vector2::ZERO(0.0f,0.0f);


////////////////////////////////////////////////////////////////////////////////
// Factories
Vector2 Vector2::CompMult(const Vector2& u,
                          const Vector2& v)
{ return Vector2(u[0]*v[0], u[1]*v[1]); }

Vector2 Vector2::CompDiv(const Vector2& u,
                         const Vector2& v)
{ return Vector2(u[0]/v[0], u[1]/v[1]); }

Vector2 Vector2::CompPow(const Vector2& base,
                         const Vector2& exponent)
{ return Vector2(std::pow(base[0],exponent[0]),
                 std::pow(base[1],exponent[1])); }

Vector2 Vector2::CompMin(const Vector2& u,
                         const Vector2& v)
{ return Vector2(std::min(u[0],v[0]),
                 std::min(u[1],v[1])); }

Vector2 Vector2::CompMax(const Vector2& u,
                         const Vector2& v)
{ return Vector2(std::max(u[0],v[0]),
                 std::max(u[1],v[1])); }

Vector2 Vector2::CompClamp(const Vector2& v,
                           const Vector2& min,
                           const Vector2& max)
{ return CompMin(CompMax(v, min), max); }


////////////////////////////////////////////////////////////////////////////////
// Factories (continued)
Vector2 Vector2::Reflect(const Vector2& incident,
                         const Vector2& unitNormal)
{
	return incident - 2.0f*DotProduct(unitNormal, incident)*unitNormal;
}

Vector2 Vector2::Refract(const Vector2& unitIncident,
                         const Vector2& unitNormal,
                         const float& eta)
{
	float nDotI = DotProduct(unitIncident, unitNormal);
	float k     = 1.0f - eta * eta * (1.0f - nDotI * nDotI);
	if(k < 0.0f)
		return Vector2(0.0f, 0.0f);
	else
		return eta * unitIncident - (eta * nDotI + std::sqrt(k)) * unitNormal;
}


////////////////////////////////////////////////////////////////////////////////
// Constructor
Vector2::Vector2(const float& x, const float& y) :
	mX(x), mY(y)
{
}


////////////////////////////////////////////////////////////////////////////////
// Length
float Vector2::Length() const
{
	return std::sqrt(LengthSquared());
}


////////////////////////////////////////////////////////////////////////////////
// Length Squared
float Vector2::LengthSquared() const
{
	return mX*mX + mY*mY;
}


////////////////////////////////////////////////////////////////////////////////
// Normalize
Vector2 Vector2::Normalize() const
{
	float invLength = 1.0f/Length();
	return invLength*(*this);
}


////////////////////////////////////////////////////////////////////////////////
// Bracket operators
const float& Vector2::operator[](size_t row) const
{
#ifndef NDEBUG
	assert(row < 2);
#endif
	return (&mX)[row];
}

float& Vector2::operator[](size_t row)
{
	return const_cast< float& >((static_cast< const Vector2& >(*this))[row]);
}


////////////////////////////////////////////////////////////////////////////////
// Arithmetic operators
Vector2 Vector2::operator+(const Vector2& v) const
{return Vector2(mX+v.mX, mY+v.mY);}

Vector2 Vector2::operator-(const Vector2& v) const
{return Vector2(mX-v.mX, mY-v.mY);}

Vector2 Vector2::operator*(const float& s) const
{return Vector2(mX*s, mY*s);}

Vector2 Vector2::operator/(const float& s) const
{
#ifndef NDEBUG
	assert(s != 0.0f);
#endif
	return (1.0f/s) * (*this);
}

Vector2 Vector2::operator+() const
{return Vector2(+mX, +mY);}

Vector2 Vector2::operator-() const
{return Vector2(-mX, -mY);}

////////////////////////////////////////////////////////////////////////////////
// Assignment operators
Vector2& Vector2::operator+=(const Vector2& v)
{mX+=v.mX; mY+=v.mY; return (*this);}

Vector2& Vector2::operator-=(const Vector2& v)
{mX-=v.mX; mY-=v.mY; return (*this);}

Vector2& Vector2::operator*=(const float& s)
{mX*=s; mY*=s; return (*this);}

Vector2& Vector2::operator/=(const float& s)
{
#ifndef NDEBUG
	assert(s != 0.0f);
#endif
	float invS = 1.0f/s;
	mX *= invS;
	mY *= invS;
	return (*this);
}

////////////////////////////////////////////////////////////////////////////////
// Comparison operators
bool Vector2::operator==(const Vector2& v) const
{ return (v.mX == mX && v.mY == mY); }

bool Vector2::operator!=(const Vector2& v) const
{ return !(v == *this); }


////////////////////////////////////////////////////////////////////////////////
// Additionnal operators
Vector2 operator*(const float& s, const Vector2& v)
{
	return Vector2(s*v[0], s*v[1]);
}


////////////////////////////////////////////////////////////////////////////////
// Per component queries
Vector2 Vector2::Sign() const
{ return Vector2(float((mX > 0) - (mX < 0)),
                 float((mY > 0) - (mY < 0))); }

Vector2 Vector2::Abs() const
{return Vector2(std::abs(mX), std::abs(mY));}

Vector2 Vector2::Sqr() const
{return Vector2(mX*mX, mY*mY);}

Vector2 Vector2::Sqrt() const
{return Vector2(std::sqrt(mX), std::sqrt(mY));}

Vector2 Vector2::Exp() const
{return Vector2(std::exp(mX), std::exp(mY));}

Vector2 Vector2::Log() const
{return Vector2(std::log(mX), std::log(mY));}

Vector2 Vector2::Log10() const
{return Vector2(std::log10(mX), std::log10(mY));}

Vector2 Vector2::Ceil() const
{return Vector2(std::ceil(mX), std::ceil(mY));}

Vector2 Vector2::Floor() const
{return Vector2(std::floor(mX), std::floor(mY));}

Vector2 Vector2::Frac() const
{return (*this) - Floor();}


////////////////////////////////////////////////////////////////////////////////
// Dot product
float Vector2::DotProduct(const Vector2& u, const Vector2& v)
{
	return u[0]*v[0]+u[1]*v[1];
}


#if 0
#include <iostream>
int main(int argc, char** argv)
{
	Vector2 x = Vector2(1,8);
	std::cout << x.GetX() << " " << x.GetY() << std::endl;
	std::cout << x[0] << " " << x[1] << std::endl;
	x[0] += 2;
	x[1] = 9 - x[1];
	std::cout << x[0] << " " << x[1] << std::endl;

	Vector2 a(1,0);
	a = a.Abs();
	a = a.Exp();
	a = -Vector2(0,1);
	Vector2 b(1,0);
	b = -Vector2::CompMult(a,b);
	std::cout << Vector2::DotProduct(a.Normalize(),b) << std::endl;
	std::cout << a.Length() << " " << a.LengthSquared() << std::endl;
}
#endif

