//////////////////////////////////////////////////////////////////////////
//File : Only QUATERNION( Only Math Lib)
//Author : Zipxin  
//E-mail: zipxin@163.com
//Project : OnlyGameEngine
//////////////////////////////////////////////////////////////////////////
#ifndef _ONLY_QUATERNION_H_
#define _ONLY_QUATERNION_H_

#if _MSC_VER > 1000
#pragma once
#endif 

#include "../OInclude/Common/OnlyGameDefine.h"

#include "../OInclude/Math/OMatrix4x4.h"
#include "../OInclude/Math/OVector4.h"

//w 绕着 v向量旋转的量（x,y,z）
//q = （cos（w/2）,sin(w/2)*v）
//q = cos(w/2) , (sin(w/2) * x, sin(w/2) * y, sin(w/2) * z)
class OQuaternion
{
public:
	float w;
	float x;
	float y;
	float z;

/// Identity quaternion.
	static const OQuaternion IDENTITY;
    static const OQuaternion ZERO;
	

	OQuaternion() :
		w(1.0f),
		x(0.0f),
		y(0.0f),
		z(0.0f)
	{
	}

	OQuaternion(const OQuaternion& quat) :
		w(quat.w),
		x(quat.x),
		y(quat.y),
		z(quat.z)
	{
	}

	OQuaternion(float32 w, float32 x, float32 y, float32 z) :
		w(w),
		x(x),
		y(y),
		z(z)
	{
	}

	OQuaternion(const float32* data) :
		w(data[0]),
		x(data[1]),
		y(data[2]),
		z(data[3])
	{
	}


	/// Construct from an angle (in degrees) and axis.
	OQuaternion(float32 angle, const OVector3& axis)
	{
		FromAngleAxis(angle, axis);
	}

	/// 从欧拉角进行构造 (in degrees.)
	OQuaternion(float32 x, float32 y, float32 z)
	{
		FromEulerAngles(x, y, z);
	}

	/// Construct from the rotation difference between two direction vectors.
	OQuaternion(const OVector3& start, const OVector3& end)
	{
		FromRotationTo(start, end);
	}

	/// Construct from orthonormal axes.
	OQuaternion(const OVector3& xAxis, const OVector3& yAxis, const OVector3& zAxis)
	{
		FromAxes(xAxis, yAxis, zAxis);
	}

	/// Construct from a rotation matrix.
	OQuaternion(const OMatrix3x3& matrix)
	{
		FromRotationMatrix(matrix);
	}

	/// Assign from another quaternion.
	OQuaternion& operator = (const OQuaternion& rhs)
	{
		w = rhs.w;
		x = rhs.x;
		y = rhs.y;
		z = rhs.z;
		return *this;
	}

	/// Add-assign a quaternion.
	OQuaternion& operator += (const OQuaternion& rhs)
	{
		w += rhs.w;
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
		return *this;
	}

	/// Multiply-assign a scalar.
	OQuaternion& operator *= (float32 rhs)
	{
		w *= rhs;
		x *= rhs;
		y *= rhs;
		z *= rhs;
		return *this;
	}

	bool operator == (const OQuaternion& rhs) const { return w == rhs.w && x == rhs.x && y == rhs.y && z == rhs.z; }
	bool operator != (const OQuaternion& rhs) const { return w != rhs.w || x != rhs.x || y != rhs.y || z != rhs.z; }
	/// Multiply with a scalar.
	OQuaternion operator * (float32 rhs) const { return OQuaternion(w * rhs, x * rhs, y * rhs, z * rhs); }
	friend inline OQuaternion operator* (float fScalar, const OQuaternion& lhs)
	{
		return OQuaternion(fScalar * lhs.w,fScalar*lhs.x,fScalar*lhs.y,
							fScalar*lhs.z);
	}
	
	/// Return negation.
	OQuaternion operator - () const { return OQuaternion(-w, -x, -y, -z); }
	/// Add a quaternion.
	OQuaternion operator + (const OQuaternion& rhs) const { return OQuaternion(w + rhs.w, x + rhs.x, y + rhs.y, z + rhs.z); }
	/// Subtract a quaternion.
	OQuaternion operator - (const OQuaternion& rhs) const { return OQuaternion(w - rhs.w, x - rhs.x, y - rhs.y, z - rhs.z); }

	/// Q = Q1 * Q2
	/// w =	w1 * w2 - x1 * x2 - y1 * y2 - z1 * z2
	/// x = w1 * x2 + x1 * w2 + y1 * z2 - z1 * y2
	/// y = w1 * y2 + y1 * w2 + z1 * x2 - x1 * z2
	/// z = w1 * z2 + z1 * w2 + x1 * y2 - y1 * x2
	OQuaternion operator * (const OQuaternion& rhs) const
	{
		return OQuaternion(
			w * rhs.w - x * rhs.x - y * rhs.y - z * rhs.z,
			w * rhs.x + x * rhs.w + y * rhs.z - z * rhs.y,
			w * rhs.y + y * rhs.w + z * rhs.x - x * rhs.z,
			w * rhs.z + z * rhs.w + x * rhs.y - y * rhs.x
			);
	}

	/// Multiply a Vector3.
	OVector3 operator * (const OVector3& rhs) const
	{
		OVector3 qVec(x,y,z);
		OVector3 cross1( Vec3_CrossProduct(qVec, rhs));
		OVector3 cross2( Vec3_CrossProduct(qVec, cross1));

		return rhs + 2.0f * (cross1 * w + cross2);
	}

	/// Define from an angle (in degrees) and axis.
	void FromAngleAxis(float angle, const OVector3& axis);
	/// Define from Euler angles (in degrees.)
	void FromEulerAngles(float x, float y, float z);
	/// Define from the rotation difference between two direction vectors.
	void FromRotationTo(const OVector3& start, const OVector3& end);
	/// Define from orthonormal axes.
	void FromAxes(const OVector3& xAxis, const OVector3& yAxis, const OVector3& zAxis);
	
	void FromAxes (const OVector3* akAxis);
	/// Define from a rotation matrix.
	void FromRotationMatrix(const OMatrix3x3& matrix);
	/// Define from a direction to look in and an up direction
	void FromLookRotation(const OVector3& direction, const OVector3& up = OVector3::UP);

	/// Normalize to unit length.
	void Normalize()
	{
		float lenSquared = LengthSquared();
		if (!OEquals(lenSquared, 1.0f) && lenSquared > 0.0f)
		{
			float invLen = 1.0f / sqrtf(lenSquared);
			w *= invLen;
			x *= invLen;
			y *= invLen;
			z *= invLen;
		}
	}

	/// Return normalized to unit length.
	OQuaternion Normalized() const
	{
		float lenSquared = LengthSquared();
		if (!OEquals(lenSquared, 1.0f) && lenSquared > 0.0f)
		{
			float invLen = 1.0f / sqrtf(lenSquared);
			return *this * invLen;
		}
		else
			return *this;
	}

	/// Return inverse.
	OQuaternion Inverse() const
	{
		float lenSquared = LengthSquared();
		if (lenSquared == 1.0f)
			return Conjugate();
		else if (lenSquared >= EPSILON)
		{
			float fInvNorm = 1.0f / lenSquared;
			return Conjugate() * fInvNorm;
		}
		else
			return ZERO;
	}

	void ToAngleRadianAxis (float& rfRadian, OVector3& rkAxis) const;
	// in degree
	inline void ToAngleDegreeAxis (float& dAngle, OVector3& rkAxis) const {
		float rRadian;
		ToAngleRadianAxis ( rRadian, rkAxis );
		dAngle = RAD_TO_DEG * rRadian;
	}
	void ToAxes (OVector3* akAxis) const;
	void ToAxes (OVector3& xAxis, OVector3& yAxis, OVector3& zAxis) const;
	/// Get the local x-axis
	OVector3 xAxis(void) const;
	/// Get the local y-axis
	OVector3 yAxis(void) const;
	/// Get the local z-axis
	OVector3 zAxis(void) const;


	OQuaternion UnitInverse () const;  
	OQuaternion Exp () const;
	OQuaternion Log () const;

	// spherical linear interpolation
	static OQuaternion Slerp (float fT, const OQuaternion& rkP,
		const OQuaternion& rkQ, bool shortestPath = false);

	static OQuaternion SlerpExtraSpins (float fT,
		const OQuaternion& rkP, const OQuaternion& rkQ,
		int iExtraSpins);

	// setup for spherical quadratic interpolation
	static void Intermediate (const OQuaternion& rkQ0,
		const OQuaternion& rkQ1, const OQuaternion& rkQ2,
		OQuaternion& rka, OQuaternion& rkB);

	// spherical quadratic interpolation
	static OQuaternion Squad (float fT, const OQuaternion& rkP,
		const OQuaternion& rkA, const OQuaternion& rkB,
		const OQuaternion& rkQ, bool shortestPath = false);



	/// 返回长度的平方
	float LengthSquared() const { return w * w + x * x + y * y + z * z; }
	/// Calculate dot product.
	float DotProduct(const OQuaternion& rhs) const { return w * rhs.w + x * rhs.x + y * rhs.y + z * rhs.z; }
	/// Test for equality with another quaternion with epsilon.
	bool Equals(const OQuaternion& rhs) const { return OEquals(w, rhs.w) && OEquals(x, rhs.x) && OEquals(y, rhs.y) && OEquals(z, rhs.z); }
	/// 返回共轭四元数
	OQuaternion Conjugate() const { return OQuaternion(w, -x, -y, -z); }

	/// Return Euler angles in degrees.
	OVector3 EulerAngles() const;
	/// Return yaw angle in degrees.
	float YawAngle() const;
	/// Return pitch angle in degrees.
	float PitchAngle() const;
	/// Return roll angle in degrees.
	float RollAngle() const;
	/// Return the rotation matrix that corresponds to this quaternion.
	OMatrix3x3 RotationMatrix() const;
	/// Spherical interpolation with another quaternion.
	OQuaternion Slerp(OQuaternion rhs, float t) const;
	/// Normalized linear interpolation with another quaternion.
	OQuaternion Nlerp(OQuaternion rhs, float t, bool shortestPath = false) const;
	/// Return float data.
	const float* Data() const { return &w; }

	/// Return whether is NaN.
	//bool IsNaN() const { return IsNaN(w) || IsNaN(x) || IsNaN(y) || IsNaN(z); }

	/// Return as string.


	inline friend std::ostream& operator <<
		( std::ostream& o, const OQuaternion& q )
	{
		o << "Quaternion (" << q.x << ", " << q.y << ", " << q.z << ", " << q.w << ")";
		return o;
	}

	inline const char* ToCString() const
	{
		char *buf = new char[128];
		memset(buf, 0 , 128);
		sprintf_s(buf, 128, "Quaternion: (%5.2f,%5.2f,%5.2f,%5.2f)\n", x, y, z, w);
		return buf;
	}

	inline const wchar_t* ToWString() const
	{
		wchar_t *buf = new wchar_t[128];
		memset(buf, 0 , 128);
		swprintf_s(buf, 128, L"Quaternion: (%5.2f,%5.2f,%5.2f,%5.2f)\n", x, y, z, w);
		return buf;
	}
};



#endif/*File Is Over*/