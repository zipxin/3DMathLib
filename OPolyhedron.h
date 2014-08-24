#ifndef _ONLY_POLYHEDRON_H_
#define _ONLY_POLYHEDRON_H_

#if _MSC_VER > 1000
#pragma once
#endif 

#include "../OInclude/Common/OnlyGameDefine.h"

class OPolyhedron
{
private:
	/// Set a triangle face by index.
	void SetFace(unsigned index, const OVector3& v0, const OVector3& v1, const OVector3& v2);
	/// Set a quadrilateral face by index.
	void SetFace(unsigned index, const OVector3& v0, const OVector3& v1, const OVector3& v2, const OVector3& v3);
	/// Internal vector for clipped vertices.
	OVector<OVector3> m_clippedVertices;
	/// Internal vector for the new face being constructed.
	OVector<OVector3> m_outFace;
	/// Polygon faces.
	OVector<OVector<OVector3> > m_faces;
public:
	/// Construct empty.
	OPolyhedron()
	{
	}

	/// Copy-construct from another polyhedron.
	OPolyhedron(const OPolyhedron& polyhedron) :
	m_faces(polyhedron.m_faces)
	{
	}

	/// Construct from a list of faces.
	OPolyhedron(const OVector<OVector<OVector3> >& faces) :
	m_faces(faces)
	{
	}

	/// Construct from a bounding box.
	OPolyhedron(const OBoundingBox& box)
	{
		Init(box);
	}

	/// Construct from a frustum.
	OPolyhedron(const OFrustum& frustum)
	{
		Init(frustum);
	}

	/// Destruct.
	~OPolyhedron();

	/// Init from a bounding box.
	void Init(const OBoundingBox& box);
	/// Init from a frustum.
	void Init(const OFrustum& frustum);
	/// Add a triangle face.
	void AddFace(const OVector3& v0, const OVector3& v1, const OVector3& v2);
	/// Add a quadrilateral face.
	void AddFace(const OVector3& v0, const OVector3& v1, const OVector3& v2, const OVector3& v3);
	/// Add an arbitrary face.
	void AddFace(const OVector<OVector3>& face);
	/// Clip with a plane.
	void Clip(const OPlane& plane);
	/// Clip with a bounding box.
	void Clip(const OBoundingBox& box);
	/// Clip with a frustum.
	void Clip(const OFrustum& box);
	/// Clear all faces.
	void Clear();
	/// Transform with a 3x3 matrix.
	void Transform(const OMatrix3x3& transform);
	/// Transform with a 3x4 matrix.
	void Transform(const OMatrix3x4& transform);

	/// Return transformed with a 3x3 matrix.
	OPolyhedron Transformed(const OMatrix3x3& transform) const;
	/// Return transformed with a 3x4 matrix.
	OPolyhedron Transformed(const OMatrix3x4& transform) const;
	/// Return whether is empty.
	bool Empty() const { return m_faces.empty(); }

};


#endif/*File Is Over*/