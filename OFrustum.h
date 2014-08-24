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
	
	��׶����6��ƽ����ɵļ��ϣ�����������ռ�.
	��Щ��Ļ������ռ������ֱ����ȡ

	NOTE: ��Щƽ�治һ������λ��������ֻ�ܼ���������ĸ��ռ䣬
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

	//��ʼ��
	void Init(float32 fov, float32 aspectRatio, float32 zoom, float32 nearZ, float32 farZ, const OMatrix3x4& transform = OMatrix3x4::IDENTITY);
	void Init(const OVector3& near, const OVector3& far, const OMatrix3x4& transform = OMatrix3x4::IDENTITY);
	void Init(const OBoundingBox& box, const OMatrix3x4& transform = OMatrix3x4::IDENTITY);

	void InitOrtho(float orthoSize, float aspectRatio, float zoom, float nearZ, float farZ, const OMatrix3x4& transform = OMatrix3x4::IDENTITY);

    void UpdatePlanes();

	//�Ӿ�������ȡ
	void ExtractFromMatrix(
		const OMatrix4x4& matrix,
		bool normalizePlanes = false);


	/// ���Ե��Ƿ���ƽ��ͷ����
	Intersection IsInside(const OVector3& point) const
	{
		for (uint32 i = 0; i < ONLY_FRUSTUM_PLANES_NUM; ++i)
		{
			if (planes[i].Distance(point) < 0.0f)
				return OUTSIDE;
		}
		return INSIDE;
	}

	/// ���������ཻ��������׶������
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

	/// ���ټ�⣬��������Ƿ�����׶���ڣ������Ǿֲ��ģ���������׶����
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