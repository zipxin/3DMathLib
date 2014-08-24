#include "stdafx.h"

#include "OQuaternion.h"


const OQuaternion OQuaternion::IDENTITY;
const OQuaternion OQuaternion::ZERO(0.0,0.0,0.0,0.0);


//////////////////////////////////////////////////////////////////////////
// axis 会被归一化处理
// The quaternion representing the rotation is
//   q = cos(A/2)+sin(A/2)*(x*i+y*j+z*k)
void OQuaternion::FromAngleAxis(float32 angle, const OVector3& axis)
{
	OVector3 norAxis = axis.Nomarlized();
	angle *= DEGTORAD_2;
	float sinAngle = sinf(angle);
	float cosAngle = cosf(angle);

	w = cosAngle;
	x = norAxis.x * sinAngle;
	y = norAxis.y * sinAngle;
	z = norAxis.z * sinAngle;
}

void OQuaternion::FromEulerAngles(float32 _x, float32 _y, float32 _z)
{
	// Order of rotations: Z first, then X, then Y 
	// (mimics typical FPS camera with gimbal lock at top/bottom)
	_x *= DEGTORAD_2;
	_y *= DEGTORAD_2;
	_z *= DEGTORAD_2;
	float sinX = sinf(_x);
	float cosX = cosf(_x);
	float sinY = sinf(_y);
	float cosY = cosf(_y);
	float sinZ = sinf(_z);
	float cosZ = cosf(_z);

	w = cosY * cosX * cosZ + sinY * sinX * sinZ;
	x = cosY * sinX * cosZ + sinY * cosX * sinZ;
	y = sinY * cosX * cosZ - cosY * sinX * sinZ;
	z = cosY * cosX * sinZ - sinY * sinX * cosZ;
}

void OQuaternion::FromRotationTo(const OVector3& start, const OVector3& end)
{
	OVector3 normStart = start.Nomarlized();
	OVector3 normEnd = end.Nomarlized();
	float32 d = Vec3_Dotf(normStart, normEnd);

	if (d > -1.0f + EPSILON)
	{
		OVector3 c = Vec3_CrossProduct(normStart, normEnd);
		float32 s = sqrtf((1.0f + d) * 2.0f);
		float32 invS = 1.0f / s;

		x = c.x * invS;
		y = c.y * invS;
		z = c.z * invS;
		w = 0.5f * s;
	}
	else
	{
		OVector3 axis = Vec3_CrossProduct(OVector3::RIGHT, normStart);
		if (axis.Length() < EPSILON)
			axis = Vec3_CrossProduct(OVector3::UP, normStart);

		FromAngleAxis(180.f, axis);
	}
}
void OQuaternion::FromAxes (const OVector3* akAxis)
{
	OMatrix3x3 kRot;

	for (int iCol = 0; iCol < 3; iCol++)
	{
		kRot[0][iCol] = akAxis[iCol].x;
		kRot[1][iCol] = akAxis[iCol].y;
		kRot[2][iCol] = akAxis[iCol].z;
	}

	FromRotationMatrix(kRot);
}

void OQuaternion::FromAxes(const OVector3& xAxis, const OVector3& yAxis, const OVector3& zAxis)
{
	OMatrix3x3 matrix(
		xAxis.x, yAxis.x, zAxis.x,
		xAxis.y, yAxis.y, zAxis.y,
		xAxis.z, yAxis.z, zAxis.z
		);

	FromRotationMatrix(matrix);
}

void OQuaternion::FromRotationMatrix(const OMatrix3x3& matrix)
{
	float32 t = matrix.m11 + matrix.m22 + matrix.m33;

	if (t > 0.0f)
	{
		float invS = 0.5f / sqrtf(1.0f + t);

		x = (matrix.m32 - matrix.m32) * invS;
		y = (matrix.m13 - matrix.m31) * invS;
		z = (matrix.m21 - matrix.m12) * invS;
		w = 0.25f / invS;
	}
	else
	{
		if (matrix.m11 > matrix.m22 && matrix.m11 > matrix.m33)
		{
			float32 invS = 0.5f / sqrtf(1.0f + matrix.m11 - matrix.m22 - matrix.m33);

			x = 0.25f / invS;
			y = (matrix.m12 + matrix.m21) * invS;
			z = (matrix.m31 + matrix.m13) * invS;
			w = (matrix.m32 - matrix.m23) * invS;
		}
		else if (matrix.m22 > matrix.m33)
		{
			float32 invS = 0.5f / sqrtf(1.0f + matrix.m22 - matrix.m11 - matrix.m33);

			x = (matrix.m12 + matrix.m21) * invS;
			y = 0.25f / invS;
			z = (matrix.m23 + matrix.m32) * invS;
			w = (matrix.m13 - matrix.m31) * invS;
		}
		else
		{
			float32 invS = 0.5f / sqrtf(1.0f + matrix.m33 - matrix.m11 - matrix.m22);

			x = (matrix.m13 + matrix.m31) * invS;
			y = (matrix.m23 + matrix.m32) * invS;
			z = 0.25f / invS;
			w = (matrix.m21 - matrix.m12) * invS;
		}
	}
}

void OQuaternion::FromLookRotation(const OVector3& direction, const OVector3& upDirection)
{
	OVector3 forward = direction.Nomarlized();
	OVector3 v = Vec3_CrossProduct(forward, upDirection);
	v.Nomarlize();
	OVector3 up = Vec3_CrossProduct(v, forward);
	OVector3 right = Vec3_CrossProduct(up, forward);

	OQuaternion ret;
	ret.w = sqrtf(1.0f + right.x + up.y + forward.z) * 0.5f;
	float32 w4Recip = 1.0f / (4.0f * ret.w);
	ret.x = (up.z - forward.y) * w4Recip;
	ret.y = (forward.x - right.z) * w4Recip;
	ret.z = (right.y - up.x) * w4Recip;

	(*this) = ret;
}

OVector3 OQuaternion::EulerAngles() const
{
	// Derivation from http://www.geometrictools.com/Documentation/EulerAngles.pdf
	// Order of rotations: Z first, then X, then Y
	float check = 2.0f * (-y * z + w * x);

	if (check < -0.995f)
	{
		return OVector3(
			-90.0f,
			0.0f,
			-atan2f(2.0f * (x * z - w * y), 1.0f - 2.0f * (y * y + z * z)) * RAD_TO_DEG
			);
	}
	else if (check > 0.995f)
	{
		return OVector3(
			90.0f,
			0.0f,
			atan2f(2.0f * (x * z - w * y), 1.0f - 2.0f * (y * y + z * z)) * RAD_TO_DEG
			);
	}
	else
	{
		return OVector3(
			asinf(check) * RAD_TO_DEG,
			atan2f(2.0f * (x * z + w * y), 1.0f - 2.0f * (x * x + y * y)) * RAD_TO_DEG,
			atan2f(2.0f * (x * y + w * z), 1.0f - 2.0f * (x * x + z * z)) * RAD_TO_DEG
			);
	}
}

//asinf(-2*(x*z - w*y))
float OQuaternion::YawAngle() const
{
	return EulerAngles().y;
}

//atan2f(2*(y*z + w*x), w*w - x*x - y*y + z*z)
float OQuaternion::PitchAngle() const
{
	return EulerAngles().x;
}

//atan2f(2*(x*y + w*z), w*w + x*x - y*y - z*z)
float OQuaternion::RollAngle() const
{
	return EulerAngles().z;
}

OMatrix3x3 OQuaternion::RotationMatrix() const
{
	OMatrix3x3 kRot;
	float fTx  = 2.0f * x;
	float fTy  = 2.0f * y;
	float fTz  = 2.0f * z;
	float fTwx = fTx * w;
	float fTwy = fTy * w;
	float fTwz = fTz * w;
	float fTxx = fTx * x;
	float fTxy = fTy * x;
	float fTxz = fTz * x;
	float fTyy = fTy * y;
	float fTyz = fTz * y;
	float fTzz = fTz * z;

	kRot[0][0] = 1.0f - ( fTyy + fTzz );
	kRot[0][1] = fTxy - fTwz;
	kRot[0][2] = fTxz + fTwy;
	kRot[1][0] = fTxy + fTwz;
	kRot[1][1] = 1.0f - ( fTxx + fTzz );
	kRot[1][2] = fTyz - fTwx;
	kRot[2][0] = fTxz - fTwy;
	kRot[2][1] = fTyz + fTwx;
	kRot[2][2] = 1.0f - ( fTxx + fTyy );

	return kRot;
}

OQuaternion OQuaternion::Slerp(OQuaternion rhs, float t) const
{
	float cosAngle = DotProduct(rhs);
	// Enable shortest path rotation
	if (cosAngle < 0.0f)
	{
		cosAngle = -cosAngle;
		rhs = -rhs;
	}

	float angle = acosf(cosAngle);
	float sinAngle = sinf(angle);
	float t1, t2;

	if (sinAngle > 0.001f)
	{
		float invSinAngle = 1.0f / sinAngle;
		t1 = sinf((1.0f - t) * angle) * invSinAngle;
		t2 = sinf(t * angle) * invSinAngle;
	}
	else
	{
		t1 = 1.0f - t;
		t2 = t;
	}

	return *this * t1 + rhs * t2;
}

OQuaternion OQuaternion::Nlerp(OQuaternion rhs, float t, bool shortestPath) const
{
	OQuaternion result;
	float fCos = DotProduct(rhs);
	if (fCos < 0.0f && shortestPath)
		result = (*this) + (((-rhs) - (*this)) * t);
	else
		result = (*this) + ((rhs - (*this)) * t);
	result.Normalize();
	return result;
}


//-----------------------------------------------------------------------
void OQuaternion::ToAngleRadianAxis (float& rfAngle, OVector3& rkAxis) const
{
	// The quaternion representing the rotation is
	//   q = cos(A/2)+sin(A/2)*(x*i+y*j+z*k)

	float fSqrLength = x*x+y*y+z*z;
	if ( fSqrLength > 0.0 )
	{
		rfAngle = 2.f*acosf(w);
// 		float fInvLength = InvSqrt(fSqrLength);
// 		rkAxis.x = x*fInvLength;
// 		rkAxis.y = y*fInvLength;
// 		rkAxis.z = z*fInvLength;
	}
	else
	{
		// angle is 0 (mod 2*pi), so any axis will do
		rfAngle  = 0;
		rkAxis.x = 1.0;
		rkAxis.y = 0.0;
		rkAxis.z = 0.0;
	}
}
//-----------------------------------------------------------------------


//-----------------------------------------------------------------------
void OQuaternion::ToAxes (OVector3* akAxis) const
{
	OMatrix3x3 kRot;

	kRot = RotationMatrix();

	for (int iCol = 0; iCol < 3; iCol++)
	{
		akAxis[iCol].x = kRot[0][iCol];
		akAxis[iCol].y = kRot[1][iCol];
		akAxis[iCol].z = kRot[2][iCol];
	}
}
//-----------------------------------------------------------------------
OVector3 OQuaternion::xAxis(void) const
{
	float fTx  = 2.f*x;
	float fTy  = 2.f*y;
	float fTz  = 2.f*z;
	float fTwy = fTy*w;
	float fTwz = fTz*w;
	float fTxy = fTy*x;
	float fTxz = fTz*x;
	float fTyy = fTy*y;
	float fTzz = fTz*z;

	return OVector3(1.f-(fTyy+fTzz), fTxy+fTwz, fTxz-fTwy);
}
//-----------------------------------------------------------------------
OVector3 OQuaternion::yAxis(void) const
{
	float fTx  = 2.f*x;
	float fTy  = 2.f*y;
	float fTz  = 2.f*z;
	float fTwx = fTx*w;
	float fTwz = fTz*w;
	float fTxx = fTx*x;
	float fTxy = fTy*x;
	float fTyz = fTz*y;
	float fTzz = fTz*z;

	return OVector3(fTxy-fTwz, 1.f-(fTxx+fTzz), fTyz+fTwx);
}
//-----------------------------------------------------------------------
OVector3 OQuaternion::zAxis(void) const
{
	float fTx  = 2.f*x;
	float fTy  = 2.f*y;
	float fTz  = 2.f*z;
	float fTwx = fTx*w;
	float fTwy = fTy*w;
	float fTxx = fTx*x;
	float fTxz = fTz*x;
	float fTyy = fTy*y;
	float fTyz = fTz*y;

	return OVector3(fTxz+fTwy, fTyz-fTwx, 1.0f-(fTxx+fTyy));
}
//-----------------------------------------------------------------------
void OQuaternion::ToAxes (OVector3& xaxis, OVector3& yaxis, OVector3& zaxis) const
{
	OMatrix3x3 kRot;

	kRot = RotationMatrix();

	xaxis.x = kRot[0][0];
	xaxis.y = kRot[1][0];
	xaxis.z = kRot[2][0];

	yaxis.x = kRot[0][1];
	yaxis.y = kRot[1][1];
	yaxis.z = kRot[2][1];

	zaxis.x = kRot[0][2];
	zaxis.y = kRot[1][2];
	zaxis.z = kRot[2][2];
}


OQuaternion OQuaternion::Exp () const
{
	// If q = A*(x*i+y*j+z*k) where (x,y,z) is unit length, then
	// exp(q) = cos(A)+sin(A)*(x*i+y*j+z*k).  If sin(A) is near zero,
	// use exp(q) = cos(A)+A*(x*i+y*j+z*k) since A/sin(A) has limit 1.

	float fAngle ( sqrtf(x*x+y*y+z*z) );
	float fSin = sinf(fAngle);

	OQuaternion kResult;
	kResult.w = cosf(fAngle);

	if ( fabsf(fSin) >= 1e-03f )
	{
		float fCoeff = fSin/(fAngle);
		kResult.x = fCoeff*x;
		kResult.y = fCoeff*y;
		kResult.z = fCoeff*z;
	}
	else
	{
		kResult.x = x;
		kResult.y = y;
		kResult.z = z;
	}

	return kResult;
}
//-----------------------------------------------------------------------
OQuaternion OQuaternion::Log () const
{
	// If q = cos(A)+sin(A)*(x*i+y*j+z*k) where (x,y,z) is unit length, then
	// log(q) = A*(x*i+y*j+z*k).  If sin(A) is near zero, use log(q) =
	// sin(A)*(x*i+y*j+z*k) since sin(A)/A has limit 1.

	OQuaternion kResult;
	kResult.w = 0.0;

	if ( fabsf(w) < 1.0 )
	{
		float fAngle ( acosf(w) );
		float fSin = sinf(fAngle);
		if ( fabsf(fSin) >= 1e-03f )
		{
			float fCoeff = fAngle/fSin;
			kResult.x = fCoeff*x;
			kResult.y = fCoeff*y;
			kResult.z = fCoeff*z;
			return kResult;
		}
	}

	kResult.x = x;
	kResult.y = y;
	kResult.z = z;

	return kResult;
}

//-----------------------------------------------------------------------
OQuaternion OQuaternion::Slerp (float fT, const OQuaternion& rkP,
							  const OQuaternion& rkQ, bool shortestPath)
{
	float fCos = rkP.DotProduct(rkQ);
	float fAngle ( acosf(fCos) );

	if ( fabsf(fAngle) < 1e-03f )
		return rkP;

	float fSin = sinf(fAngle);
	float fInvSin = 1.0f/fSin;
	float fCoeff0 = sinf((1.0f-fT)*fAngle)*fInvSin;
	float fCoeff1 = sinf(fT*fAngle)*fInvSin;
	// Do we need to invert rotation?
	if (fCos < 0.0f && shortestPath)
	{
		fCoeff0 = -fCoeff0;
		// taking the complement requires renormalisation
		OQuaternion t(fCoeff0*rkP + fCoeff1*rkQ);
		t.Normalize();
		return t;
	}
	else
	{
		return fCoeff0*rkP + fCoeff1*rkQ;
	}
}
//-----------------------------------------------------------------------
//ms_fEpsilon = 1e-03f;
OQuaternion OQuaternion::SlerpExtraSpins (float fT,
										const OQuaternion& rkP, const OQuaternion& rkQ, int iExtraSpins)
{
	float fCos = rkP.DotProduct(rkQ);
	float fAngle ( acosf(fCos) );

	if ( fabsf(fAngle) < 1e-03f )
		return rkP;

	float fSin = sinf(fAngle);
	float fPhase ( PI*iExtraSpins*fT );
	float fInvSin = 1.0f/fSin;
	float fCoeff0 = sinf((1.0f-fT)*fAngle - fPhase)*fInvSin;
	float fCoeff1 = sinf(fT*fAngle + fPhase)*fInvSin;
	return fCoeff0*rkP + fCoeff1*rkQ;
}
//-----------------------------------------------------------------------
void OQuaternion::Intermediate (const OQuaternion& rkQ0,
							   const OQuaternion& rkQ1, const OQuaternion& rkQ2,
							   OQuaternion& rkA, OQuaternion& rkB)
{
	// assert:  q0, q1, q2 are unit quaternions

	OQuaternion kQ0inv = rkQ0.UnitInverse();
	OQuaternion kQ1inv = rkQ1.UnitInverse();
	OQuaternion rkP0 = kQ0inv*rkQ1;
	OQuaternion rkP1 = kQ1inv*rkQ2;
	OQuaternion kArg = 0.25*(rkP0.Log()-rkP1.Log());
	OQuaternion kMinusArg = -kArg;

	rkA = rkQ1*kArg.Exp();
	rkB = rkQ1*kMinusArg.Exp();
}
//-----------------------------------------------------------------------
OQuaternion OQuaternion::Squad (float fT,
							  const OQuaternion& rkP, const OQuaternion& rkA,
							  const OQuaternion& rkB, const OQuaternion& rkQ, bool shortestPath)
{
	float fSlerpT = 2.0f*fT*(1.0f-fT);
	OQuaternion kSlerpP = Slerp(fT, rkP, rkQ, shortestPath);
	OQuaternion kSlerpQ = Slerp(fT, rkA, rkB);
	return Slerp(fSlerpT, kSlerpP ,kSlerpQ);
}