#include "stdafx.h"
#include "OSphere.h"

#include "../OInclude/Math/OBoundingBox.h"
#include "../OInclude/Math/OFrustum.h"

void OSphere::Init(const OVector3* vertices, unsigned count)
{
	if (!count)
		return;

	m_isInited = false;
	Merge(vertices, count);
}

void OSphere::Init(const OBoundingBox& box)
{
	const OVector3& min = box.m_min;
	const OVector3& max = box.m_max;

	m_isInited = false;
	Merge(min);
	Merge(OVector3(max.x, min.y, min.z));
	Merge(OVector3(min.x, max.y, min.z));
	Merge(OVector3(max.x, max.y, min.z));
	Merge(OVector3(min.x, min.y, max.z));
	Merge(OVector3(max.x, min.y, max.z));
	Merge(OVector3(min.x, max.y, max.z));
	Merge(max);
}

void OSphere::Init(const OFrustum& frustum)
{
	Init(frustum.vertices, ONLY_FRUSTUM_VERTICES_NUM);
}

void OSphere::Init(const OPolyhedron& poly)
{
	m_isInited = false;
	Merge(poly);
}

void OSphere::Merge(const OVector3* vertices, unsigned count)
{
	while (count--)
		Merge(*vertices++);
}

void OSphere::Merge(const OBoundingBox& box)
{
	const OVector3& min = box.m_min;
	const OVector3& max = box.m_max;

	Merge(min);
	Merge(OVector3(max.x, min.y, min.z));
	Merge(OVector3(min.x, max.y, min.z));
	Merge(OVector3(max.x, max.y, min.z));
	Merge(OVector3(min.x, min.y, max.z));
	Merge(OVector3(max.x, min.y, max.z));
	Merge(OVector3(min.x, max.y, max.z));
	Merge(max);
}

void OSphere::Merge(const OFrustum& frustum)
{
	const OVector3* vertices = frustum.vertices;
	Merge(vertices, ONLY_FRUSTUM_VERTICES_NUM);
}

// void OSphere::Merge(const Polyhedron& poly)
// {
// 	for (unsigned i = 0; i < poly.faces_.Size(); ++i)
// 	{
// 		const PODVector<Vector3>& face = poly.faces_[i];
// 		if (!face.Empty())
// 			Merge(&face[0], face.Size());
// 	}
// }

void OSphere::Merge(const OSphere& sphere)
{
	if (!m_isInited)
	{
		m_center = sphere.m_center;
		m_radius = sphere.m_radius;
		m_isInited = true;
		return;
	}

	OVector3 offset = sphere.m_center - m_center;
	float dist = offset.Length();

	//如果要融入的球在球内部
	if (dist + sphere.m_radius < m_radius)
		return;

	// If we fit inside the other sphere, become it
	if (dist + m_radius < sphere.m_radius)
	{
		m_center = sphere.m_center;
		m_radius = sphere.m_radius;
	}
	else
	{
		OVector3 NormalizedOffset = offset / dist;

		OVector3 min = m_center - m_radius * NormalizedOffset;
		OVector3 max = sphere.m_center + sphere.m_radius * NormalizedOffset;
		m_center = (min + max) * 0.5f;
		m_radius = (max - m_center).Length();
	}
}

Intersection OSphere::IsInside(const OBoundingBox& box) const
{
	float radiusSquared = m_radius * m_radius;
	float distSquared = 0;
	float temp;
	OVector3 min = box.m_min;
	OVector3 max = box.m_max;

	if (m_center.x < min.x)
	{
		temp = m_center.x - min.x;
		distSquared += temp * temp;
	}
	else if (m_center.x > max.x)
	{
		temp = m_center.x - max.x;
		distSquared += temp * temp;
	}
	if (m_center.y < min.y)
	{
		temp = m_center.y - min.y;
		distSquared += temp * temp;
	}
	else if (m_center.y > max.y)
	{
		temp = m_center.y - max.y;
		distSquared += temp * temp;
	}
	if (m_center.z < min.z)
	{
		temp = m_center.z - min.z;
		distSquared += temp * temp;
	}
	else if (m_center.z > max.z)
	{
		temp = m_center.z - max.z;
		distSquared += temp * temp;
	}

	if (distSquared >= radiusSquared)
		return OUTSIDE;

	min -= m_center;
	max -= m_center;

	OVector3 tempVec = min; // - - -
	if (tempVec.LengthNotSqrt() >= radiusSquared)
		return INTERSECTS;
	tempVec.x = max.x; // + - -
	if (tempVec.LengthNotSqrt() >= radiusSquared)
		return INTERSECTS;
	tempVec.y = max.y; // + + -
	if (tempVec.LengthNotSqrt() >= radiusSquared)
		return INTERSECTS;
	tempVec.x = min.x; // - + -
	if (tempVec.LengthNotSqrt() >= radiusSquared)
		return INTERSECTS;
	tempVec.z = max.z; // - + +
	if (tempVec.LengthNotSqrt() >= radiusSquared)
		return INTERSECTS;
	tempVec.y = min.y; // - - +
	if (tempVec.LengthNotSqrt() >= radiusSquared)
		return INTERSECTS;
	tempVec.x = max.x; // + - +
	if (tempVec.LengthNotSqrt() >= radiusSquared)
		return INTERSECTS;
	tempVec.y = max.y; // + + +
	if (tempVec.LengthNotSqrt() >= radiusSquared)
		return INTERSECTS;

	return INSIDE;
}

Intersection OSphere::IsInsideFast(const OBoundingBox& box) const
{
	float radiusSquared = m_radius * m_radius;
	float distSquared = 0;
	float temp;
	OVector3 min = box.m_min;
	OVector3 max = box.m_max;

	if (m_center.x < min.x)
	{
		temp = m_center.x - min.x;
		distSquared += temp * temp;
	}
	else if (m_center.x > max.x)
	{
		temp = m_center.x - max.x;
		distSquared += temp * temp;
	}
	if (m_center.y < min.y)
	{
		temp = m_center.y - min.y;
		distSquared += temp * temp;
	}
	else if (m_center.y > max.y)
	{
		temp = m_center.y - max.y;
		distSquared += temp * temp;
	}
	if (m_center.z < min.z)
	{
		temp = m_center.z - min.z;
		distSquared += temp * temp;
	}
	else if (m_center.z > max.z)
	{
		temp = m_center.z - max.z;
		distSquared += temp * temp;
	}

	if (distSquared >= radiusSquared)
		return OUTSIDE;
	else
		return INSIDE;
}
