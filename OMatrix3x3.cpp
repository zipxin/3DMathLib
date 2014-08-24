#include "stdafx.h"
#include "../OInclude/Math/OMatrix3x3.h"

const OMatrix3x3 OMatrix3x3::ZERO(
							0.0f, 0.0f, 0.0f,
							0.0f, 0.0f, 0.0f,
							0.0f, 0.0f, 0.0f);

const OMatrix3x3 OMatrix3x3::IDENTITY(
								1.0f, 0.0f, 0.0f,
								0.0f, 1.0f, 0.0f,
								0.0f, 0.0f, 1.0f);

OMatrix3x3 OMatrix3x3::Inverse() const
{
	float32 det = m11 * m22 * m33 +
		          m21 * m32 * m13 +
		          m31 * m12 * m23 -
		          m31 * m22 * m13 -
		          m21 * m12 * m33 -
		          m11 * m32 * m23;

	if(det < EPSILON8) return OMatrix3x3::ZERO;
	float invDet = 1.0f / det;

	return OMatrix3x3(
		 (m22 * m33 - m32 * m23) * invDet,
		-(m12 * m33 - m32 * m13) * invDet,
		 (m12 * m23 - m22 * m13) * invDet,
		-(m21 * m33 - m31 * m23) * invDet,
		 (m11 * m33 - m31 * m13) * invDet,
		-(m11 * m23 - m21 * m13) * invDet,
		 (m21 * m32 - m31 * m22) * invDet,
		-(m11 * m32 - m31 * m12) * invDet,
		 (m11 * m22 - m21 * m12) * invDet
		);
}

float OMatrix3x3::Determinant () const
{
	float fCofactor00 = ele_f[1][1]*ele_f[2][2] -
	            	    ele_f[1][2]*ele_f[2][1];
	float fCofactor10 = ele_f[1][2]*ele_f[2][0] -
						ele_f[1][0]*ele_f[2][2];
	float fCofactor20 = ele_f[1][0]*ele_f[2][1] -
						ele_f[1][1]*ele_f[2][0];

	float fDet =
				ele_f[0][0]*fCofactor00 +
				ele_f[0][1]*fCofactor10 +
				ele_f[0][2]*fCofactor20;

	return fDet;
}


const OMatrix3x3& OMatrix3x3::RotateXYZ(const float radianX, const float radianY,  const float radianZ)
{
	*this = *this * RotateXYZ_Replace(radianX, radianY, radianZ);	
	return *this;
}


OMatrix3x3 OMatrix3x3::RotateX_Replace(const float radian)
{
	OMatrix3x3 matrix = OMatrix3x3::IDENTITY;

	float fCos = cosf(radian);
	float fSin = sinf(radian);

	matrix.ele_f[1][1] = fCos;
	matrix.ele_f[1][2] = fSin;
	matrix.ele_f[2][1] = -fSin;
	matrix.ele_f[2][2] = fCos;

	return matrix;
}

OMatrix3x3 OMatrix3x3::RotateY_Replace(const float radian)
{
	OMatrix3x3 matrix = OMatrix3x3::IDENTITY;

	float fCos = cosf(radian);
	float fSin = sinf(radian);

	matrix.ele_f[0][0] = fCos;
	matrix.ele_f[0][2] = -fSin;
	matrix.ele_f[2][0] = fSin;
	matrix.ele_f[2][2] = fCos;

	return matrix;
}

OMatrix3x3 OMatrix3x3::RotateZ_Replace(const float radian)
{
	OMatrix3x3 matrix = OMatrix3x3::IDENTITY;

	float fCos = cosf(radian);
	float fSin = sinf(radian);

	matrix.ele_f[0][0] = fCos;
	matrix.ele_f[0][1] = fSin;
	matrix.ele_f[1][0] = -fSin;
	matrix.ele_f[1][1] = fCos;

	return matrix;
}

OMatrix3x3 OMatrix3x3::RotateXYZ_Replace(const float radianX, const float radianY,  const float radianZ)
{
	return (RotateX_Replace(radianX) * RotateY_Replace(radianY)) * RotateZ_Replace(radianZ);

}



// ×ÔÉíÐý×ª
const OMatrix3x3& OMatrix3x3::RotateX(const float radian)
{
	*this = *this * RotateX_Replace(radian);	
	return *this;
}

const OMatrix3x3& OMatrix3x3::RotateY(const float radian)
{
	*this = *this * RotateY_Replace(radian);	
	return *this;
}

const OMatrix3x3& OMatrix3x3::RotateZ(const float radian)
{
	*this = *this * RotateZ_Replace(radian);	
	return *this;
}

