//////////////////////////////////////////////////////////////////////////
//File : Only BoundingBox ( Only Math Lib)
//Author : Zipxin  [China]
//E-mail: zipxin@163.com
//Project : OnlyGameEngine
//////////////////////////////////////////////////////////////////////////
#ifndef _ONLY_BOUNDINGBOX_H_
#define _ONLY_BOUNDINGBOX_H_

#if _MSC_VER > 1000
#pragma once
#endif 

#include "../OInclude/Common/OnlyGameDefine.h"
#include "../OInclude/Math/OVector3.h"

#include "../OInclude/Math/ORect.h"

class OSphere;
class OPolyhedron;
class OFrustum;
class OMatrix3x4;
class OMatrix3x3;

class OBoundingBox
{
public:

	
	OVector3 m_min;
	OVector3 m_max;
	bool   m_isInit;

	OBoundingBox() :
		m_min(OVector3::ZERO),
		m_max(OVector3::ZERO),
		m_isInit(false){}

	OBoundingBox(const OBoundingBox& box) :
		m_min(box.m_min),
		m_max(box.m_max),
		m_isInit(box.m_isInit){}

	OBoundingBox(const ORect& rect) :
		m_min(OVector3(rect.min.x, rect.min.y, 0.0f)),
		m_max(OVector3(rect.max.x, rect.max.y, 0.0f)),
		m_isInit(true)
	{
	}

	OBoundingBox(const OVector3& min, const OVector3& max) :
		m_min(min),
		m_max(max),
		m_isInit(true)
	{
	}

	OBoundingBox(float32 min, float32 max) :
		m_min(OVector3(min, min, min)),
		m_max(OVector3(max, max, max)),
		m_isInit(true)
	{
	}

	OBoundingBox(const OVector3* vertices, unsigned count) :
	m_isInit(false)
	{
		Init(vertices, count);
	}

	OBoundingBox(const OFrustum& frustum) :
	m_isInit(false)
	{
		Init(frustum);
	}

	OBoundingBox(const OPolyhedron& poly) :
	m_isInit(false)
	{
		Init(poly);
	}

	OBoundingBox(const OSphere& sphere) :
	m_isInit(false)
	{
		Init(sphere);
	}

	OBoundingBox& operator = (const OBoundingBox& rhs)
	{
		m_min = rhs.m_min;
		m_max = rhs.m_max;
		m_isInit = rhs.m_isInit;
		return *this;
	}

	/// Assign from a Rect, with the Z dimension left zero.
	OBoundingBox& operator = (const ORect& rhs)
	{
		m_min = OVector3(rhs.min.x, rhs.min.y, 0.0f);
		m_max = OVector3(rhs.max.x, rhs.max.y, 0.0f);
		m_isInit = true;
		return *this;
	}

	bool operator == (const OBoundingBox& rhs) const { return (m_min == rhs.m_min && m_max == rhs.m_max); }
	bool operator != (const OBoundingBox& rhs) const { return (m_min != rhs.m_min || m_max != rhs.m_max); }

	void Init(const OBoundingBox& box)
	{
		Init(box.m_min, box.m_max);
	}

	void Init(const ORect& rect)
	{
		Init(OVector3(rect.min.x, rect.min.y, 0.0f), OVector3(rect.max.x, rect.max.y, 0.0f));
	}

	void Init(const OVector3& min, const OVector3& max)
	{
		m_min = min;
		m_max = max;
		m_isInit = true;
	}

	void Init(float32 min, float32 max)
	{
		m_min = OVector3(min, min, min);
		m_max = OVector3(max, max, max);
		m_isInit = true;
	}

	void Init(const OVector3& point)
	{
		m_min = m_max = point;
		m_isInit = true;
	}

	void Merge(const OVector3& point)
	{
		if (!m_isInit)
		{
			m_min = m_max = point;
			m_isInit = true;
			return;
		}

		if (point.x < m_min.x)
			m_min.x = point.x;
		if (point.y < m_min.y)
			m_min.y = point.y;
		if (point.z < m_min.z)
			m_min.z = point.z;
		if (point.x > m_max.x)
			m_max.x = point.x;
		if (point.y > m_max.y)
			m_max.y = point.y;
		if (point.z > m_max.z)
			m_max.z = point.z;
	}

	void Merge(const OBoundingBox& box)
	{
		if (!m_isInit)
		{
			m_min = box.m_min;
			m_max = box.m_max;
			m_isInit = true;
			return;
		}

		if (box.m_min.x < m_min.x)
			m_min.x = box.m_min.x;
		if (box.m_min.y < m_min.y)
			m_min.y = box.m_min.y;
		if (box.m_min.z < m_min.z)
			m_min.z = box.m_min.z;
		if (box.m_max.x > m_max.x)
			m_max.x = box.m_max.x;
		if (box.m_max.y > m_max.y)
			m_max.y = box.m_max.y;
		if (box.m_max.z > m_max.z)
			m_max.z = box.m_max.z;
	}

	void Init(const OVector3* vertices, unsigned count);
	void Init(const OFrustum& frustum);
	void Init(const OPolyhedron& poly);
	void Init(const OSphere& sphere);


	void Merge(const OVector3* vertices, unsigned count);
	void Merge(const OFrustum& frustum);
	void Merge(const OPolyhedron& poly);
	void Merge(const OSphere& sphere);


	void Clip(const OBoundingBox& box);

	void Transform(const OMatrix3x3& transform);
	void Transform(const OMatrix3x4& transform);

	/// Clear to unInit state.
	void Clear()
	{
		m_min = OVector3::ZERO;
		m_max = OVector3::ZERO;
		m_isInit = false;
	}

	OVector3 Center() const { return (m_max + m_min) * 0.5f; }
	OVector3 Size() const { return m_max - m_min; }
	OVector3 HalfSize() const { return (m_max - m_min) * 0.5f; }

	OBoundingBox Transformed(const OMatrix3x3& transform) const;
	OBoundingBox Transformed(const OMatrix3x4& transform) const;

	/// Return projected by a 4x4 projection matrix.
	ORect Projected(const OMatrix4x4& projection) const;

	/// Test if a point is inside.
	Intersection IsInside(const OVector3& point) const
	{
		if (point.x < m_min.x || point.x > m_max.x || 
			point.y < m_min.y || point.y > m_max.y ||
			point.z < m_min.z || point.z > m_max.z)
			return OUTSIDE;
		else
			return INSIDE;
	}

	/// Test if another bounding box is inside, outside or intersects.
	Intersection IsInside(const OBoundingBox& box) const
	{
		if (box.m_max.x < m_min.x || box.m_min.x > m_max.x ||
			box.m_max.y < m_min.y || box.m_min.y > m_max.y ||
			box.m_max.z < m_min.z || box.m_min.z > m_max.z)
			return OUTSIDE;
		else if (box.m_min.x < m_min.x || box.m_max.x > m_max.x ||
			box.m_min.y < m_min.y || box.m_max.y > m_max.y ||
			box.m_min.z < m_min.z || box.m_max.z > m_max.z)
			return INTERSECTS;
		else
			return INSIDE;
	}

	/// Test if another bounding box is (partially) inside or outside.
	Intersection IsInsideFast(const OBoundingBox& box) const
	{
		if (box.m_max.x < m_min.x || box.m_min.x > m_max.x || 
			box.m_max.y < m_min.y || box.m_min.y > m_max.y ||
			box.m_max.z < m_min.z || box.m_min.z > m_max.z)
			return OUTSIDE;
		else
			return INSIDE;
	}

	/// Test if a sphere is inside, outside or intersects.
	Intersection IsInside(const OSphere& sphere) const;
	/// Test if a sphere is (partially) inside or outside.
	Intersection IsInsideFast(const OSphere& sphere) const;

	/// Return as string.
	//OString ToString() const;

};


#endif/*File Is Over*/