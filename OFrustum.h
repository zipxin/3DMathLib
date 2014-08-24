//////////////////////////////////////////////////////////////////////////
//File : Only Frustum ( Only Math Lib)
//Author : Zipxin  [China]
//E-mail: zipxin@163.com
//Project : OnlyGameEngine
//////////////////////////////////////////////////////////////////////////
#ifndef _ONLY_FRUSTUM_H_
#define _ONLY_FRUSTUM_H_

#if _MSC_VER > 1000
#pragma once
#endif 

#include "../OInclude/Common/OnlyGameDefine.h"

#include "../OInclude/Math/OPlane.h"
#include "../OInclude/Math/OMatrix3x4.h"
#include "../OInclude/Math/OBoundingBox.h"
#include "OSphere.h"



/*	OFrustum
-----------------------------------------------------------------
	
	视锥体是6个平面组成的集合，代表着相机空间.
	这些屏幕从相机空间矩阵里直接提取

	NOTE: 这些平面不一定被单位化，所以只能检测物体在哪个空间，
	This means they are only sutable for half-space testing.
	No distance values calcualted using these planes will be
	accurate other than to show whether positions lie in the 
	positive or negative half-space of the plane.

-----------------------------------------------------------------
*/
enum FrustumPlane
{
	PLANE_NEAR = 0,
	PLANE_LEFT,
	PLANE_RIGHT,
	PLANE_UP,
	PLANE_DOWN,
	PLANE_FAR,
};

static const unsigned ONLY_FRUSTUM_PLANES_NUM = 6;
static const unsigned ONLY_FRUSTUM_VERTICES_NUM = 8;

class OFrustum
{
	friend class OSphere;
	friend class OBoundingBox;
	friend class ORay;
protected:
	OPlane planes[ONLY_FRUSTUM_PLANES_NUM];
	OVector3 vertices[ONLY_FRUSTUM_VERTICES_NUM];
public:
	OFrustum(){}
	OFrustum(const OFrustum& frustum)
	{
		if(&frustum != this)
			*this = frustum;
	}
	OFrustum& operator = (const OFrustum& rhs);

	~OFrustum(){}

	//初始化
	void Init(float32 fov, float32 aspectRatio, float32 zoom, float32 nearZ, float32 farZ, const OMatrix3x4& transform = OMatrix3x4::IDENTITY);
	void Init(const OVector3& near, const OVector3& far, const OMatrix3x4& transform = OMatrix3x4::IDENTITY);
	void Init(const OBoundingBox& box, const OMatrix3x4& transform = OMatrix3x4::IDENTITY);

	void InitOrtho(float orthoSize, float aspectRatio, float zoom, float nearZ, float farZ, const OMatrix3x4& transform = OMatrix3x4::IDENTITY);

    void UpdatePlanes();

	//从矩阵中提取
	void ExtractFromMatrix(
		const OMatrix4x4& matrix,
		bool normalizePlanes = false);


	/// 测试点是否在平截头体内
	Intersection IsInside(const OVector3& point) const
	{
		for (uint32 i = 0; i < ONLY_FRUSTUM_PLANES_NUM; ++i)
		{
			if (planes[i].Distance(point) < 0.0f)
				return OUTSIDE;
		}
		return INSIDE;
	}

	/// 测试球是相交还是在视锥体内外
	Intersection IsInside(const OSphere& sphere) const
	{
		bool allInside = true;
		for (unsigned i = 0; i < ONLY_FRUSTUM_PLANES_NUM; ++i)
		{
			float dist = planes[i].Distance(sphere.m_center);
			if (dist < -sphere.m_radius)
				return OUTSIDE;
			else if (dist < sphere.m_radius)
				allInside = false;
		}
		return allInside ? INSIDE : INTERSECTS;
	}

	/// 快速检测，检测球体是否在视锥体内（可能是局部的）或者在视锥体外
	Intersection IsInsideFast(const OSphere& sphere) const
	{
		for (unsigned i = 0; i < ONLY_FRUSTUM_PLANES_NUM; ++i)
		{
			if (planes[i].Distance(sphere.m_center) < -sphere.m_radius)
				return OUTSIDE;
		}
		return INSIDE;
	}


	/// Test if a bounding box is inside, outside or intersects.
	Intersection IsInside(const OBoundingBox& box) const
	{
		OVector3 center = box.Center();
		OVector3 edge = center - box.m_min;
		bool allInside = true;

		for (unsigned i = 0; i < ONLY_FRUSTUM_PLANES_NUM; ++i)
		{
			const OPlane& plane = planes[i];
			float dist = Vec3_Dotf(plane.normal, center) + plane.d;
			OVector3 planeNor(plane.normal);
			float absDist = Vec3_Dotf(planeNor.Abs(),edge);

			if (dist < -absDist)
				return OUTSIDE;
			else if (dist < absDist)
				allInside = false;
		}

		return allInside ? INSIDE : INTERSECTS;
	}


	void Transform(const OMatrix3x3& transform);
	void Transform(const OMatrix3x4& transform);


	Intersection IsInsideFast(const OBoundingBox& box) const
	{
		OVector3 center = box.Center();
		OVector3 edge = center - box.m_min;

		for (unsigned i = 0; i < ONLY_FRUSTUM_PLANES_NUM; ++i)
		{
			const OPlane& plane = planes[i];
			float dist = Vec3_Dotf(plane.normal, center) + plane.d;
			OVector3 planeNor(plane.normal);
			float absDist = Vec3_Dotf(planeNor.Abs(),edge);

			if (dist < -absDist)
				return OUTSIDE;
		}

		return INSIDE;
	}

	/// Return distance of a point to the frustum, or 0 if inside.
	float Distance(const OVector3& point) const
	{
		float32 distance = 0.0f;
		for (unsigned i = 0; i < ONLY_FRUSTUM_PLANES_NUM; ++i)
			distance = OMax2<float32>(-planes[i].Distance(point), distance);

		return distance;
	}

	OFrustum Transformed(const OMatrix3x3& transform) const;
	OFrustum Transformed(const OMatrix3x4& transform) const;

	ORect Projected(const OMatrix4x4& transform) const;
};

#endif /* File Is Over */