#ifndef __ONLY_MATHUTIL_H__
#define __ONLY_MATHUTIL_H__

#ifndef _INCLUDE_MATH_H_
#	define _INCLUDE_MATH_H_
#	include <math.h>
#endif

#include <assert.h>
#include "../OInclude/Common/OnlyGamedefine.h"


#define PI         ((float)3.141592654f)
#define PI2        ((float)6.283185307f)
#define PI_DIV_2   ((float)1.570796327f)
#define PI_DIV_4   ((float)0.785398163f) 
#define PI_INV     ((float)0.318309886f) 

#define RAD_TO_DEG  ((float)57.29577951f)
#define DEG_TO_RAD  ((float)0.017453293f)

static const float DEGTORAD   = (float)PI / 180.0f;
//相当于弧度除以2，在四元数中应用较多
static const float DEGTORAD_2 = (float)PI / 360.0f; // M_DEGTORAD / 2.f



#define EPSILON4     ((float)1E-4)
#define EPSILON6     ((float)1E-6)
#define EPSILON8     ((float)1E-8)

static const int MIN_INT = 0x80000000;
static const int MAX_INT = 0x7fffffff;

static const unsigned MIN_UINT = 0x00000000;
static const unsigned MAX_UINT = 0xffffffff;

static const float   EPSILON = 0.000001f;

static const int32	   MIN_INT32   =   (int32)0xffffffff; // (-2147483646);
static const int32	   MAX_INT32   =   (int32)0x7fffffff; // ( 2147483647);
static const int16	   MIN_INT16   =   (int16)0xffff; // (-32768);
static const int16	   MAX_INT16   =   (int16)0x7fff; // ( 32767);
static const int8	   MIN_INT8    =   (int8)0xff; // (-128);
static const int8	   MAX_INT8    =   (int8)0x7f; // ( 127);
static const uint32   MIN_UINT32  =   (uint32)0;
static const uint32   MAX_UINT32  =   (uint32)0xffffffff;
static const uint16   MIN_UINT16  =   (uint16)0;
static const uint16   MAX_UINT16  =   (uint16)0xffff;
static const uint8	   MIN_UINT8   =   (uint8)0;
static const uint8	   MAX_UINT8   =   (uint8)0xff;
// 
static const float	 MAX_REAL32  =   static_cast<float>(3.4E+38);
static const float	 MIN_REAL32  =   static_cast<float>(-3.4E+38);
static const float	 TINY_REAL32  =   static_cast<float>(3.4E-38);

static const float INFINITY = (float)HUGE_VAL;

enum Intersection
{
	OUTSIDE,
	INTERSECTS,
	INSIDE
};

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
	return lh > OMin2<T>(mh, rh)  ?  OMin2<T>(mh, rh) : lh;
}

template <typename T>
T OMax3(const T& lh, const T& mh,const T& rh)
{
	return lh < OMax2<T>(mh, rh)  ?  OMax2<T>(mh, rh) : lh;
}

inline float Lerp(float32 lhs, float32 rhs, float32 t) 
{
	return lhs * (1.0f - t) + rhs * t; 
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

#define fpOneBits 0x3F800000
// reinterpret a float as an int32
#define fpBits(f) (*reinterpret_cast<const int32*>(&(f))) 
// reinterpret an int32 as a float
#define intBits(i) (*reinterpret_cast<const float*>(&(i))) 
inline float OInverse(float value)
{
	int _i = 2 * fpOneBits - fpBits(value);                                 
	float r = intBits(_i);                                                       
	return fpBits(value) ? (r * (2.0f - (value) * r)) : 0;  
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

inline float32 OClamp(float32 value, float32 min, float32 max)
{
    if (value < min)
        return min;
    else if (value > max)
        return max;
    else
        return value;
}

/// Return the sign of a float (-1, 0 or 1.)
inline float OSign(float value) 
{ 
	return value > 0.0f ? 1.0f : (value < 0.0f ? -1.0f : 0.0f); 
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

inline bool OEquals(float lhs, float rhs) 
{
	return lhs + EPSILON >= rhs && lhs - EPSILON <= rhs; 
}

/// Update a hash with the given 8-bit value using the SDBM algorithm.
inline uint32 SDBMHash(uint32 hash, uint8 c) 
{ 
	return c + (hash << 6) + (hash << 16) - hash;
}


#endif/* File Is Over */