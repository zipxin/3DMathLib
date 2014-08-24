#include "stdafx.h"
#include "../OInclude/Math/OVector3.h"
#include "../OInclude/Math/OMatrix4x4.h"

OVector3 g_Vector3f_Zero = OVector3(0.0f, 0.0f, 0.0f);
OVector3 g_Vector3f_One = OVector3(1.0f, 1.0f, 1.0f);
OVector3 g_Vector3f_MinusOne = OVector3(-1.0f, -1.0f, -1.0f);
OVector3 g_Vector3_AbsMask = OVector3( (unsigned int)0x7fffffff );
OVector3 g_Vector3_SignMask = OVector3 ((unsigned int)0x80000000 );

const OVector3 OVector3::ZERO(0.0f, 0.0f, 0.0f);
const OVector3 OVector3::LEFT(-1.0f, 0.0f, 0.0f);
const OVector3 OVector3::RIGHT(1.0f, 0.0f, 0.0f);
const OVector3 OVector3::UP(0.0f, 1.0f, 0.0f);
const OVector3 OVector3::DOWN(0.0f, -1.0f, 0.0f);
const OVector3 OVector3::FORWARD(0.0f, 0.0f, 1.0f);
const OVector3 OVector3::BACK(0.0f, 0.0f, -1.0f);
const OVector3 OVector3::ONE(1.0f, 1.0f, 1.0f);

OVector3 TempVector3List[256];
int32    TempVector3ListIndex = 0;




// OVector3 OVector3::GetNormal()
// {
// 	float fx = fabsf(x); 
// 	float fy = fabsf(y); 
// 	float fz = fabsf(z); 
// 	if(fx > fy && fx > fz) return OVector3(1,0,0); 
// 	if(fy > fx && fy > fz) return OVector3(0,1,0); 
// 	if(fz > fx && fz > fy) return OVector3(0,0,1); 
// 
// 	return OVector3(0,0,0);
// }



// OVector3 OVector3::NormalFromTriangle(const OVector3& v0, const OVector3& v1, const OVector3& v2)
// {
// 	OVector3 n1, n2;
// 	n1 = v1-v0;n2 = v2-v0;
// 	return Vec3_CrossProduct(n1,n2);
// }

// 
// 
// 
OVector3 OVector3::operator * ( const OMatrix4x4 &m ) const
{
	OVector3 r;

	float fInvW = 1.0f / ( m[0][3] * x + m[1][3] * y + m[2][3] * z + m[3][3] );

	r.x = ( m[0][0] * x + m[1][0] * y + m[2][0] * z + m[3][0] ) * fInvW;
	r.y = ( m[0][1] * x + m[1][1] * y + m[2][1] * z + m[3][1] ) * fInvW;
	r.z = ( m[0][2] * x + m[1][2] * y + m[2][2] * z + m[3][2] ) * fInvW;

	return r;
}



/// FIXME: Hacky and slow
OVector3 MakeDirection(float yaw, float pitch, float roll)
{
	//Convert from degrees to radians
	roll  *=DEG_TO_RAD;
	pitch *=DEG_TO_RAD;
	yaw   *=DEG_TO_RAD;

	double X = (sinf(pitch)*sinf(yaw)*sinf(roll))+ (cosf(pitch)*cosf(roll));
	double Y = cosf(yaw)*sinf(roll);
	double Z = (sinf(pitch)*cosf(roll))- (cosf(roll)*sinf(pitch)*sinf(yaw));

	return OVector3((float)X,(float)Y,(float)Z).Nomarlized();
}



// float OVector3::DistanceToLine(const OVector3& p0, const OVector3& p1) const
// {
// 	OVector3 p0_to_p = *this - p0;
// 	OVector3 p0_to_p1 = p1 - p0;
// 
// 	OVector3 p_on_line = p0_to_p.ProjectionOntoVector(p0_to_p1);
// 	OVector3 perp	  = p0_to_p - p_on_line;
// 
// 	return perp.Length();
// }

