#include "stdafx.h"
#include "../OInclude/Math/OPlane.h"

const OPlane OPlane::UP(OVector3(0.0f, 1.0f, 0.0f), OVector3(0.0f, 0.0f, 0.0f));

// Static initialization order can not be relied on, so do not use Vector3 constants

void OPlane::Transform(const OMatrix3x3& transform)
{
	//Init(OMatrix4x4(transform).Inverse().Transpose() * ToVector4());
}

void OPlane::Transform(const OMatrix3x4& transform)
{
	//Init(transform.ToMatrix4x4().Inverse().Transpose() * ToVector4());
}

void OPlane::Transform(const OMatrix4x4& transform)
{
	//Init(transform.Inverse().Transpose() * ToVector4());
}

OMatrix3x4 OPlane::ReflectionMatrix() const
{
	return OMatrix3x4(
		-2.0f * normal.x * normal.x + 1.0f,
		-2.0f * normal.x * normal.y,
		-2.0f * normal.x * normal.z,
		-2.0f * normal.x * d,
		-2.0f * normal.y * normal.x ,
		-2.0f * normal.y * normal.y + 1.0f,
		-2.0f * normal.y * normal.z,
		-2.0f * normal.y * d,
		-2.0f * normal.z * normal.x,
		-2.0f * normal.z * normal.y,
		-2.0f * normal.z * normal.z + 1.0f,
		-2.0f * normal.z * d
		);
}

OPlane OPlane::Transformed(const OMatrix3x3& transform) const
{
	return OPlane(OMatrix4x4(transform).Inverse().Transpose() * ToVector4());
}

OPlane OPlane::Transformed(const OMatrix3x4& transform) const
{
	return OPlane(transform.ToMatrix4x4().Inverse().Transpose() * ToVector4());
}

OPlane OPlane::Transformed(const OMatrix4x4& transform) const
{
	return OPlane(transform.Inverse().Transpose() * ToVector4());
}

OPlane::PlaneSide OPlane::GetSide(OVector3 point)
{
	float fDistance = Distance(point);

	if ( fDistance < 0.0 )
		return OPlane::NEGATIVE_SIDE;

	if ( fDistance > 0.0 )
		return OPlane::POSITIVE_SIDE;

	return OPlane::ON_THE_PLANE;
}
