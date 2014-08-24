//////////////////////////////////////////////////////////////////////////
//File : Only Ray ( Only Math Lib)
//Author : Zipxin  [China]
//Project : OnlyGameEngine
//E-mail: zipxin@163.com
//////////////////////////////////////////////////////////////////////////
#ifndef _ONLY_RAY_H_
#define _ONLY_RAY_H_

#if _MSC_VER > 1000
#pragma once
#endif 

#include "../OInclude/Common/OnlyGameDefine.h"
#include "../OInclude/Math/OVector3.h"

class OBoundingBox;
class OFrustum;
class OPlane;
class OSphere;
class OMatrix3x4;

class ORay
{
public:
	// ���ߵ����
	OVector3 m_origin;
	// ���ߵķ���
	OVector3 m_direction;
	ORay()
	{
	}

	/// ͨ�����ߵ����ͷ�����г�ʼ��
	ORay(const OVector3& origin, const OVector3& direction)
	{
		Init(origin, direction);
	}

	ORay(const ORay& ray) :
		m_origin(ray.m_origin),
		m_direction(ray.m_direction)
	{
	}

	ORay& operator = (const ORay& rhs)
	{
		m_origin = rhs.m_origin;
		m_direction = rhs.m_direction;
		return *this;
	}

	bool operator == (const ORay& rhs) const { return m_origin == rhs.m_origin && m_direction == rhs.m_direction; }
	bool operator != (const ORay& rhs) const { return m_origin != rhs.m_origin || m_direction != rhs.m_direction; }

	//
	inline OVector3 operator*(float32 t) const { 
		return GetRayPoint(t);
	};

	void Init(const OVector3& origin, const OVector3& direction)
	{
		m_origin = origin;
		m_direction = direction.Nomarlized();
	}

	/** �õ���ǰ�����Ͼ���������Ϊt�������� */
	inline OVector3 GetRayPoint(float32 t) const { 
		return OVector3(m_origin + (m_direction * t));
	}

	/// ���������ϵ�ͶӰ
	OVector3 Project(const OVector3& point) const
	{
		OVector3 offset = point - m_origin;
		return m_origin +  Vec3_Dotf( offset, m_direction ) * m_direction;
	}

	/// ���ص㵽���ߵľ���.
	float32 Distance(const OVector3& point) const
	{
		OVector3 projected = Project(point);
		return (point - projected).Length();
	}

	/// ������һ����������ĵ�
	OVector3 ClosestPoint(const ORay& ray) const;
	//�ཻ���
	float HitDistance(const OPlane& plane) const;
	float HitDistance(const OBoundingBox& box) const;
	float HitDistance(const OFrustum& frustum, bool solidInside = true) const;
	float HitDistance(const OSphere& sphere) const;
	float HitDistance(const OVector3& v0, const OVector3& v1, const OVector3& v2) const;
	float HitDistance(const OVector3& v0, const OVector3& v1, const OVector3& v2, OVector3* outNormal) const;
	float HitDistance(const void* vertexData, unsigned vertexSize, unsigned vertexStart, unsigned vertexCount, OVector3* outNormal = 0) const;
	float HitDistance(const void* vertexData, unsigned vertexSize, const void* indexData, unsigned indexSize, unsigned indexStart, unsigned indexCount, OVector3* outNormal = 0) const;
	
	
	bool InsideGeometry(const void* vertexData, unsigned vertexSize, unsigned vertexStart, unsigned vertexCount) const;
	bool InsideGeometry(const void* vertexData, unsigned vertexSize, const void* indexData, unsigned indexSize, unsigned indexStart, unsigned indexCount) const;
	
	ORay Transformed(const OMatrix3x4& transform) const;

	inline const char* ToCString() const 
	{
		char *buf = new char[128];
		memset(buf, 0 , 128);
		sprintf_s(buf, 128, "RAY: ( origin: %5.2f,%5.2f,%5.2f direction: %5.2f,%5.2f,%5.2f)\n", 
									m_origin.x, m_origin.y, m_origin.z,
									m_direction.x, m_direction.y, m_direction.z);
		return buf;
	}

	inline const wchar_t* ToWString() const 
	{
		wchar_t *buf = new wchar_t[128];
		memset(buf, 0 , 128);
		swprintf_s(buf, 128, L"RAY: ( origin: %5.2f,%5.2f,%5.2f direction: %5.2f,%5.2f,%5.2f)\n", 
										m_origin.x, m_origin.y, m_origin.z,
										m_direction.x, m_direction.y, m_direction.z);
		return buf;
	}

	inline friend std::ostream& operator <<	( std::ostream& o, const ORay& v )
	{
		//o <<"RAY: ("<<v.min.x<<","<<v.min.y<<","<<v.max.x<<","<<v.max.y<<")";
		return o;
	}

	inline void StoreToArrayf(float32 *p) const 
	{
		p[0] = m_origin.x;
		p[1] = m_origin.y;
		p[2] = m_origin.z;
		p[3] = m_direction.x;
		p[4] = m_direction.y;
		p[5] = m_direction.z;
	}


};


// 	/** �жϹ��������ƽ��p�Ƿ��ཻ
// 	 *	@returns [pair<bool, float>] : ��һ������ֵ��ʾ�Ƿ��ཻ, �ڶ�������ֵ����㵽����ľ���
// 	 */
// 	inline std::pair<bool, float> Intersects(const Plane& p) const
// 	{
// 		return Math::Intersects(*this, p);
// 	}
// 
// 	/** �жϹ������������p�Ƿ��ཻ
// 	 *	@returns [pair<bool, float>] : ��һ������ֵ��ʾ�Ƿ��ཻ, �ڶ�������ֵ����㵽����ľ���
// 	 */
// 	inline std::pair<bool, float> Intersects(const Sphere& s) const
// 	{
// 		return Math::Intersects(*this, s);
// 	}
#endif/*File Is Over*/