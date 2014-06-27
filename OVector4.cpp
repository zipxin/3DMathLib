#include "OVector4.h"


OVector4 g_Vector4f_Zero = OVector4(0.0f, 0.0f, 0.0f, 0.0f);
OVector4 g_Vector4f_One = OVector4(1.0f, 1.0f, 1.0f, 1.0f);
OVector4 g_Vector4f_MinusOne = OVector4(-1.0f, -1.0f, -1.0f, -1.0f);
OVector4 g_Vector4_AbsMask = OVector4( (unsigned int)0x7fffffff );
OVector4 g_Vector4_SignMask = OVector4 ((unsigned int)0x80000000 );


OVector4 TempVector4List[256];
int TempVector4ListIndex = 0;