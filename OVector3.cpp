#include "OVector3.h"


OVector3 g_Vector3f_Zero = OVector3(0.0f, 0.0f, 0.0f);
OVector3 g_Vector3f_One = OVector3(1.0f, 1.0f, 1.0f);
OVector3 g_Vector3f_MinusOne = OVector3(-1.0f, -1.0f, -1.0f);
OVector3 g_Vector3_AbsMask = OVector3( (unsigned int)0x7fffffff );
OVector3 g_Vector3_SignMask = OVector3 ((unsigned int)0x80000000 );


OVector3 TempVector3List[256];
int TempVector3ListIndex = 0;