//////////////////////////////////////////////////////////////////////////
//File : Only Sphere ( Only Math Lib)
//Author : Zipxin  [China]
//E-mail: zipxin@163.com
//Project : OnlyGameEngine
//////////////////////////////////////////////////////////////////////////
#ifndef _ONLY_SPHERE_H_
#define _ONLY_SPHERE_H_

#if _MSC_VER > 1000
#pragma once
#endif 

#include "../OInclude/Common/OnlyGameDefine.h"
#include "../OInclude/Math/OMathUtil.h"

#include <stdio.h>

#include "../OInclude/Math/OVector3.h"



class OPolyhedron;
class OBoundingBox;
class OFrustum;

class OSphere
{
public:
	//Բ��
	OVector3 m_center;
	//�뾶
	float m_radius;
	//�Ƿ��ʼ����־
	bool m_isInited;

	OSphere() :
		m_center(OVector3::ZERO),
		m_radius(0.0f),
		m_isInited(false)
	{
	}


	OSphere(float32 x, float32 y, float32 z, float32 r) :
		m_center(x,y,z),
		m_radius(r),
		m_isInited(true)
	{
	}

	OSphere(const OSphere& sphere) :
		m_center(sphere.m_center),
		m_radius(sphere.m_radius),
		m_isInited(sphere.m_isInited)
	{
	}

	OSphere(const OVector3& center, float radius) :
		m_center(center),
		m_radius(radius),
		m_isInited(true)
	{
	}

	OSphere(const OVector3* vertices, unsigned count) :
		m_isInited(false)
	{
		Init(vertices, count);
	}

	OSphere(const OBoundingBox& box) :
		m_isInited(false)
	{
		Init(box);
	}

	OSphere(const OFrustum& frustum) :
		m_isInited(false)
	{
		Init(frustum);
	}

	OSphere(const OPolyhedron& poly) :
		m_isInited(false)
	{
		Init(poly);
	}

	OSphere& operator = (const OSphere& rhs)
	{
		m_center = rhs.m_center;
		m_radius = rhs.m_radius;
		m_isInited = rhs.m_isInited;
		return *this;
	}

	bool operator == (const OSphere& rhs) const { return m_center == rhs.m_center && m_radius == rhs.m_radius; }
	bool operator != (const OSphere& rhs) const { return m_center != rhs.m_center || m_radius != rhs.m_radius; }

	void Init(const OSphere& sphere)
	{
		Init(sphere.m_center, sphere.m_radius);
	}

	void Init(const OVector3& center, float radius)
	{
		m_center = center;
		m_radius = radius;
		m_isInited = true;
	}

	void Init(const OVector3* vertices, unsigned count);
	void Init(const OBoundingBox& box);
	void Init(const OFrustum& frustum);
	void Init(const OPolyhedron& poly);

	/// ?????
	void Merge(const OVector3& point)
	{
		if (!m_isInited)
		{
			m_center = point;
			m_radius = 0.0f;
			m_isInited = true;
			return;
		}

		OVector3 offset = point - m_center;
		float32 dist = offset.Length();

		if (dist > m_radius)
		{
			float32 half = (dist - m_radius) * 0.5f;
			m_radius += half;
			m_center += (half / dist) * offset;
		}
	}

	void Merge(const OVector3* vertices, unsigned count);
	void Merge(const OBoundingBox& box);
	void Merge(const OFrustum& frustum);
	void Merge(const OPolyhedron& poly);
	void Merge(const OSphere& sphere);

	void Clear()
	{
		m_center = OVector3::ZERO;
		m_radius = 0.0f;
		m_isInited = false;
	}

	/// ���Ե�����֮��Ĺ�ϵ
	Intersection IsInside(const OVector3& point) const
	{
		float distSquared = (point - m_center).LengthNotSqrt();
		if (distSquared < m_radius * m_radius)
			return INSIDE;
		else
			return OUTSIDE;
	}

	Intersection IsInside(const OSphere& sphere) const
	{
		float dist = (sphere.m_center - m_center).Length();
		if (dist >= sphere.m_radius + m_radius)
			return OUTSIDE;
		else if (dist + sphere.m_radius < m_radius)
			return INSIDE;
		else
			return INTERSECTS;
	}

	/// ������һ�����뵱ǰ��Ĺ�ϵ
	Intersection IsInsideFast(const OSphere& sphere) const
	{
		float32 distSquared = (sphere.m_center - m_center).LengthNotSqrt();
		float32 combined = sphere.m_radius + m_radius;

		if (distSquared >= combined * combined)
			return OUTSIDE;
		else
			return INSIDE;
	}

	//���԰�Χ������֮��Ĺ�ϵ
	Intersection IsInside(const OBoundingBox& box) const;
	Intersection IsInsideFast(const OBoundingBox& box) const;

	/// ���ص㵽��֮��ľ��룬���������ڲ���Ϊ0
	float32 Distance(const OVector3& point) const { return OMax2((point - m_center).Length() - m_radius, 0.0f); }


	inline void Offset(const OVector3 &offset)
	{
		m_center += offset;
	}



	inline void Expand(float32 n)
	{
		m_radius += n;
	}

	//------Display
	inline const char* ToCString() const 
	{
		char *buf = new char[128];
		memset(buf, 0 , 128);
		sprintf_s(buf, 128, "SPHERE: ( center: %5.2f,%5.2f,%5.2f radius:%5.2f)\n", m_center.x, m_center.y, m_center.z, m_radius);
		return buf;
	}

	inline const wchar_t* ToWString() const 
	{
		wchar_t *buf = new wchar_t[128];
		memset(buf, 0 , 128);
		swprintf_s(buf, 128, L"SPHERE: ( center: %5.2f,%5.2f,%5.2f radius:%5.2f)\n", m_center.x, m_center.y, m_center.z, m_radius);
		return buf;
	}

	inline void StoreToArrayf(float32 *p) const 
	{
		p[0] = m_center.x;
		p[1] = m_center.y;
		p[2] = m_center.z;
		p[3] = m_radius;
	}

	/** ����<<����������Խ���ά��������Vector2(x,y)�ĸ�ʽ��� */
	inline friend std::ostream& operator <<	( std::ostream& o, const OSphere& v )
	{
		o <<"SPHERE: ( center: "<<v.m_center.x<<","<<v.m_center.y<<","<<v.m_center.z<<" radius:"<<v.m_radius<<")";
		return o;
	}

// 	/** �ж�Բ�Ƿ���������ཻ */
// 	bool Intersects(const Frustum& frustum) const
// 	{ return Math::Intersects(*this, frustum); }


// 	inline void Sphere::Normalize()
// 	{
// 		radius = absoluteValue(radius);
// 	}
//  δ���õ�������֯����
// 	union
// 	{
// 		struct
// 		{
// 			float	radius;
// 			OVector3 center;
// 		};
// 		struct
// 		{
// 			OCircle circle;
// 			float z;
// 		};
// 	};
};


#endif /*File Is Over*/