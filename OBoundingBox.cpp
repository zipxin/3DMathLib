#include "stdafx.h"

#include "../OInclude/Math/OBoundingBox.h"
#include "../OInclude/Math/OFrustum.h"

void OBoundingBox::Init(const OVector3* vertices, unsigned count)
{
	if (!count)
		return;

	m_isInit = false;
	Merge(vertices, count);
}

void OBoundingBox::Init(const OFrustum& frustum)
{
	Init(frustum.vertices, ONLY_FRUSTUM_VERTICES_NUM);
}

void OBoundingBox::Init(const OPolyhedron& poly)
{
	m_isInit = false;
	Merge(poly);
}

void OBoundingBox::Init(const OSphere& sphere)
{
	const OVector3& center = sphere.m_center;
	float radius = sphere.m_radius;

	m_min = center + OVector3(-radius, -radius, -radius);
	m_max = center + OVector3(radius, radius, radius);
	m_isInit = true;
}

void OBoundingBox::Merge(const OVector3* vertices, unsigned count)
{
	while (count--)
		Merge(*vertices++);
}

void OBoundingBox::Merge(const OFrustum& frustum)
{
	Merge(frustum.vertices, ONLY_FRUSTUM_VERTICES_NUM);
}

void OBoundingBox::Merge(const OPolyhedron& poly)
{
// 	for (unsigned i = 0; i < poly.faces_.Size(); ++i)
// 	{
// 		const PODVector<Vector3>& face = poly.faces_[i];
// 		if (!face.Empty())
// 			Merge(&face[0], face.Size());
// 	}
}

//如果这条直径刚好在BoundingBox中呢？
void OBoundingBox::Merge(const OSphere& sphere)
{
	const OVector3& center = sphere.m_center;
	float radius = sphere.m_radius;

	Merge(center + OVector3(radius, radius, radius));
	Merge(center + OVector3(-radius, -radius, -radius));
}

void OBoundingBox::Clip(const OBoundingBox& box)
{
	if (box.m_min.x > m_min.x)
		m_min.x = box.m_min.x;
	if (box.m_max.x < m_max.x)
		m_max.x = box.m_max.x;
	if (box.m_min.y > m_min.y)
		m_min.y = box.m_min.y;
	if (box.m_max.y < m_max.y)
		m_max.y = box.m_max.y;
	if (box.m_min.z > m_min.z)
		m_min.z = box.m_min.z;
	if (box.m_max.z < m_max.z)
		m_max.z = box.m_max.z;

	if (m_min.x > m_max.x)
		OSwap<float32>(m_min.x, m_max.x);
	if (m_min.y > m_max.y)
		OSwap<float32>(m_min.y, m_max.y);
	if (m_min.z > m_max.z)
		OSwap<float32>(m_min.z, m_max.z);
}

void OBoundingBox::Transform(const OMatrix3x3& transform)
{
	*this = Transformed(OMatrix3x4(transform));
}

void OBoundingBox::Transform(const OMatrix3x4& transform)
{
	*this = Transformed(transform);
}

OBoundingBox OBoundingBox::Transformed(const OMatrix3x3& transform) const
{
	return Transformed(OMatrix3x4(transform));
}

OBoundingBox OBoundingBox::Transformed(const OMatrix3x4& transform) const
{
// 	OVector3 newCenter = transform * Center();
// 	OVector3 oldEdge = Size() * 0.5f;
// 	OVector3 newEdge = OVector3(
// 		OAbs(transform.m11) * oldEdge.x + OAbs(transform.m12) * oldEdge.y + OAbs(transform.m13) * oldEdge.z,
// 		OAbs(transform.m21) * oldEdge.x + OAbs(transform.m22) * oldEdge.y + OAbs(transform.m23) * oldEdge.z,
// 		OAbs(transform.m31) * oldEdge.x + OAbs(transform.m32) * oldEdge.y + OAbs(transform.m33) * oldEdge.z
// 		);
// 
// 	return OBoundingBox(newCenter - newEdge, newCenter + newEdge);
	return *this;
}

ORect OBoundingBox::Projected(const OMatrix4x4& projection) const
{
// 	Vector3 projMin = min_;
// 	Vector3 projMax = max_;
// 	if (projMin.z_ < M_MIN_NEARCLIP)
// 		projMin.z_ = M_MIN_NEARCLIP;
// 	if (projMax.z_ < M_MIN_NEARCLIP)
// 		projMax.z_ = M_MIN_NEARCLIP;
// 
// 	Vector3 vertices[8];
// 	vertices[0] = projMin;
// 	vertices[1] = Vector3(projMax.x_, projMin.y_, projMin.z_);
// 	vertices[2] = Vector3(projMin.x_, projMax.y_, projMin.z_);
// 	vertices[3] = Vector3(projMax.x_, projMax.y_, projMin.z_);
// 	vertices[4] = Vector3(projMin.x_, projMin.y_, projMax.z_);
// 	vertices[5] = Vector3(projMax.x_, projMin.y_, projMax.z_);
// 	vertices[6] = Vector3(projMin.x_, projMax.y_, projMax.z_);
// 	vertices[7] = projMax;

	ORect rect;
// 	for (unsigned i = 0; i < 8; ++i)
// 	{
// 		Vector3 projected = projection * vertices[i];
// 		rect.Merge(Vector2(projected.x_, projected.y_));
// 	}

	return rect;
}

Intersection OBoundingBox::IsInside(const OSphere& sphere) const
{
// 	float distSquared = 0;
// 	float temp;
// 	const Vector3& center = sphere.center_;
// 
// 	if (center.x_ < min_.x_)
// 	{
// 		temp = center.x_ - min_.x_;
// 		distSquared += temp * temp;
// 	}
// 	else if (center.x_ > max_.x_)
// 	{
// 		temp = center.x_ - max_.x_;
// 		distSquared += temp * temp;
// 	}
// 	if (center.y_ < min_.y_)
// 	{
// 		temp = center.y_ - min_.y_;
// 		distSquared += temp * temp;
// 	}
// 	else if (center.y_ > max_.y_)
// 	{
// 		temp = center.y_ - max_.y_;
// 		distSquared += temp * temp;
// 	}
// 	if (center.z_ < min_.z_)
// 	{
// 		temp = center.z_ - min_.z_;
// 		distSquared += temp * temp;
// 	}
// 	else if (center.z_ > max_.z_)
// 	{
// 		temp = center.z_ - max_.z_;
// 		distSquared += temp * temp;
// 	}
// 
// 	float radius = sphere.radius_;
// 	if (distSquared >= radius * radius)
// 		return OUTSIDE;
// 	else if (center.x_ - radius < min_.x_ || center.x_ + radius > max_.x_ || center.y_ - radius < min_.y_ ||
// 		center.y_ + radius > max_.y_ || center.z_ - radius < min_.z_ || center.z_ + radius > max_.z_)
// 		return INTERSECTS;
// 	else
		return INSIDE;
}

Intersection OBoundingBox::IsInsideFast(const OSphere& sphere) const
{
// 	float distSquared = 0;
// 	float temp;
// 	const Vector3& center = sphere.center_;
// 
// 	if (center.x_ < min_.x_)
// 	{
// 		temp = center.x_ - min_.x_;
// 		distSquared += temp * temp;
// 	}
// 	else if (center.x_ > max_.x_)
// 	{
// 		temp = center.x_ - max_.x_;
// 		distSquared += temp * temp;
// 	}
// 	if (center.y_ < min_.y_)
// 	{
// 		temp = center.y_ - min_.y_;
// 		distSquared += temp * temp;
// 	}
// 	else if (center.y_ > max_.y_)
// 	{
// 		temp = center.y_ - max_.y_;
// 		distSquared += temp * temp;
// 	}
// 	if (center.z_ < min_.z_)
// 	{
// 		temp = center.z_ - min_.z_;
// 		distSquared += temp * temp;
// 	}
// 	else if (center.z_ > max_.z_)
// 	{
// 		temp = center.z_ - max_.z_;
// 		distSquared += temp * temp;
// 	}
// 
// 	float radius = sphere.radius_;
// 	if (distSquared >= radius * radius)
// 		return OUTSIDE;
// 	else
		return INSIDE;
}

// String BoundingBox::ToString() const
// {
// 	return min_.ToString() + " - " + max_.ToString();
// }
