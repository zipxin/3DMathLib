#ifndef __ONLY_MATHUTIL_H__
#define __ONLY_MATHUTIL_H__

#ifndef _INCLUDE_MATH_H_
#	define _INCLUDE_MATH_H_
#	include <math.h>
#endif
#include <assert.h>
#include "OnlyGameDefine.h"


#define PI         ((float)3.141592654f)
#define PI2        ((float)6.283185307f)
#define PI_DIV_2   ((float)1.570796327f)
#define PI_DIV_4   ((float)0.785398163f) 
#define PI_INV     ((float)0.318309886f) 

#define RAD_TO_DEG  ((float)57.29577951f)
#define DEG_TO_RAD  ((float)0.017453293f)


#define EPSILON4     ((float)1E-4)
#define EPSILON6     ((float)1E-6)
#define EPSILON8     ((float)1E-8)


template <typename T>
T OMin2(const T& lh, const T& rh)
{
	return lh > rh  ? rh : lh;
}

template <typename T>
T OMax2(const T& lh, const T& rh)
{
	return lh > rh  ? lh : rh;
}

template <typename T>
T OMin3(const T& lh, const T& mh,const T& rh)
{
	return lh > Min2<T>(mh, rh)  ?  Min2<T>(mh, rh) : lh;
}

template <class T>
void OSwap(T& lh, T& rh)
{
	T temp = lh;
	lh = rh;
	rh = temp;
}

template <typename T>
inline T OAbs(T value)
{
	return abs(value);	
}

inline float32 OAbs(float32 value)
{
	int32 temp = *reinterpret_cast<const int32*>(&(value));
	temp &= 0x7fffffff;
	return *reinterpret_cast<const float32*>(&temp);
}

inline float32 OSqrt(float32 value)
{
	float32 res = sqrt(value);
	return res;
}

//暂时这么写
//以后通过查表啊,FPU啊等增加效率
inline float32 OCot(float32 radian)
{
	assert(radian != 0);
	return (float32)1/tan((float32) radian);
}

inline float32 OSin(float32 radian)
{
	return (float32)sin(radian);
}

inline float32 OCos(float32 radian)
{
	return (float32)cos(radian);
}

#endif/* File Is Over */