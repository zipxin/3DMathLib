//////////////////////////////////////////////////////////////////////////
//File : Only Rect ( Only Math Lib)
//Author : Zipxin  [China]
//Project : OnlyGameEngine
//E-mail: zipxin@163.com
//////////////////////////////////////////////////////////////////////////
#ifndef _ONLY_RECT_H_
#define _ONLY_RECT_H_

#if _MSC_VER > 1000
#pragma once
#endif 

#include "../OInclude/Common/OnlyGameDefine.h"

#include "../OInclude/Math/OMathUtil.h"
#include <stdio.h>

#include "../OInclude/Math/OVector2.h"
#include "../OInclude/Math/OVector4.h"


class ORect
{
	friend class OBoundingBox;
protected:
	OVector2 min;
	OVector2 max;
	bool     isInited;
public:
	static const ORect FULL;
	static const ORect POSITIVE;
	static const ORect ZERO;
//-----构造器
	ORect() : min(OVector2::ZERO),max(OVector2::ZERO), isInited(false){}

	ORect(const ORect& rect) : min(rect.min), max(rect.max), isInited(rect.isInited){}

	ORect(const OVector2& _min, const OVector2& _max) :min(_min),max(_max),isInited(true) {}

	ORect(float32 left, float32 top, float32 right, float32 bottom) : min(left, top),max(right, bottom),isInited(true){}

	explicit ORect(const OVector4& vector) :min(vector.x, vector.y), max(vector.z, vector.w),
		isInited(true) {}


//----Operator
	ORect& operator = (const ORect& rhs)
	{
		min = rhs.min;
		max = rhs.max;
		isInited = rhs.isInited;
		return *this;
	}

	bool operator == (const ORect& rhs) const 
	{ 
		return min == rhs.min && max == rhs.max; 
	}
	
	bool operator != (const ORect& rhs) const 
	{
		return min != rhs.min || max != rhs.max; 
	}


//-----Init
	void Init(const ORect& rect)
	{
		min = rect.min;
		max = rect.max;
		isInited = true;
	}

	void Init(const OVector2& _min, const OVector2& _max)
	{
		min = _min;
		max = _max;
		isInited = true;
	}

	void Init(const OVector2& point)
	{
		min = max = point;
		isInited = true;
	}

//------function
	OVector2 Center() const { return (max + min) * 0.5f; }
	OVector2 Size() const { return max - min; }
	OVector2 HalfSize() const { return (max - min) * 0.5f; }

	void Clear()
	{
		min = OVector2::ZERO;
		max = OVector2::ZERO;
		isInited = false;
	}

	float32 Width() const { return Size().x; }

	float32 Height() const { return Size().y; }

	bool    Equals(const ORect& rhs) const { return min.Equals(rhs.min) && max.Equals(rhs.max); }

	void    Clip(const ORect& rect);


	Intersection IsInside(const OVector2& point) const
	{
		if ( point.x < min.x || point.y < min.y || point.x > max.x || point.y > max.y )
			return OUTSIDE;
		else
			return INSIDE;
	}

	void Merge(const OVector2& point)
	{
		if (!isInited)
		{
			min = max = point;
			isInited = true;
		}

		if (point.x < min.x)
			min.x = point.x;
		if (point.x > max.x)
			max.x = point.x;
		if (point.y < min.y)
			min.y = point.y;
		if (point.y > max.y)
			max.y = point.y;
	}

	void Merge(const ORect& rect)
	{
		if (!isInited)
		{
			min = rect.min;
			max = rect.max;
			isInited = true;
		}

		if (rect.min.x < min.x)
			min.x = rect.min.x;
		if (rect.min.y < min.y)
			min.y = rect.min.y;
		if (rect.max.x > max.x)
			max.x = rect.max.x;
		if (rect.max.y > max.y)
			max.y = rect.max.y;
	}

	OVector4 ToVector4() const { return OVector4(min.x, min.y, max.x, max.y); }


//------Display
	inline const char* ToCString() const 
	{
		char *buf = new char[128];
		memset(buf, 0 , 128);
		sprintf_s(buf, 128, "RECT: (%5.2f,%5.2f,%5.2f,%5.2f)\n", min.x, min.y, max.x, max.y);
		return buf;
	}

	inline const wchar_t* ToWString() const 
	{
		wchar_t *buf = new wchar_t[128];
		memset(buf, 0 , 128);
		swprintf_s(buf, 128, L"RECT: (%5.2f,%5.2f,%5.2f,%5.2f)\n", min.x, min.y, max.x, max.y);
		return buf;
	}

	/** 重载<<运算符，可以将二维向量按照Vector2(x,y)的格式输出 */
	inline friend std::ostream& operator <<	( std::ostream& o, const ORect& v )
	{
		o <<"RECT: ("<<v.min.x<<","<<v.min.y<<","<<v.max.x<<","<<v.max.y<<")";
		return o;
	}

	inline void StoreToArrayf(float32 *p) const 
	{
		p[0] = min.x;
		p[1] = min.y;
		p[2] = max.x;
		p[3] = max.y;
	}
};

#endif