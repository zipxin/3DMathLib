//////////////////////////////////////////////////////////////////////////
//File : Only Plane ( Only Math Lib)
//Author : Zipxin  [China]
//Project : OnlyGameEngine
//E-mail: zipxin@163.com
//////////////////////////////////////////////////////////////////////////
#ifndef _ONLY_PLANE_H_
#define _ONLY_PLANE_H_

#if _MSC_VER > 1000
#pragma once
#endif 
/*  3D空间中的平面.
		3D空间中的平面方程如下所示
		Ax + By + Cz + D = 0
		其中Vector3（A,B,C）是平面的法向，D是原点到平面的距离
*/

#include "../OInclude/Common/OnlyGameDefine.h"

#include "../OInclude/Math/OMathUtil.h"
#include <stdio.h>

#include "../OInclude/Math/OVector3.h"
#include "../OInclude/Math/OVector4.h"

#include "../OInclude/Math/OMatrix3x4.h"
#include "../OInclude/Math/OMatrix3x3.h"
#include "../OInclude/Math/OMatrix4x4.h"
/*	OPlane
------------------------------------------------------------------------------------------
	
	A OPlane in 3D Space represented in point-normal 
	form (Ax + By + Cz + D = 0).

	The convention for the distance constant D is:

	D = -(A, B, C) dot (X, Y, Z)

------------------------------------------------------------------------------------------
*/
class OPlane
{
public:
	OVector3 normal;
	float32  d;

	enum PlaneSide
	{
		ON_THE_PLANE, //在平面上
		POSITIVE_SIDE,//在平面正面
		NEGATIVE_SIDE //在平面负面
	};
public:
	//构造函数=================================================
	OPlane():normal(OVector3::ZERO), d(0.0f){}

	//拷贝构造函数
	OPlane(const OPlane& plane):normal(plane.normal), d(plane.d) {}

	OPlane(const OVector3& v0, const OVector3& v1, const OVector3& v2)
	{
		Init(v0, v1, v2);
	}

	OPlane(const OVector3& normal, const OVector3& point)
	{
		Init(normal, point);
	}

	OPlane(const OVector4& plane)
	{
		Init(plane);
	}

	//初始化===========================================
	void Init(const OVector3& v0, const OVector3& v1, const OVector3& v2)
	{
		OVector3 dist1 = v1 - v0;
		OVector3 dist2 = v2 - v0;

		Init(Vec3_CrossProduct(dist1, dist2), v0);
	}

	void Init(const OVector3& _normal, const OVector3& point)
	{
		normal = _normal;
		normal.Nomarlize();
		d = -Vec3_Dotf(normal, point);
	}

	void Init(const OVector4& plane)
	{
		normal = OVector3(plane.GetXf(), plane.GetYf(), plane.GetZf());
		d = plane.GetWf();
	}


	float32 Distance(const OVector3& point) const 
	{ 
		return Vec3_Dotf(normal, point) + d;
	}

	OVector3 Reflect(const OVector3& direction) const 
	{
		return direction - ( 2.0f * Vec3_Dotf(normal,direction) * normal );
	}


	void Transform(const OMatrix3x3& transform);
	void Transform(const OMatrix3x4& transform);
	void Transform(const OMatrix4x4& transform);


	OMatrix3x4 ReflectionMatrix() const;
	OPlane Transformed(const OMatrix3x3& transform) const;
	OPlane Transformed(const OMatrix3x4& transform) const;
	OPlane Transformed(const OMatrix4x4& transform) const;
	OVector4 ToVector4() const { return OVector4(normal.x,normal.y,normal.z, d); }
/** 判定rkPoint在平面的那一侧，对于平面的侧定义了正，负，无，分别表示与法向量同向，反向，在平面上 */
	PlaneSide GetSide(OVector3 point);

	inline void Normalize()
	{
		float32 mag = normal.Length();
		float32 inv_mag = 1.0f/mag;

		normal.x *= inv_mag;
		normal.y *= inv_mag;
		normal.z *= inv_mag;
		d *= inv_mag;
	}


	//----------------------------------------------------------------------------------------
	//
	//	Given a 3D point in space, project the point onto this plane along the plane normal
	//
	//-------------------------------------------------------------------------------------://
	inline OVector3 ProjectPointToPlane(const OVector3& Point)const
	{
		float distance = Distance(Point);
		OVector3 result(
			(normal.x * -distance) + Point.x,
			(normal.y * -distance) + Point.y,
			(normal.z * -distance) + Point.z);

		return(result);
	}


	//:	solveForX
	//----------------------------------------------------------------------------------------
	//
	//	Given Z and Y, solve for X on the plane 
	//
	//-------------------------------------------------------------------------------------://
	inline float32 SolveForX(float32 Y, float32 Z)const
	{
		//Ax + By + Cz + D = 0
		// Ax = -(By + Cz + D)
		// x = -(By + Cz + D)/A

		if (normal.x)
		{
			return ( -(normal.y*Y + normal.z*Z + d) / normal.x );
		}

		return (0.0f);
	}

	//:	solveForY
	//----------------------------------------------------------------------------------------
	//
	//	Given X and Z, solve for Y on the plane 
	//
	//-------------------------------------------------------------------------------------://
	inline float32 SolveForY(float32 X, float32 Z)const
	{
		//Ax + By + Cz + D = 0
		// By = -(Ax + Cz + D)
		// y = -(Ax + Cz + D)/B

		if (normal.y)
		{
			return ( -(normal.x*X + normal.z*Z + d) / normal.y );
		}

		return (0.0f);
	}

	//:	solveForZ
	//----------------------------------------------------------------------------------------
	//
	//	Given X and Y, solve for Z on the plane 
	//
	//-------------------------------------------------------------------------------------://
	inline float32 SolveForZ(float32 X, float32 Y)const
	{
		//Ax + By + Cz + D = 0
		// Cz = -(Ax + By + D)
		// z = -(Ax + By + D)/C

		if (normal.z)
		{
			return ( -(normal.x*X + normal.y*Y + d) / normal.z);
		}

		return (0.0f);
	}

	/** 重载运算符 << 输出平面 */
	inline friend std::ostream& operator<< (std::ostream& o, OPlane& p)
	{
		o << "OPlane(normal=" << p.normal << ", d=" << p.d << ")";
		return o;
	}

	inline const char* ToCString() const 
	{
		char *buf = new char[128];
		memset(buf, 0 , 128);
		sprintf_s(buf, 128, "Plane: (%5.2f,%5.2f,%5.2f,%5.2f)\n", normal.x, normal.y, normal.z, d);
		return buf;
	}

	inline const wchar_t* ToWString() const 
	{
		wchar_t *buf = new wchar_t[128];
		memset(buf, 0 , 128);
		swprintf_s(buf, 128, L"Plane: (%5.2f,%5.2f,%5.2f,%5.2f)\n", normal.x, normal.y, normal.z, d);
		return buf;
	}



	inline void StoreToArrayf(float32 *p) const 
	{
		p[0] = normal.x;
		p[1] = normal.y;
		p[2] = normal.z;
		p[3] = d;
	}

	static const OPlane UP;
};

// inline void cPlane3d::xForm(const cMatrix4x4& matrix)
// {
// 	D3DXVec3TransformNormal(&normal, &normal, &matrix);
// 	normal.normalize();
// 
// 	cVector3 point = normal * distance;
// 	D3DXVec3TransformCoord(&point, &point, &matrix);
// 	distance = -normal.dotProduct(point);
// }



#endif /*File Is Over*/