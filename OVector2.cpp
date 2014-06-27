#include "OVector2.h"


OVector2 g_Vector2f_Zero = OVector2(0.0f, 0.0f);
OVector2 g_Vector2f_One = OVector2(1.0f, 1.0f);
OVector2 g_Vector2f_MinusOne = OVector2(-1.0f, -1.0f);
OVector2 g_Vector2_AbsMask = OVector2( (unsigned int)0x7fffffff );
OVector2 g_Vector2_SignMask = OVector2 ((unsigned int)0x80000000 );


OVector2 TempVector2List[256];
int TempVector2ListIndex = 0;