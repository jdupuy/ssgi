#include <cassert>
#include <cmath>

#include "Transform.hpp"


////////////////////////////////////////////////////////////////////////////////
// Perspective factory
Projection Projection::Perspective(float fovy,
                                   float aspect,
                                   float near,
                                   float far)
{
#ifndef NDEBUG
	assert(   fovy > 0.0f
	       && aspect > 0.0f
	       && near < far
	       && near > 0.0f);
#endif

	// convert to frustum
	float halfHeight = std::tan(fovy*0.5f) * near;
	float halfWidth  = halfHeight * aspect;

	return Frustum(-halfWidth,
	                halfWidth,
	               -halfHeight,
	                halfHeight,
	                near,
	                far);
}


////////////////////////////////////////////////////////////////////////////////
// Frustum factory
Projection Projection::Frustum(float left,
                               float right,
                               float bottom,
                               float top,
                               float near,
                               float far)
{
#ifndef NDEBUG
	assert(   left != right 
	       && bottom != top
	       && near != far 
	       && near > 0.0f
	       && far > 0.0f);
#endif

	return Projection(left,
	                  right,
	                  bottom,
	                  top,
	                  near,
	                  far,
	                  PROJECTION_TYPE_PERSPECTIVE);
}


////////////////////////////////////////////////////////////////////////////////
// Ortho factory
Projection Projection::Orthographic(float left,
	                                float right,
	                                float bottom,
	                                float top,
	                                float near,
	                                float far)
{
#ifndef NDEBUG
	assert(   left != right 
	       && bottom != top
	       && near != far);
#endif
	return Projection(left,
	                  right,
	                  bottom,
	                  top,
	                  near,
	                  far,
	                  PROJECTION_TYPE_ORTHOGRAPHIC);
}


////////////////////////////////////////////////////////////////////////////////
// Explicit constructor
Projection::Projection(float left,
                       float right,
                       float bottom,
                       float top,
                       float near,
                       float far,
                       Projection::ProjectionType type):
	mLeft(left),
	mRight(right),
	mBottom(bottom),
	mTop(top),
	mNear(near),
	mFar(far),
	mType(type)
{
}


////////////////////////////////////////////////////////////////////////////////
// Extract Matrix
Matrix4x4 Projection::ExtractTransformMatrix() const
{
	if(mType == PROJECTION_TYPE_PERSPECTIVE)
		return Matrix4x4::Frustum(mLeft,
		                          mRight,
		                          mBottom,
		                          mTop,
		                          mNear,
		                          mFar);
	return Matrix4x4::Ortho(mLeft,
		                    mRight,
		                    mBottom,
		                    mTop,
		                    mNear,
		                    mFar);
}

Matrix4x4 Projection::ExtractInverseTransformMatrix() const
{
	return ExtractTransformMatrix().Inverse();
}


////////////////////////////////////////////////////////////////////////////////
// Queries
float Projection::Width() const
{ return std::abs(mRight - mLeft); }

float Projection::Height() const
{ return std::abs(mTop - mBottom); }

float Projection::Depth() const
{ return std::abs(mFar - mNear); }

float Projection::Aspect() const
{ return Width() / Height(); }

bool Projection::IsPerspective() const
{ return (mType == PROJECTION_TYPE_PERSPECTIVE); }

bool Projection::IsOrthographic() const
{ return (mType == PROJECTION_TYPE_ORTHOGRAPHIC); }


////////////////////////////////////////////////////////////////////////////////
// Fit to aspect
void Projection::FitHeightToAspect(float aspect)
{
	// compute factor
	float factor        = Aspect()/aspect;

	mBottom *= factor;
	mTop    *= factor;
}

void Projection::FitWidthToAspect(float aspect)
{
	// get current aspect
	float factor        = aspect/Aspect();

	mLeft  *= factor;
	mRight *= factor;
}


////////////////////////////////////////////////////////////////////////////////
// Accessors
const float& Projection::GetLeft() const
{return mLeft;}
const float& Projection::GetRight() const
{return mRight;}
const float& Projection::GetBottom() const
{return mBottom;}
const float& Projection::GetTop() const
{return mTop;}
const float& Projection::GetNear() const
{return mNear;}
const float& Projection::GetFar() const
{return mFar;}
Projection::ProjectionType Projection::GetType() const
{return mType;}


////////////////////////////////////////////////////////////////////////////////
// Mutators
void Projection::SetLeft(float left)
{
#ifndef NDEBUG
	assert(left != mRight);
#endif
	mLeft = left;
}

void Projection::SetRight(float right)
{
#ifndef NDEBUG
	assert(right != mLeft);
#endif
	mRight = right;
}

void Projection::SetBottom(float bottom)
{
#ifndef NDEBUG
	assert(bottom != mTop);
#endif
	mBottom = bottom;
}

void Projection::SetTop(float top)
{
#ifndef NDEBUG
	assert(mBottom != top);
#endif
	mTop = top;
}

void Projection::SetNear(float near)
{
#ifndef NDEBUG
	assert(near != mFar);
	if(mType == PROJECTION_TYPE_PERSPECTIVE)
		assert(near > 0.0f);
#endif
	mNear = near;
}

void Projection::SetFar(float far)
{
#ifndef NDEBUG
	assert(far != mNear);
	if(mType == PROJECTION_TYPE_PERSPECTIVE)
		assert(far > 0.0f);
#endif
	mFar = far;
}

void Projection::SetType(Projection::ProjectionType type)
{
	mType = type;
}





