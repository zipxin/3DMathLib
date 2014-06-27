//////////////////////////////////////////////////////////////////////////
//File : Only Vector2 ( Only Math Lib )
//Author : Zipxin  [China]
//Project : OnlyGameEngine
//////////////////////////////////////////////////////////////////////////
#ifndef __OM_VECTOR2_H__
#define __OM_VECTOR2_H__

#include "OnlyGameDefine.h"

#include "OMathUtil.h"
#include <stdio.h>
#include <assert.h>

//////////////////////////////////////////////////////////////////////////
//Construct
//////////////////////////////////////////////////////////////////////////
//Getter Setter
//////////////////////////////////////////////////////////////////////////
//Store
//////////////////////////////////////////////////////////////////////////
//Function
//////////////////////////////////////////////////////////////////////////
//Operator 
//////////////////////////////////////////////////////////////////////////
//static Function
//////////////////////////////////////////////////////////////////////////


//Declare/////////////////////////////////////////////////////////////////
class OVector2;


//////////////////////////////////////////////////////////////////////////
//Global
//////////////////////////////////////////////////////////////////////////
extern OVector2 g_Vector2f_Zero;
extern OVector2 g_Vector2f_One;

//Define//////////////////////////////////////////////////////////////////
class OVector2
{
private :
	union 
	{
		struct 
		{
			float32 x, y;
		};
		float32 elem_f[2];
		int32   elem_i[2];
	};
public :
	inline OVector2(){};

	inline OVector2(float32 ix, float32 iy):x(ix),y(iy){}

	inline OVector2(const OVector2 &a):x(a.x),y(a.y){}

	inline OVector2(float32 f):x(f),y(f){}


	inline OVector2(int32 x, int32 y)
	{
		elem_i[0] = x;
		elem_i[1] = y;
	}

	inline OVector2( uint32 value )
	{
		elem_i[0] = value;
		elem_i[1] = value;
	}


	//////////////////////////////////////////////////////////////////////////
	inline void Set(float x, float y)
	{
		this->x = x;
		this->y = y;
	}

	inline void Set(float value)
	{
		this->x = value;
		this->y = value;
	}

	inline void Set(float *p)
	{
		this->x = p[0];
		this->y = p[1];
	}

	inline void SetX(float x)
	{
		this->x = x;
	}

	inline float32 GetXf() { return x; }

	inline float32 GetYf() { return y; }



	inline OVector2 GetXXf(void)
	{
		OVector2 result(x);
		return result;
	}


	inline OVector2 GetYYf(void)
	{
		OVector2 result(y);
		return result;
	}


	inline void SetY(float y)
	{
		this->y = y;
	}

	
	inline void SetXY(float *p)
	{
		x = p[0];
		y = p[1];
	}
	//////////////////////////////////////////////////////////////////////////
	//存放在数组p中，值为float类型
	inline void StoreToArrayf(float *p)
	{
		p[0] = x;
		p[1] = y;
	}

	inline void StoreToArrayf(int *p)
	{
		p[0] = (int)x;
		p[1] = (int)y;
	}

	inline void StoreToArrayi(int *p)
	{
		p[0] = elem_i[0];
		p[1] = elem_i[1];
	}

	//////////////////////////////////////////////////////////////////////////

	inline OVector2& InvertSign()
	{
		x = -x;
		y = -y;
		return *this;
	}

	inline float32 Length()
	{
		float32 res = 0.0f;
		float32 sum = x*x + y*y;// + w*w;
		res = OSqrt(sum);
		return res;
	}	

	inline float32 LengthNotSqrt()
	{
		return x*x + y*y;
	}	


	inline void Display()
	{
		printf("Vector 2: ( %5.2f,%5.2f )\n", x, y);
	}

	//将元素绝对值化
	inline OVector2 &Abs()
	{
		x = OAbs(x);
		y = OAbs(y);
		return *this;
	}

	inline float32 NormalizeAndGetLength(void)
	{
		float32 len = Length();
		float32 returnlen = len;
		if(len > 0.0f )
		{
			len = 1.0f / len;
		}else
		{
			len = 0.0f;
		}
		x *= len;
		y *= len;
		return returnlen;
	}

	//对元素求倒数
	inline void Reciprocal(void)
	{
		x = 1.0f/x;
		y = 1.0f/y;
	}


	inline void Nomarlize()
	{
		float32 len = Length();
		if(len > 0.0f )
		{
			len = 1.0f / len;
		}else
		{
			len = 0.0f;
		}
		x *= len;
		y *= len;
	}

	//饱和处理
	inline OVector2 &Saturate(void)
	{
		if ( x > 1.0f ) x = 1.0f;
		if ( y > 1.0f ) y = 1.0f;

		if ( x < 0.0f ) x = 0.0f;
		if ( y < 0.0f ) y = 0.0f;

		return *this;
	}
	inline OVector2 &Clamp_to_0(void)
	{
		if ( x < 0.0f ) x = 0.0f;
		if ( y < 0.0f ) y = 0.0f;

		return *this;
	}

	inline OVector2 &Clamp_to_1(void)
	{
		if ( x > 1.0f ) x = 1.0f;
		if ( y > 1.0f ) y = 1.0f;

		return *this;
	}

	inline OVector2 &Floor(void)
	{
		x = floor(x);
		y = floor(y);
		return *this;
	}

	//////////////////////////////////////////////////////////////////////////
	/*Operator*/

public:

	inline static OVector2 &GetZero(void)
	{
		return g_Vector2f_Zero;
	}

	inline static OVector2 &GetOne(void)
	{
		return g_Vector2f_One;
	}



public:

	inline OVector2& operator *= (float32 value)
	{
		x *= value;
		y *= value;
		return *this;
	}
	inline OVector2 operator =(const OVector2 &value)
	{
		x = value.x;
		y = value.y;
		return *this;
	}


	inline OVector2 &operator+=(OVector2 &rhs)
	{
		x += rhs.x;
		y += rhs.y;
		return *this;
	}

	inline OVector2 &operator+=(float32 value)
	{
		x += value;
		y += value;
		return *this;
	}

	inline OVector2 &operator=(float32 value)
	{
		Set(value);
		return *this;
	}

	inline bool operator ==(const OVector2 &value) const 
	{
		return x==value.x && y == value.y ;
	}

	inline bool operator !=(const OVector2 &value) const 
	{
		return x!=value.x||y!=value.y;
	}

	inline OVector2 operator -=(const OVector2 &value) const 
	{
		OVector2 result;
		result.x = x - value.x;
		result.y = y - value.y;

		return result;
	}



	inline OVector2 operator-() const
	{
		return OVector2(-x,-y);
	}


	inline OVector2 &operator/=(float32 value)
	{
		x /= value;
		y /= value;
		return *this;
	}


	inline float32 &operator[](int32 index)
	{
		assert(index < 2 && index >= 0 &&"下标越界");
		return elem_f[index];
	}

	inline const float32 &operator[](int32 index) const
	{
		assert(index < 2 && index >= 0 &&"下标越界");
		return elem_f[index];
	}

	inline const tchar *GetVector2Info(void)
	{
		return _T("Vector2 : General , C++ , v 0.5.6");
	}

//////////////////////////////////////////////////////////////////////////
//Debug
	inline void Vec2_FPrint(FILE* file, const tchar* str) const 
	{
		_ftprintf(file, _T("%s Vector 2: <%f, %f>\n"), str, x, y);
	}

};



extern OVector2 TempVector2List[256];
extern int TempVector2ListIndex ;

inline OVector2* GetNextTempVector2()
{
	TempVector2ListIndex = (TempVector2ListIndex++) & 255;
	return &TempVector2List[TempVector2ListIndex];
}


inline OVector2 operator+(const OVector2 &a,const OVector2 &b)
{
	OVector2 *c = GetNextTempVector2();

	c->x = a.x + b.x;
	c->y = a.y + b.y;
	return *c;
}

inline OVector2 operator-(const OVector2 &a, const OVector2 &b)
{
	OVector2 *c = GetNextTempVector2();

	c->x = a.x - b.x;
	c->y = a.y - b.y;

	return *c;
}

inline OVector2 operator*(const float32 f, const OVector2 &v)
{
	OVector2 *result = GetNextTempVector2();

	result->x = f * v.x;
	result->y = f * v.y;

	return *result;
}

inline OVector2 operator*(const OVector2 &v, const float32 f)
{
	OVector2 *result = GetNextTempVector2();

	result->x = f * v.x;
	result->y = f * v.y;

	return *result;
}

inline float Vec2_Dotf(const OVector2 &a, const OVector2 &b)
{
	float result = a.x * b.x + a.y * b.y ;
	return result;
}


inline OVector2 Vec2_Lerp(const OVector2 &a, const OVector2 &b, const float32 t)
{
	OVector2 c = a + (b - a) * t;
	return c;
}

inline OVector2 Vec2_Max(const OVector2 &a, const OVector2 &b)
{
	OVector2 *c = GetNextTempVector2();

	c->x = a.x > b.x ? a.x : b.x;
	c->y = a.y > b.y ? a.y : b.y;

	return *c;
}


inline OVector2 Vec2_Min(const OVector2 &a, const OVector2 &b)
{
	OVector2 *c = GetNextTempVector2();

	c->x = a.x < b.x ? a.x : b.x;
	c->y = a.y < b.y ? a.y : b.y;

	return *c;
}


inline OVector2 Vec2_Normalize(const OVector2 &a)
{
	OVector2 result = a;
	result.Nomarlize();
	return result;
}

inline OVector2 Vec2_Abs(const OVector2 &a)
{
	OVector2 result = a;
	result.Abs();
	return result;
}

inline OVector2 Vec2_InvertSign(const OVector2 &a)
{
	OVector2 result = a;
	result.InvertSign();

	return result;
}

inline OVector2 Vec2_Saturate(const OVector2 &a)
{
	OVector2 result = a;
	result.Saturate();
	return result;
}
inline void Vec2_Swap(OVector2 &a, OVector2 &b)
{
	OVector2 temp = a;
	a = b;
	b = temp;
}

//判断两个向量是否相似
inline bool Vec2_NearlyEquals( const OVector2& a, const OVector2& b, float32 r ) 
{
	OVector2 diff = a - b;  // difference

	return(Vec2_Dotf(diff, diff) < r*r);  // radius
}





//////////////////////////////////////////////////////////////////////////
//Utility Function
//////////////////////////////////////////////////////////////////////////


#endif/* File Is Over */