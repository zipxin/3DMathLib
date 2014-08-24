#include "stdafx.h"
#include "../OInclude/Math/ORay.h"

#include "../OInclude/Math/OBoundingBox.h"
#include "../OInclude/Math/OFrustum.h"
#include "../OInclude/Math/OPlane.h"
#include "../OInclude/Math/ORay.h"
#include "OSphere.h"

//算法来自网络 
OVector3 ORay::ClosestPoint(const ORay& ORay) const
{
	OVector3 p13 = m_origin - ORay.m_origin;
	OVector3 p43 = ORay.m_direction;
	OVector3 p21 = m_direction;

	float d1343 = Vec3_Dotf(p13, p43);
	float d4321 = Vec3_Dotf(p43, p21);
	float d1321 = Vec3_Dotf(p13, p21);
	float d4343 = Vec3_Dotf(p43, p43);
	float d2121 = Vec3_Dotf(p21, p21);

	float d = d2121 * d4343 - d4321 * d4321;
	if (OAbs(d) < EPSILON)
		return m_origin;
	float n = d1343 * d4321 - d1321 * d4343;
	float a = n / d;

	return m_origin + a * m_direction;
}

//算法来自：
//http://jiegeng0805.blog.163.com/blog/static/24057709201241515923710/
float32 ORay::HitDistance(const OPlane& plane) const
{
	float32 d = Vec3_Dotf( plane.normal ,m_direction );
	if (OAbs(d) >= EPSILON)
	{
		float t = -( Vec3_Dotf( plane.normal, m_origin) + plane.d ) / d;
		if (t >= 0.0f)
			return t;
		else
			return INFINITY;
	}
	else //平行
		return INFINITY;
}

float ORay::HitDistance(const OBoundingBox& box) const
{
	// If undefined, no hit (infinite distance)
	if (!box.m_isInit)
		return INFINITY;

	// Check for ORay origin being inside the box
	if (box.IsInside(m_origin))
		return 0.0f;

	float dist = INFINITY;

	// Check for intersecting in the X-direction
	if (m_origin.x < box.m_min.x && m_direction.x > 0.0f)
	{
		float x = (box.m_min.x - m_origin.x) / m_direction.x;
		if (x < dist)
		{
			OVector3 point = m_origin + x * m_direction;
			if (point.y >= box.m_min.y && point.y <= box.m_max.y && point.z >= box.m_min.z && point.z <= box.m_max.z)
				dist = x;
		}
	}
	if (m_origin.x > box.m_max.x && m_direction.x < 0.0f)
	{
		float x = (box.m_max.x - m_origin.x) / m_direction.x;
		if (x < dist)
		{
			OVector3 point = m_origin + x * m_direction;
			if (point.y >= box.m_min.y && point.y <= box.m_max.y && point.z >= box.m_min.z && point.z <= box.m_max.z)
				dist = x;
		}
	}
	// Check for intersecting in the Y-direction
	if (m_origin.y < box.m_min.y && m_direction.y > 0.0f)
	{
		float x = (box.m_min.y - m_origin.y) / m_direction.y;
		if (x < dist)
		{
			OVector3 point = m_origin + x * m_direction;
			if (point.x >= box.m_min.x && point.x <= box.m_max.x && point.z >= box.m_min.z && point.z <= box.m_max.z)
				dist = x;
		}
	}
	if (m_origin.y > box.m_max.y && m_direction.y < 0.0f)
	{
		float x = (box.m_max.y - m_origin.y) / m_direction.y;
		if (x < dist)
		{
			OVector3 point = m_origin + x * m_direction;
			if (point.x >= box.m_min.x && point.x <= box.m_max.x && point.z >= box.m_min.z && point.z <= box.m_max.z)
				dist = x;
		}
	}
	// Check for intersecting in the Z-direction
	if (m_origin.z < box.m_min.z && m_direction.z > 0.0f)
	{
		float x = (box.m_min.z - m_origin.z) / m_direction.z;
		if (x < dist)
		{
			OVector3 point = m_origin + x * m_direction;
			if (point.x >= box.m_min.x && point.x <= box.m_max.x && point.y >= box.m_min.y && point.y <= box.m_max.y)
				dist = x;
		}
	}
	if (m_origin.z > box.m_max.z && m_direction.z < 0.0f)
	{
		float x = (box.m_max.z - m_origin.z) / m_direction.z;
		if (x < dist)
		{
			OVector3 point = m_origin + x * m_direction;
			if (point.x >= box.m_min.x && point.x <= box.m_max.x && point.y >= box.m_min.y && point.y <= box.m_max.y)
				dist = x;
		}
	}

	return dist;
}

float ORay::HitDistance(const OFrustum& frustum, bool solidInside) const
{
	float maxOutside = 0.0f;
	float minInside = INFINITY;
	bool allInside = true;

	for (unsigned i = 0; i < ONLY_FRUSTUM_PLANES_NUM; ++i)
	{
		const OPlane& plane = frustum.planes[i];
		float distance = HitDistance(frustum.planes[i]);

		if (plane.Distance(m_origin) < 0.0f)
		{
			maxOutside = OMax2<float32>(maxOutside, distance);
			allInside = false;
		}
		else
			minInside = OMin2<float32>(minInside, distance);
	}

	if (allInside)
		return solidInside ? 0.0f : minInside;
	else if (maxOutside <= minInside)
		return maxOutside;
	else
		return INFINITY;
}

float ORay::HitDistance(const OSphere& sphere) const
{
	OVector3 centeredOrigin = m_origin - sphere.m_center;
	float squaredRadius = sphere.m_radius * sphere.m_radius;

	// Check if ORay originates inside the sphere
	if (centeredOrigin.LengthNotSqrt() <= squaredRadius)
		return 0.0f;

	// Calculate intersection by quadratic equation
	float a = Vec3_Dotf(m_direction, m_direction);
	float b = 2.0f * Vec3_Dotf(centeredOrigin, m_direction);
	float c = Vec3_Dotf(centeredOrigin,  centeredOrigin) - squaredRadius;
	float d = b * b - 4.0f * a * c;

	// No solution
	if (d < 0.0f)
		return INFINITY;

	// Get the nearer solution
	float dSqrt = sqrtf(d);
	float dist = (-b - dSqrt) / (2.0f * a);
	if (dist >= 0.0f)
		return dist;
	else
		return (-b + dSqrt) / (2.0f * a);
}

float ORay::HitDistance(const OVector3& v0, const OVector3& v1, const OVector3& v2) const
{
	return HitDistance(v0, v1, v2, 0);
}


//三角形v0,v1,v2
//判断点v是不是在三角形上只需要知道 O+ Dt = (1 - u - v)V0 + uV1 + vV2
//详细讲解参照：http://www.cnblogs.com/graphics/archive/2010/08/09/1795348.html
float ORay::HitDistance(const OVector3& v0, const OVector3& v1, const OVector3& v2, OVector3* outNormal) const
{
	// Based on Fast, Minimum Storage ORay/Triangle Intersection by M鰈ler & Trumbore
	// http://www.graphics.cornell.edu/pubs/1997/MT97.pdf
	// Calculate edge vectors
	OVector3 edge1(v1 - v0);
	OVector3 edge2(v2 - v0);

	// Calculate determinant & check backfacing
	OVector3 p( Vec3_CrossProduct( m_direction, edge2));
	float det = Vec3_Dotf( edge1, p );
	if (det >= EPSILON)
	{
		// Calculate u & v parameters and test
		OVector3 t(m_origin - v0);
		float u = Vec3_Dotf(t, p);
		if (u >= 0.0f && u <= det)
		{
			OVector3 q(Vec3_CrossProduct(t, edge1));
			float v = Vec3_Dotf( m_direction, q );
			if (v >= 0.0f && u + v <= det)
			{
				// There is an intersection, so calculate distance & optional normal
				if (outNormal)
					*outNormal = Vec3_CrossProduct(edge1, edge2);

				return Vec3_Dotf(edge2, q) / det;
			}
		}
	}

	return INFINITY;
}

float ORay::HitDistance(const void* vertexData, unsigned vertexSize, unsigned vertexStart, unsigned vertexCount, OVector3* outNormal) const
{
	float nearest = INFINITY;
	const unsigned char* vertices = ((const unsigned char*)vertexData) + vertexStart * vertexSize;
	unsigned index = 0;

	while (index + 2 < vertexCount)
	{
		const OVector3& v0 = *((const OVector3*)(&vertices[index * vertexSize]));
		const OVector3& v1 = *((const OVector3*)(&vertices[(index + 1) * vertexSize]));
		const OVector3& v2 = *((const OVector3*)(&vertices[(index + 2) * vertexSize]));
		nearest = OMin2<float32>(nearest, HitDistance(v0, v1, v2, outNormal));
		index += 3;
	}

	return nearest;
}

float ORay::HitDistance(const void* vertexData, unsigned vertexSize, const void* indexData, unsigned indexSize,
					   unsigned indexStart, unsigned indexCount, OVector3* outNormal) const
{
	float nearest = INFINITY;
	const unsigned char* vertices = (const unsigned char*)vertexData;

	// 16-bit indices
	if (indexSize == sizeof(unsigned short))
	{
		const unsigned short* indices = ((const unsigned short*)indexData) + indexStart;
		const unsigned short* indicesEnd = indices + indexCount;

		while (indices < indicesEnd)
		{
			const OVector3& v0 = *((const OVector3*)(&vertices[indices[0] * vertexSize]));
			const OVector3& v1 = *((const OVector3*)(&vertices[indices[1] * vertexSize]));
			const OVector3& v2 = *((const OVector3*)(&vertices[indices[2] * vertexSize]));
			nearest = OMin2<float32>(nearest, HitDistance(v0, v1, v2, outNormal));
			indices += 3;
		}
	}
	// 32-bit indices
	else
	{
		const unsigned* indices = ((const unsigned*)indexData) + indexStart;
		const unsigned* indicesEnd = indices + indexCount;

		while (indices < indicesEnd)
		{
			const OVector3& v0 = *((const OVector3*)(&vertices[indices[0] * vertexSize]));
			const OVector3& v1 = *((const OVector3*)(&vertices[indices[1] * vertexSize]));
			const OVector3& v2 = *((const OVector3*)(&vertices[indices[2] * vertexSize]));
			nearest = OMin2<float32>(nearest, HitDistance(v0, v1, v2, outNormal));
			indices += 3;
		}
	}

	return nearest;
}

bool ORay::InsideGeometry(const void* vertexData, unsigned vertexSize, unsigned vertexStart, unsigned vertexCount) const
{
	float currentFrontFace = INFINITY;
	float currentBackFace = INFINITY;
	const unsigned char* vertices = ((const unsigned char*)vertexData) + vertexStart * vertexSize;
	unsigned index = 0;

	while (index + 2 < vertexCount)
	{
		const OVector3& v0 = *((const OVector3*)(&vertices[index * vertexSize]));
		const OVector3& v1 = *((const OVector3*)(&vertices[(index + 1) * vertexSize]));
		const OVector3& v2 = *((const OVector3*)(&vertices[(index + 2) * vertexSize]));
		float frontFaceDistance = HitDistance(v0, v1, v2);
		float backFaceDistance = HitDistance(v2, v1, v0);
		currentFrontFace = OMin2<float32>(frontFaceDistance > 0.0f ? frontFaceDistance : INFINITY, currentFrontFace);
		// A backwards face is just a regular one, with the vertices in the opposite order. This essentially checks backfaces by
		// checking reversed frontfaces
		currentBackFace = OMin2<float32>(backFaceDistance > 0.0f ? backFaceDistance : INFINITY, currentBackFace);
		index += 3;
	}

	// If the closest face is a backface, that means that the ORay originates from the inside of the geometry
	// NOTE: there may be cases where both are equal, as in, no collision to either. This is prevented in the most likely case
	// (ORay doesnt hit either) by this conditional
	if (currentFrontFace != INFINITY || currentBackFace != INFINITY)
		return currentBackFace < currentFrontFace;

	// It is still possible for two triangles to be equally distant from the triangle, however, this is extremely unlikely.
	// As such, it is safe to assume they are not
	return false;
}

bool ORay::InsideGeometry(const void* vertexData, unsigned vertexSize, const void* indexData, unsigned indexSize,
						 unsigned indexStart, unsigned indexCount) const
{
	float currentFrontFace = INFINITY;
	float currentBackFace = INFINITY;
	const unsigned char* vertices = (const unsigned char*)vertexData;

	// 16-bit indices
	if (indexSize == sizeof(unsigned short))
	{
		const unsigned short* indices = ((const unsigned short*)indexData) + indexStart;
		const unsigned short* indicesEnd = indices + indexCount;

		while (indices < indicesEnd)
		{
			const OVector3& v0 = *((const OVector3*)(&vertices[indices[0] * vertexSize]));
			const OVector3& v1 = *((const OVector3*)(&vertices[indices[1] * vertexSize]));
			const OVector3& v2 = *((const OVector3*)(&vertices[indices[2] * vertexSize]));
			float frontFaceDistance = HitDistance(v0, v1, v2);
			float backFaceDistance = HitDistance(v2, v1, v0);
			currentFrontFace = OMin2<float32>(frontFaceDistance > 0.0f ? frontFaceDistance : INFINITY, currentFrontFace);
			// A backwards face is just a regular one, with the vertices in the opposite order. This essentially checks backfaces by
			// checking reversed frontfaces
			currentBackFace = OMin2<float32>(backFaceDistance > 0.0f ? backFaceDistance : INFINITY, currentBackFace);
			indices += 3;
		}
	}
	// 32-bit indices
	else
	{
		const unsigned* indices = ((const unsigned*)indexData) + indexStart;
		const unsigned* indicesEnd = indices + indexCount;

		while (indices < indicesEnd)
		{
			const OVector3& v0 = *((const OVector3*)(&vertices[indices[0] * vertexSize]));
			const OVector3& v1 = *((const OVector3*)(&vertices[indices[1] * vertexSize]));
			const OVector3& v2 = *((const OVector3*)(&vertices[indices[2] * vertexSize]));
			float32 frontFaceDistance = HitDistance(v0, v1, v2);
			float32 backFaceDistance = HitDistance(v2, v1, v0);
			currentFrontFace = OMin2<float32>(frontFaceDistance > 0.0f ? frontFaceDistance : INFINITY, currentFrontFace);
			// A backwards face is just a regular one, with the vertices in the opposite order. This essentially checks backfaces by
			// checking reversed frontfaces
			currentBackFace = OMin2<float32>(backFaceDistance > 0.0f ? backFaceDistance : INFINITY, currentBackFace);
			indices += 3; 
		}
	}

	// If the closest face is a backface, that means that the ORay originates from the inside of the geometry
	// NOTE: there may be cases where both are equal, as in, no collision to either. This is prevented in the most likely case
	// (ORay doesnt hit either) by this conditional
	if (currentFrontFace != INFINITY || currentBackFace != INFINITY)
		return currentBackFace < currentFrontFace;

	// It is still possible for two triangles to be equally distant from the triangle, however, this is extremely unlikely.
	// As such, it is safe to assume they are not
	return false;
}

ORay ORay::Transformed(const OMatrix3x4& transform) const
{
	ORay ret;
	//ret.m_origin = transform * m_origin;
	//ret.m_direction = transform * OVector4(m_direction, 0.0f);
	return ret;
}