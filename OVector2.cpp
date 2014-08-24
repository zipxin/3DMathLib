#include "stdafx.h"
#include "../OInclude/Math/OVector2.h"


OVector2 g_Vector2f_Zero = OVector2(0.0f, 0.0f);
OVector2 g_Vector2f_One = OVector2(1.0f, 1.0f);
OVector2 g_Vector2f_MinusOne = OVector2(-1.0f, -1.0f);
OVector2 g_Vector2_AbsMask = OVector2( (unsigned int)0x7fffffff );
OVector2 g_Vector2_SignMask = OVector2 ((unsigned int)0x80000000 );

const OVector2 OVector2::X_AXIS( 1, 0);
const OVector2 OVector2::Y_AXIS( 0, 1);
const OVector2 OVector2::NEG_X_AXIS( -1,  0);
const OVector2 OVector2::NEG_Y_AXIS(  0, -1);


const OVector2 OVector2::ZERO(0.0f, 0.0f);
const OVector2 OVector2::LEFT(-1.0f, 0.0f);
const OVector2 OVector2::RIGHT(1.0f, 0.0f);
const OVector2 OVector2::UP(0.0f, 1.0f);
const OVector2 OVector2::DOWN(0.0f, -1.0f);
const OVector2 OVector2::ONE(1.0f, 1.0f);


OVector2 TempVector2List[256];
int TempVector2ListIndex = 0;


float32 OVector2::GetRadianBetween2Vector2(OVector2 src, OVector2 dest)
{
	float32 srcR, destR;
	if (src.x == 0){
		if (src.y >= 0)
			srcR = PI/2;
		else
			srcR = -PI/2;
	}
	else
	{
		srcR = atanf(src.y/src.x);
		if (src.x < 0)
			srcR += PI;
	}


	if (dest.x == 0){
		if (dest.y >= 0)
			destR = PI/2;
		else
			destR = -PI/2;
	}
	else
	{
		destR = atanf(dest.y/dest.x);
		if (dest.x < 0)
			destR += PI;
	}


	float btwR = srcR - destR;
	if (btwR > PI)
		btwR -= 2 * PI;
	else if (btwR < -PI)
		btwR += 2 * PI;

	return btwR;
}
