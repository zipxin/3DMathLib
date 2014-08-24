#include "stdafx.h"
#include "../OInclude/Math/OMatrix4x4.h"

OMatrix4x4 g_Matrix4x4_Identity = OMatrix4x4(
	1.0f, 0.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 0.0f, 1.0f
	);

OMatrix4x4 g_Matrix4x4_Zero = OMatrix4x4(
	0.0f, 0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f, 0.0f
	);


const OMatrix4x4 OMatrix4x4::ZERO(
							0, 0, 0, 0,
							0, 0, 0, 0,
							0, 0, 0, 0,
							0, 0, 0, 0 );

const OMatrix4x4 OMatrix4x4::IDENTITY(
								1, 0, 0, 0,
								0, 1, 0, 0,
								0, 0, 1, 0,
								0, 0, 0, 1 );

const OMatrix4x4 OMatrix4x4::CLIPSPACE2DTOIMAGESPACE(
							0.5,    0,  0, 0.5, 
							0, -0.5,  0, 0.5, 
							0,    0,  1,   0,
							0,    0,  0,   1);


inline float
MINOR(const OMatrix4x4& m, const int r0, const int r1, const int r2, 
	  const int c0, const int c1, const int c2)
{
	return m[r0][c0] * (m[r1][c1] * m[r2][c2] - m[r2][c1] * m[r1][c2]) -
		m[r0][c1] * (m[r1][c0] * m[r2][c2] - m[r2][c0] * m[r1][c2]) +
		m[r0][c2] * (m[r1][c0] * m[r2][c1] - m[r2][c0] * m[r1][c1]);
}


OMatrix4x4 OMatrix4x4::Adjoint() const
{
	return OMatrix4x4( MINOR(*this, 1, 2, 3, 1, 2, 3),
		-MINOR(*this, 0, 2, 3, 1, 2, 3),
		MINOR(*this, 0, 1, 3, 1, 2, 3),
		-MINOR(*this, 0, 1, 2, 1, 2, 3),

		-MINOR(*this, 1, 2, 3, 0, 2, 3),
		MINOR(*this, 0, 2, 3, 0, 2, 3),
		-MINOR(*this, 0, 1, 3, 0, 2, 3),
		MINOR(*this, 0, 1, 2, 0, 2, 3),

		MINOR(*this, 1, 2, 3, 0, 1, 3),
		-MINOR(*this, 0, 2, 3, 0, 1, 3),
		MINOR(*this, 0, 1, 3, 0, 1, 3),
		-MINOR(*this, 0, 1, 2, 0, 1, 3),

		-MINOR(*this, 1, 2, 3, 0, 1, 2),
		MINOR(*this, 0, 2, 3, 0, 1, 2),
		-MINOR(*this, 0, 1, 3, 0, 1, 2),
		MINOR(*this, 0, 1, 2, 0, 1, 2));
}


float OMatrix4x4::Determinant() const
{
	return ele_f[0][0] * MINOR(*this, 1, 2, 3, 1, 2, 3) -
		ele_f[0][1] * MINOR(*this, 1, 2, 3, 0, 2, 3) +
		ele_f[0][2] * MINOR(*this, 1, 2, 3, 0, 1, 3) -
		ele_f[0][3] * MINOR(*this, 1, 2, 3, 0, 1, 2);
}

OMatrix4x4 OMatrix4x4::Inverse() const
{
	float f = Determinant();
	if (fabsf(f) < EPSILON8)
		return OMatrix4x4::ZERO;
	else
		return Adjoint() * (1.0f / f);
}

OMatrix4x4 OMatrix4x4::RotaieXYZ_Replace(const float radianX, const float radianY,  const float radianZ)
{
	/* m = GetRotatonMatrixX * GetRotatonMatrixY * GetRotatonMatrixZ
	 * sx, cx, sy, cy, sz, cz
	 * 
	 *
	 *
	 */
/*	float sx = sinf(radianX);
	float cx = cosf(radianX);
	float sy = sinf(radianY);
	float cy = cosf(radianY);
	float sz = sinf(radianZ);
	float cz = cosf(radianZ);
*/
	return (RotateX_Replace(radianX) * RotateY_Replace(radianY)) * RotateZ_Replace(radianZ);

}


//   /// Return decomposition to translation, rotation and scale
// void OMatrix4x4::Decompose(Vector3& translation, Quaternion& rotation, Vector3& scale) const
// {
// 	translation.x_ = m03_;
// 	translation.y_ = m13_;
// 	translation.z_ = m23_;
// 
// 	scale.x_ = sqrtf(m00_ * m00_ + m10_ * m10_ + m20_ * m20_);
// 	scale.y_ = sqrtf(m01_ * m01_ + m11_ * m11_ + m21_ * m21_);
// 	scale.z_ = sqrtf(m02_ * m02_ + m12_ * m12_ + m22_ * m22_);
// 
// 	Vector3 invScale(1.0f / scale.x_, 1.0f / scale.y_, 1.0f / scale.z_);
// 	rotation = Quaternion(ToMatrix3().Scaled(invScale));
// }

// Matrix4 Matrix4::Inverse() const
// {
// 	float v0 = m20_ * m31_ - m21_ * m30_;
// 	float v1 = m20_ * m32_ - m22_ * m30_;
// 	float v2 = m20_ * m33_ - m23_ * m30_;
// 	float v3 = m21_ * m32_ - m22_ * m31_;
// 	float v4 = m21_ * m33_ - m23_ * m31_;
// 	float v5 = m22_ * m33_ - m23_ * m32_;
// 
// 	float i00 = (v5 * m11_ - v4 * m12_ + v3 * m13_);
// 	float i10 = -(v5 * m10_ - v2 * m12_ + v1 * m13_);
// 	float i20 = (v4 * m10_ - v2 * m11_ + v0 * m13_);
// 	float i30 = -(v3 * m10_ - v1 * m11_ + v0 * m12_);
// 
// 	float invDet = 1.0f / (i00 * m00_ + i10 * m01_ + i20 * m02_ + i30 * m03_);
// 
// 	i00 *= invDet;
// 	i10 *= invDet;
// 	i20 *= invDet;
// 	i30 *= invDet;
// 
// 	float i01 = -(v5 * m01_ - v4 * m02_ + v3 * m03_) * invDet;
// 	float i11 = (v5 * m00_ - v2 * m02_ + v1 * m03_) * invDet;
// 	float i21 = -(v4 * m00_ - v2 * m01_ + v0 * m03_) * invDet;
// 	float i31 = (v3 * m00_ - v1 * m01_ + v0 * m02_) * invDet;
// 
// 	v0 = m10_ * m31_ - m11_ * m30_;
// 	v1 = m10_ * m32_ - m12_ * m30_;
// 	v2 = m10_ * m33_ - m13_ * m30_;
// 	v3 = m11_ * m32_ - m12_ * m31_;
// 	v4 = m11_ * m33_ - m13_ * m31_;
// 	v5 = m12_ * m33_ - m13_ * m32_;
// 
// 	float i02 = (v5 * m01_ - v4 * m02_ + v3 * m03_) * invDet;
// 	float i12 = -(v5 * m00_ - v2 * m02_ + v1 * m03_) * invDet;
// 	float i22 = (v4 * m00_ - v2 * m01_ + v0 * m03_) * invDet;
// 	float i32 = -(v3 * m00_ - v1 * m01_ + v0 * m02_) * invDet;
// 
// 	v0 = m21_ * m10_ - m20_ * m11_;
// 	v1 = m22_ * m10_ - m20_ * m12_;
// 	v2 = m23_ * m10_ - m20_ * m13_;
// 	v3 = m22_ * m11_ - m21_ * m12_;
// 	v4 = m23_ * m11_ - m21_ * m13_;
// 	v5 = m23_ * m12_ - m22_ * m13_;
// 
// 	float i03 = -(v5 * m01_ - v4 * m02_ + v3 * m03_) * invDet;
// 	float i13 = (v5 * m00_ - v2 * m02_ + v1 * m03_) * invDet;
// 	float i23 = -(v4 * m00_ - v2 * m01_ + v0 * m03_) * invDet;
// 	float i33 = (v3 * m00_ - v1 * m01_ + v0 * m02_) * invDet;
// 
// 	return Matrix4(
// 		i00, i01, i02, i03,
// 		i10, i11, i12, i13,
// 		i20, i21, i22, i23,
// 		i30, i31, i32, i33);
// }
