#include "stdafx.h"
#include "../OInclude/Math/OVector4.h"
#include "../OInclude/Math/OMatrix4x4.h"

OVector4 g_Vector4f_Zero = OVector4(0.0f, 0.0f, 0.0f, 0.0f);
OVector4 g_Vector4f_One = OVector4(1.0f, 1.0f, 1.0f, 1.0f);
OVector4 g_Vector4f_MinusOne = OVector4(-1.0f, -1.0f, -1.0f, -1.0f);
OVector4 g_Vector4_AbsMask = OVector4( (unsigned int)0x7fffffff );
OVector4 g_Vector4_SignMask = OVector4 ((unsigned int)0x80000000 );


OVector4 TempVector4List[256];
int TempVector4ListIndex = 0;

OVector4 &OVector4::operator *(const OMatrix4x4& mat)
{
	OVector4 *v = GetNextTempVector4();
	v->x = mat[0][0] * x + mat[1][0] * y + mat[2][0] * z + mat[3][0] * w;
	v->y = mat[0][1] * x + mat[1][1] * y + mat[2][1] * z + mat[3][1] * w;
	v->z = mat[0][2] * x + mat[1][2] * y + mat[2][2] * z + mat[3][2] * w;
	v->w = mat[0][3] * x + mat[1][3] * y + mat[2][3] * z + mat[3][3] * w;
	return *v;
}