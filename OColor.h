//////////////////////////////////////////////////////////////////////////
//File : Only Color ( Only Math Lib)
//Author : Zipxin  [China]
//E-mail: zipxin@163.com
//Project : OnlyGameEngine
//////////////////////////////////////////////////////////////////////////
#ifndef _ONLY_COLOR_H_
#define _ONLY_COLOR_H_

#if _MSC_VER > 1000
#pragma once
#endif 

#include "../OInclude/Common/OnlyGameDefine.h"

#include "../OInclude/Math/OVector4.h"
#include "../OInclude/Math/OVector3.h"

#include <assert.h>

typedef uint32 RGBA;
typedef uint32 ARGB;

class  OColor
{
public:
	float32 r;
	float32 g;
	float32 b;
	float32 a;
public:
	OColor(): r(1.0f), g(1.0f), b(1.0f), a(1.0f){}

	OColor(const OColor& color):r(color.r),g(color.g),
	  b(color.b), a(color.a) {}

	OColor(const OColor& color, float _a):r(color.r), g(color.g),
	  b(color.b), a(_a){}

	OColor(float r, float g, float b) : r(r), g(g), b(b), a(1.0f) {}

	OColor(float32 _r, float32 _g, float32 _b, float32 _a) :
	r(_r),g(_g),b(_b),a(_a){}

	OColor(const float32* data) :
	r(data[0]),g(data[1]),b(data[2]),a(data[3]){}

	OVector3 ToVector3() const { return OVector3(r, g, b); }
	OVector4 ToVector4() const { return OVector4(r, g, b, a); }

	bool operator == (const OColor& rhs) const { return OEquals(r, rhs.r) && OEquals(g, rhs.g) && OEquals(b, rhs.b) && OEquals(a, rhs.a); }
	bool operator != (const OColor& rhs) const { return !OEquals(r, rhs.r) || !OEquals(g, rhs.g) || !OEquals(b, rhs.b) || !OEquals(a, rhs.a); }
	OColor operator * (float rhs) const { return OColor(r * rhs, g * rhs, b * rhs, a * rhs); }
	OColor operator + (const OColor& rhs) const { return OColor(r + rhs.r, g + rhs.g, b + rhs.b, a + rhs.a); }
	OColor operator - (const OColor& rhs) const { return OColor(r - rhs.r, g - rhs.g, b - rhs.b, a - rhs.a); }

	inline void operator = ( const OColor& color )
	{
		r = color.r;
		g = color.g;
		b = color.b;
		a = color.a;
	}

	OColor& operator += (const OColor& rhs)
	{
		r += rhs.r;
		g += rhs.g;
		b += rhs.b;
		a += rhs.a;
		return *this;
	}

	inline OColor operator * ( const OColor& rhs) const
	{
		OColor kProd;

		kProd.r = rhs.r * r;
		kProd.g = rhs.g * g;
		kProd.b = rhs.b * b;
		kProd.a = rhs.a * a;

		return kProd;
	}

	inline OColor operator / ( const OColor& rhs) const
	{
		assert(rhs.r != 0.0f);
		assert(rhs.g != 0.0f);
		assert(rhs.b != 0.0f);
		assert(rhs.a != 0.0f);
		OColor kProd;

		kProd.r = rhs.r / r;
		kProd.g = rhs.g / g;
		kProd.b = rhs.b / b;
		kProd.a = rhs.a / a;

		return kProd;
	}

	inline OColor operator / (const float32 fScalar ) const
	{
		assert( fScalar != 0.0 );

		OColor kDiv;

		float fInv = 1.0f / fScalar;
		kDiv.r = r * fInv;
		kDiv.g = g * fInv;
		kDiv.b = b * fInv;
		kDiv.a = a * fInv;

		return kDiv;
	}

	inline friend OColor operator * (const float fScalar, const OColor& rkVector )
	{
		OColor kProd;

		kProd.r = fScalar * rkVector.r;
		kProd.g = fScalar * rkVector.g;
		kProd.b = fScalar * rkVector.b;
		kProd.a = fScalar * rkVector.a;

		return kProd;
	}


	inline OColor& operator -= ( const OColor& rkVector )
	{
		r -= rkVector.r;
		g -= rkVector.g;
		b -= rkVector.b;
		a -= rkVector.a;

		return *this;
	}
	inline OColor& operator *= (const float fScalar )
	{
		r *= fScalar;
		g *= fScalar;
		b *= fScalar;
		a *= fScalar;
		return *this;
	}

	inline OColor& operator /= (const float fScalar )
	{
		assert( fScalar != 0.0 );

		float fInv = 1.0f / fScalar;

		r *= fInv;
		g *= fInv;
		b *= fInv;
		a *= fInv;

		return *this;
	}


	const float* StoreToArrayf() const { return &r; }

	/// 反转颜色
	void Invert(bool invertAlpha = false);
	/// 对颜色进行差值运算
	OColor Lerp(const OColor& rhs, float t) const;

	/// 将颜色规范在 [0, 1.0] 范围.
	//clipAlphle 参数：是否对Alpha进行规范
	void Clip(bool clipAlpha = false);

	inline const char* ToCString()
	{
		char *buf = new char[128];
		memset(buf, 0 , 128);
		sprintf_s(buf, 128, "Color : (%5.2f,%5.2f,%5.2f,%5.2f)\n", r, g, b, a);
		return buf;
	}

	inline const wchar_t* ToWString()
	{
		wchar_t *buf = new wchar_t[128];
		memset(buf, 0 , 128);
		swprintf_s(buf, 128, L"Color: (%5.2f,%5.2f,%5.2f,%5.2f)\n", r, g, b, a);
		return buf;
	}


	/// Return sum of RGB components.
	float SumRGB() const { return r + g + b; }
	/// Return average value of the RGB channels.
	float Average() const { return (r + g + b) * 0.333333333f; }

	RGBA GetRGBA() const;
	ARGB GetARGB() const;

	void SetFromRGBA(const RGBA color);
	void SetFromARGB(const ARGB color);

	inline void StoreToArrayf(float32 *p) const 
	{
		p[0] = r;
		p[1] = g;
		p[2] = b;
		p[3] = a;
	}

	/** 重载运算符 << 输出颜色 */
	inline friend std::ostream& operator<< (std::ostream& o, OColor& c)
	{
		o << "Color ( r:"<<  c.r << ", g:" << c.g <<", b:"<<c.b <<", a:"<<c.a<< ")";
		return o;
	}
public:
	static const OColor WHITE;
	static const OColor GRAY;
	static const OColor BLACK;
	static const OColor RED;
	static const OColor GREEN;
	static const OColor BLUE;
	static const OColor CYAN;
	static const OColor MAGENTA;
	static const OColor YELLOW;
	static const OColor TRANSPARENT;
};

#endif /*File Is Over*/