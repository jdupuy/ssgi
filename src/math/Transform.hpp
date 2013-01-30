////////////////////////////////////////////////////////////////////////////////
// \file   Transform.hpp
// \author Jonathan Dupuy (onrendering@gmail.com)
// \brief  Provides classes to build transformations easily. Every class has at
//         least one matrix extraction method.
//         List of classes
//         - Affine: allows to build affine transformations in a right handed
//           cartesian coordinate system.
//         - Projection: allows to build projections.
//         - PinholeCamera: builds both an affine and a pin hole projection.
//           The pin hole projection is locked to the aspect of the camera's
//           resolution.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include "Algebra.hpp"

////////////////////////////////////////////////////////////////////////////////
// Affine definition
class Affine {
public:
	// Factories
	static Affine Translation(const Vector3& translation);
	static Affine RotationAboutX(float radians);
	static Affine RotationAboutY(float radians);
	static Affine RotationAboutZ(float radians);
	static Affine RotationAboutAxis(const Vector3& unitAxis,
	                                float radians);
	static Affine Rotation(float yawRadians,
	                       float pitchRadians,
	                       float rollRadians);
	static Affine Scale(float nonZeroFactor);
	static Affine LookAt(const Vector3& position,
	                     const Vector3& targetPosition,
	                     const Vector3& unitUp);

	// Constructors
	Affine();

	// Comparison operators
	bool operator==(const Affine& affine) const;
	bool operator!=(const Affine& affine) const;

	// Translations
	void TranslateWorld(const Vector3& direction);
	void TranslateLocal(const Vector3& direction);

	// Rotations
	void RotateAboutWorldX(float radians);
	void RotateAboutWorldY(float radians);
	void RotateAboutWorldZ(float radians);
	void RotateAboutLocalX(float radians);
	void RotateAboutLocalY(float radians);
	void RotateAboutLocalZ(float radians);

	// Look at
	void LookAt(const Vector3& targetPos,
	            const Vector3& unitUp);

	// Resets
	void MakeDefaultAxis();
	void MakeZeroPosition();
	void MakeUnitScale();

	// Matrix extraction
	Matrix4x4 ExtractTransformMatrix()          const;
	Matrix4x4 ExtractInverseTransformMatrix()   const;

	// Axis queries
	const Vector3& UnitXAxis()      const;
	const Vector3& UnitYAxis()      const;
	const Vector3& UnitZAxis()      const;

	// Accessors
	const Matrix3x3& GetUnitAxis()  const;
	const Vector3& GetPosition()    const;
	float GetScale()                const;

	// Mutators
	void SetScale(float nonZeroScale);
	void SetPosition(const Vector3& position);

	// Constants
	static const Affine IDENTITY; // neutral transformation

private:
	// Hidden constructors
	Affine(const Matrix3x3& unitAxis, 
	       const Vector3& position,
	       float scale);

	// Internal manipulation
	void normalizeAxis();

	// Members
	Matrix3x3 mUnitAxis;      // axis
	Vector3   mPosition;      // position
	float     mScale;         // (uniform) scale
	bool      mIsRS;          // rotation scale only
};


////////////////////////////////////////////////////////////////////////////////
// Projection definition
class Projection {
public:
	// Constants
	enum ProjectionType {
		PROJECTION_TYPE_PERSPECTIVE = 0,
		PROJECTION_TYPE_ORTHOGRAPHIC
	};

	// Factories
	static Projection Orthographic(float left,
	                               float right,
	                               float bottom,
	                               float top,
	                               float near,
	                               float far);
	static Projection Perspective(float fovyRadians,
	                              float aspect,
	                              float near,
	                              float far);
	static Projection Frustum(float left,
	                          float right,
	                          float bottom,
	                          float top,
	                          float near,
	                          float far);

	// Manipulation
	void FitHeightToAspect(float aspect);
	void FitWidthToAspect(float aspect);

	// Matrix extraction
	Matrix4x4 ExtractTransformMatrix()         const;
	Matrix4x4 ExtractInverseTransformMatrix()  const;

	// Queries
	float Width()          const;
	float Height()         const;
	float Depth()          const;
	float Aspect()         const;
	bool IsPerspective()   const;
	bool IsOrthographic()  const;

	// Mutators
	void SetLeft(float left);
	void SetRight(float left);
	void SetBottom(float left);
	void SetTop(float left);
	void SetNear(float left);
	void SetFar(float left);
	void SetType(ProjectionType type);

	// Accessors
	const float& GetLeft()   const;
	const float& GetRight()  const;
	const float& GetBottom() const;
	const float& GetTop()    const;
	const float& GetNear()   const;
	const float& GetFar()    const;
	ProjectionType GetType() const;

private:
	// Hidden construtors
	Projection(float left,
	           float right,
	           float bottom,
	           float top,
	           float near,
	           float far,
	           ProjectionType type);

	// Members
	float mLeft;
	float mRight;
	float mBottom;
	float mTop;
	float mNear;
	float mFar;
	ProjectionType mType;
};


////////////////////////////////////////////////////////////////////////////////
// PinholeCamera definition
//class PinholeCamera
//{
//public:
//	// Factories (using default settings)
//	static PinholeCamera Perspective(int16_t xres,
//	                                 int16_t yres);
//	static PinholeCamera Parallel(int16_t xres,
//	                              int16_t yres);
//	static PinholeCamera Left(int16_t xres,
//	                          int16_t yres);
//	static PinholeCamera Right(int16_t xres,
//	                           int16_t yres);
//	static PinholeCamera Top(int16_t xres,
//	                         int16_t yres);
//	static PinholeCamera Bottom(int16_t xres,
//	                            int16_t yres);
//	static PinholeCamera Front(int16_t xres,
//	                           int16_t yres);
//	static PinholeCamera Back(int16_t xres,
//	                          int16_t yres);

//	// Matrix extraction
//	Matrix4x4 ExtractViewTransformMatrix()               const;
//	Matrix4x4 ExtractInverseViewTransformMatrix()        const;
//	Matrix4x4 ExtractProjectionTransformMatrix()         const;
//	Matrix4x4 ExtractInverseProjectionTransformMatrix()  const;

//	// Queries
//	float ResolutionAspect() const;

//	// Member access
//	Affine& CoordinateSystem();

//	// Extract a normalized direction 
//	Vector3 PixelRayDir(int16_t x,
//	                    int16_t y,
//	                    float offsetX,
//	                    float offsetY) const;

//	// Mutators
//	static void SetDefaultPerspectiveProjection(const Projection& p);
//	static void SetDefaultParallelProjection(const Projection& p);
//	void SetProjection(const Projection& projection);
//	void SetXResolution(int16_t pixelCount);
//	void SetYResolution(int16_t pixelCount);

//	// Accessors
//	const Projection& GetProjection()  const;
//	int16_t GetXResolution()                  const;
//	int16_t GetYResolution()                  const;

//protected:
//	// Hidden constructors
//	PinholeCamera(const AffineTransform& coordSystem,
//	              const Projection& projection,
//	              int16_t xres,
//	              int16_t yres);

//	// Members
//	static Projection sDefaultPerspectiveProjection;
//	static Projection sDefaultParallelProjection;

//	Affine             mCoordinateSystem;
//	Projection         mProjection;
//	int16_t            mXResolution;
//	int16_t            mYResolution;
//};


#endif

