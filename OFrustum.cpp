#include "stdafx.h"
#include "../OInclude/Math/OFrustum.h"


OFrustum& OFrustum::operator = (const OFrustum& rhs)
{
	for (unsigned i = 0; i < ONLY_FRUSTUM_PLANES_NUM; ++i)
		planes[i] = rhs.planes[i];
	for (unsigned i = 0; i < ONLY_FRUSTUM_VERTICES_NUM; ++i)
		vertices[i] = rhs.vertices[i];

	return *this;
}
//×óÊÖÏµ
void OFrustum::Init(float32 fov, float32 aspectRatio, float32 zoom, float32 nearZ, float32 farZ, const OMatrix3x4& transform )
{
	nearZ = OMax2<float32>(nearZ, 0.0f);
	farZ  = OMax2<float32>(farZ,  nearZ);

	float32 halfViewSize = (float32)tanf( (float32)fov * DEG_TO_RAD * 0.5f ) / zoom;
	OVector3 near, far;

	near.SetZf( nearZ );
	near.SetYf( near.GetZf() * halfViewSize );
	near.SetXf( near.GetYf() * aspectRatio );
	
	far.SetZf( farZ );
	far.SetYf( far.GetZf() * halfViewSize );
	far.SetXf( far.GetYf() * aspectRatio);

	Init(near, far, transform);
}


void OFrustum::Init(const OVector3& near, const OVector3& far, const OMatrix3x4& transform)
{
// 	vertices[0] = transform * near;
// 	vertices[1] = transform * OVector3( near.x, -near.y, near.z);
// 	vertices[2] = transform * OVector3(-near.x, -near.y, near.z);
// 	vertices[3] = transform * OVector3(-near.x,  near.y, near.z);
// 	vertices[4] = transform * far;
// 	vertices[5] = transform * OVector3( far.x, -far.y, far.z);
// 	vertices[6] = transform * OVector3(-far.x, -far.y, far.z);
// 	vertices[7] = transform * OVector3(-far.x,  far.y, far.z);

	UpdatePlanes();
}

void OFrustum::Init(const OBoundingBox& box, const OMatrix3x4& transform)
{
// 	vertices[0] = transform * OVector3(box.m_max.x, box.m_max.y, box.m_min.z);
// 	vertices[1] = transform * OVector3(box.m_max.x, box.m_min.y, box.m_min.z);
// 	vertices[2] = transform * OVector3(box.m_min.x, box.m_min.y, box.m_min.z);
// 	vertices[3] = transform * OVector3(box.m_min.x, box.m_max.y, box.m_min.z);
// 	vertices[4] = transform * OVector3(box.m_max.x, box.m_max.y, box.m_max.z);
// 	vertices[5] = transform * OVector3(box.m_max.x, box.m_min.y, box.m_max.z);
// 	vertices[6] = transform * OVector3(box.m_min.x, box.m_min.y, box.m_max.z);
// 	vertices[7] = transform * OVector3(box.m_min.x, box.m_max.y, box.m_max.z);

	UpdatePlanes();
}

/*          * v6      *v5
		   /---------/|  
          /         / |
		 /__ *v7___/  *v4	
	 v2*|   /    |v1 /
        |  /     |  /
		| /		 | /	 
		|/_______|/
	    v3        v0 
*/
void OFrustum::UpdatePlanes()
{
	planes[PLANE_NEAR].Init(vertices[2], vertices[1], vertices[0]);
	planes[PLANE_LEFT].Init(vertices[3], vertices[7], vertices[6]);
	planes[PLANE_RIGHT].Init(vertices[1], vertices[5], vertices[4]);
	planes[PLANE_UP].Init(vertices[0], vertices[4], vertices[7]);
	planes[PLANE_DOWN].Init(vertices[6], vertices[5], vertices[1]);
	planes[PLANE_FAR].Init(vertices[5], vertices[6], vertices[7]);

	if (planes[PLANE_NEAR].Distance(vertices[5]) < 0.0f)
	{
		for (unsigned i = 0; i < ONLY_FRUSTUM_PLANES_NUM; ++i)
		{
			planes[i].normal = -planes[i].normal;
			planes[i].d = -planes[i].d;
		}
	}

}


void OFrustum::ExtractFromMatrix( const OMatrix4x4& matrix,
								 bool normalizePlanes)
{
	// Left clipping plane 
	planes[PLANE_LEFT].normal.x = matrix.m14 + matrix.m11; 
	planes[PLANE_LEFT].normal.y = matrix.m24 + matrix.m21; 
	planes[PLANE_LEFT].normal.z = matrix.m34 + matrix.m31; 
	planes[PLANE_LEFT].d        = matrix.m44 + matrix.m41;

	// Right clipping plane 
	planes[PLANE_RIGHT].normal.x = matrix.m14 - matrix.m11; 
	planes[PLANE_RIGHT].normal.y = matrix.m24 - matrix.m21; 
	planes[PLANE_RIGHT].normal.z = matrix.m34 - matrix.m31; 
	planes[PLANE_RIGHT].d        = matrix.m44 - matrix.m41;

	// Top clipping plane 
	planes[PLANE_UP].normal.x = matrix.m14 - matrix.m12; 
	planes[PLANE_UP].normal.y = matrix.m24 - matrix.m22; 
	planes[PLANE_UP].normal.z = matrix.m34 - matrix.m32; 
	planes[PLANE_UP].d        = matrix.m44 - matrix.m42;

	// Bottom clipping plane 
	planes[PLANE_DOWN].normal.x = matrix.m14 + matrix.m12; 
	planes[PLANE_DOWN].normal.y = matrix.m24 + matrix.m22; 
	planes[PLANE_DOWN].normal.z = matrix.m34 + matrix.m32; 
	planes[PLANE_DOWN].d        = matrix.m44 + matrix.m42;

	// Near clipping plane 
	planes[PLANE_NEAR].normal.x = matrix.m13; 
	planes[PLANE_NEAR].normal.y = matrix.m23; 
	planes[PLANE_NEAR].normal.z = matrix.m33; 
	planes[PLANE_NEAR].d        = matrix.m43;

	// Far clipping plane 
	planes[PLANE_FAR].normal.x = matrix.m14 - matrix.m13; 
	planes[PLANE_FAR].normal.y = matrix.m24 - matrix.m23; 
	planes[PLANE_FAR].normal.z = matrix.m34 - matrix.m33; 
	planes[PLANE_FAR].d        = matrix.m44 - matrix.m43; 

	// it is not always nessesary to normalize
	// the planes of the frustum. Non-normalized
	// planes can still be used for basic
	// intersection tests.
	if (normalizePlanes)
	{
		planes[PLANE_LEFT].Normalize();
		planes[PLANE_RIGHT].Normalize();
		planes[PLANE_UP].Normalize();
		planes[PLANE_DOWN].Normalize();
		planes[PLANE_NEAR].Normalize();
		planes[PLANE_FAR].Normalize();
	}
}


// inline bool cFrustum::testRect(
// 							   const cRect3d& rect) const
// {
// 
// 	if ((planeClassify(rect, leftPlane)		
// 		== k_plane_back)
// 		|| (planeClassify(rect, rightPlane) 
// 		== k_plane_back)
// 		|| (planeClassify(rect, topPlane)	
// 		== k_plane_back)
// 		|| (planeClassify(rect, bottomPlane)
// 		== k_plane_back)
// 		|| (planeClassify(rect, nearPlane)	
// 		== k_plane_back)
// 		|| (planeClassify(rect, farPlane)	
// 		== k_plane_back))
// 	{
// 		return false;
// 	}
// 
// 	return true;
// }

inline OVector3 ClipEdgeZ(const OVector3& v0, const OVector3& v1, float clipZ)
{
	return OVector3(
		v1.x + (v0.x - v1.x) * ((clipZ - v1.z) / (v0.z - v1.z)),
		v1.y + (v0.y - v1.y) * ((clipZ - v1.z) / (v0.z - v1.z)),
		clipZ
		);
}

void ProjectAndMergeEdge(OVector3 v0, OVector3 v1, ORect& rect, const OMatrix4x4& projection)
{
// 	Check if both vertices behind near plane
// 		if (v0.z_ < M_MIN_NEARCLIP && v1.z_ < MIN_NEARCLIP)
// 			return;
// 	
// 		// Check if need to clip one of the vertices
// 		if (v1.z_ < M_MIN_NEARCLIP)
// 			v1 = ClipEdgeZ(v1, v0, M_MIN_NEARCLIP);
// 		else if (v0.z_ < M_MIN_NEARCLIP)
// 			v0 = ClipEdgeZ(v0, v1, M_MIN_NEARCLIP);
// 	
// 		// Project, perspective divide and merge
// 		Vector3 tV0(projection * v0);
// 		Vector3 tV1(projection * v1);
// 		rect.Merge(Vector2(tV0.x_, tV0.y_));
// 		rect.Merge(Vector2(tV1.x_, tV1.y_));
}




void OFrustum::InitOrtho(float orthoSize, float aspectRatio, float zoom, float nearZ, float farZ, const OMatrix3x4& transform)
{
// 	nearZ = Max(nearZ, 0.0f);
// 	farZ = Max(farZ, nearZ);
// 	float halfViewSize = orthoSize * 0.5f / zoom;
// 	Vector3 near, far;
// 
// 	near.z_ = nearZ;
// 	far.z_ = farZ;
// 	far.y_ = near.y_ = halfViewSize;
// 	far.x_ = near.x_ = near.y_ * aspectRatio;
// 
// 	Define(near, far, transform);
}

void OFrustum::Transform(const OMatrix3x3& transform)
{
	for (unsigned i = 0; i < ONLY_FRUSTUM_VERTICES_NUM; ++i)
		vertices[i] = transform * vertices[i];

	UpdatePlanes();
}

void OFrustum::Transform(const OMatrix3x4& transform)
{
	for (unsigned i = 0; i < ONLY_FRUSTUM_VERTICES_NUM; ++i)
		//vertices[i] = transform * vertices[i];

	UpdatePlanes();
}

OFrustum OFrustum::Transformed(const OMatrix3x3& transform) const
{
	OFrustum transformed;
	for (unsigned i = 0; i < ONLY_FRUSTUM_VERTICES_NUM; ++i)
		transformed.vertices[i] = transform * vertices[i];

	transformed.UpdatePlanes();
	return transformed;
}

OFrustum OFrustum::Transformed(const OMatrix3x4& transform) const
{
	OFrustum transformed;
	for (unsigned i = 0; i < ONLY_FRUSTUM_VERTICES_NUM; ++i)
		//transformed.vertices[i] = transform * vertices[i];

	transformed.UpdatePlanes();
	return transformed;
}

ORect OFrustum::Projected(const OMatrix4x4& projection) const
{
	ORect rect;

	ProjectAndMergeEdge(vertices[0], vertices[4], rect, projection);
	ProjectAndMergeEdge(vertices[1], vertices[5], rect, projection);
	ProjectAndMergeEdge(vertices[2], vertices[6], rect, projection);
	ProjectAndMergeEdge(vertices[3], vertices[7], rect, projection);
	ProjectAndMergeEdge(vertices[4], vertices[5], rect, projection);
	ProjectAndMergeEdge(vertices[5], vertices[6], rect, projection);
	ProjectAndMergeEdge(vertices[6], vertices[7], rect, projection);
	ProjectAndMergeEdge(vertices[7], vertices[4], rect, projection);

	return rect;
}


