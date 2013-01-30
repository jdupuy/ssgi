#include <cassert>

#include "Transform.hpp"

////////////////////////////////////////////////////////////////////////////////
// static data
const Affine Affine::IDENTITY(Matrix3x3::Diagonal(1,1,1),
                              Vector3(0,0,0),
                              1.0f);



////////////////////////////////////////////////////////////////////////////////
// Factories
Affine Affine::Translation(const Vector3& translation)
{
	return Affine(Matrix3x3::Diagonal(1,1,1),
	               translation,
	               1.0f);
}


////////////////////////////////////////////////////////////////////////////////
// Constructor
Affine::Affine():
	mUnitAxis(Matrix3x3::Diagonal(1,1,1)),
	mPosition(Vector3(0,0,0)),
	mScale(1.f),
	mIsRS(true)
{
}


////////////////////////////////////////////////////////////////////////////////
// Explicit constructor
Affine::Affine(const Matrix3x3& unitAxis,
               const Vector3& position,
               float scale) :
	mUnitAxis(unitAxis),
	mPosition(position),
	mScale(scale),
	mIsRS(position == Vector3::ZERO)
{
	if(position != Vector3::ZERO)
		mIsRS = false;
}


////////////////////////////////////////////////////////////////////////////////
// Comparison operators
bool Affine::operator==(const Affine& affine) const
{ return !((*this) != affine); }

bool Affine::operator!=(const Affine& affine) const
{
	return (   mUnitAxis != affine.mUnitAxis
	        || mPosition != affine.mPosition
	        ||   mScale  != affine.mScale);
}


////////////////////////////////////////////////////////////////////////////////
// Translate
void Affine::TranslateWorld(const Vector3& direction)
{
	mPosition+= direction;
	mIsRS     = mPosition == Vector3::ZERO;
}

void Affine::TranslateLocal(const Vector3& direction)
{
	TranslateWorld(mUnitAxis * direction);
}


////////////////////////////////////////////////////////////////////////////////
// RotateWorld
void Affine::RotateAboutWorldX(float radians)
{ mUnitAxis = Matrix3x3::RotationAboutX(radians) * mUnitAxis; normalizeAxis(); }

void Affine::RotateAboutWorldY(float radians)
{ mUnitAxis = Matrix3x3::RotationAboutY(radians) * mUnitAxis; normalizeAxis(); }

void Affine::RotateAboutWorldZ(float radians)
{ mUnitAxis = Matrix3x3::RotationAboutZ(radians) * mUnitAxis; normalizeAxis(); }


////////////////////////////////////////////////////////////////////////////////
// RotateLocal
void Affine::RotateAboutLocalX(float radians)
{ mUnitAxis *= Matrix3x3::RotationAboutX(radians);
  normalizeAxis(); }

void Affine::RotateAboutLocalY(float radians)
{ mUnitAxis *= Matrix3x3::RotationAboutY(radians);
  normalizeAxis(); }

void Affine::RotateAboutLocalZ(float radians)
{ mUnitAxis *= Matrix3x3::RotationAboutZ(radians);
  normalizeAxis(); }


////////////////////////////////////////////////////////////////////////////////
// Look at
void Affine::LookAt(const Vector3& targetPos,
                    const Vector3& unitUp)
{
	mUnitAxis = Matrix3x3::LookAtRotation(mPosition, targetPos, unitUp);
}


////////////////////////////////////////////////////////////////////////////////
// Reset
void Affine::MakeDefaultAxis()
{
	mUnitAxis = Matrix3x3::Diagonal(1,1,1);
}

void Affine::MakeZeroPosition()
{
	mIsRS     = true;
	mPosition = Vector3(0.0f, 0.0f, 0.0f);
}

void Affine::MakeUnitScale()
{
	mScale = 1.0f;
}


////////////////////////////////////////////////////////////////////////////////
// Matrix extraction
Matrix4x4 Affine::ExtractTransformMatrix() const
{
	return Matrix4x4(mUnitAxis[0][0]*mScale,
	                 mUnitAxis[1][0]*mScale,
	                 mUnitAxis[2][0]*mScale,
	                 mPosition[0],
	                 mUnitAxis[0][1]*mScale,
	                 mUnitAxis[1][1]*mScale,
	                 mUnitAxis[2][1]*mScale,
	                 mPosition[1],
	                 mUnitAxis[0][2]*mScale,
	                 mUnitAxis[1][2]*mScale,
	                 mUnitAxis[2][2]*mScale,
	                 mPosition[2],
	                 0.0f, 0.0f, 0.0f, 1.0f);
}

Matrix4x4 Affine::ExtractInverseTransformMatrix() const
{
	if(mIsRS)
	{
		// return transpose only
		float invScale = 1.0f / mScale;
		return Matrix4x4(mUnitAxis[0][0]*invScale,
		                 mUnitAxis[0][1],
		                 mUnitAxis[0][2],
		                 0.0f,
		                 mUnitAxis[1][0],
		                 mUnitAxis[1][1]*invScale,
		                 mUnitAxis[1][2],
		                 0.0f,
		                 mUnitAxis[2][0],
		                 mUnitAxis[2][1],
		                 mUnitAxis[2][2]*invScale,
		                 0.0f,
		                 0.0f , 0.0f, 0.0f, 1.0f);
	}
	else
	{
		// compute full inverse
		return ExtractTransformMatrix().Inverse();
	}
}


////////////////////////////////////////////////////////////////////////////////
// Axis queries
const Vector3& Affine::UnitXAxis() const { return mUnitAxis[0]; }
const Vector3& Affine::UnitYAxis() const { return mUnitAxis[1]; }
const Vector3& Affine::UnitZAxis() const { return mUnitAxis[2]; }


////////////////////////////////////////////////////////////////////////////////
// Accessors
const Matrix3x3& Affine::GetUnitAxis()  const { return mUnitAxis; }
const Vector3& Affine::GetPosition()    const { return mPosition; }
float Affine::GetScale()                const { return mScale; }


////////////////////////////////////////////////////////////////////////////////
// Mutators
void Affine::SetPosition(const Vector3& position)
{
	mPosition = position;
	mIsRS     = mPosition == Vector3::ZERO;
}

void Affine::SetScale(float nonZeroScale)
{
#ifndef NDEBUG
	assert(nonZeroScale != 0.0f);
#endif
	mScale = nonZeroScale;
}


////////////////////////////////////////////////////////////////////////////////
// Normalize Axis
void Affine::normalizeAxis()
{
	mUnitAxis[0] = mUnitAxis[0].Normalize();
	mUnitAxis[1] = mUnitAxis[1].Normalize();
	mUnitAxis[2] = mUnitAxis[2].Normalize();
}


