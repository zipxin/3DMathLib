//////////////////////////////////////////////////////////////////////////
//File : Only Vector2 ( Only Math Lib )
//Author : Zipxin  [China]
//E-mail: zipxin@163.com
//Project : OnlyGameEngine
//////////////////////////////////////////////////////////////////////////
#ifndef _ONLY_VECTOR2_H_
#define _ONLY_VECTOR2_H_

#if _MSC_VER > 1000
#pragma once
#endif 

#include "../OInclude/Common/OnlyGameDefine.h"

#include "OMathUtil.h"
#include <stdio.h>

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

	explicit inline OVector2(float32 f):x(f),y(f){}

	inline OVector2(float32 *f):x(f[0]),y(f[1]){}


	inline OVector2(int32 x, int32 y)
	{
		elem_i[0] = x;
		elem_i[1] = y;
	}

	explicit inline OVector2( uint32 value )
	{
		elem_i[0] = value;
		elem_i[1] = value;
	}

	//////////////////////////////////////////////////////////////////////////
	inline void Setf(float x, float y)
	{
		this->x = x;
		this->y = y;
	}

	inline void Setf(float value)
	{
		this->x = value;
		this->y = value;
	}

	inline void Setf(float *p)
	{
		this->x = p[0];
		this->y = p[1];
	}

	inline void SetXf(float x)
	{
		this->x = x;
	}
	inline void SetYf(float y)
	{
		this->y = y;
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
//////////////////////////////////////////////////////////////////////////
	//存放在数组p中，值为float类型
	inline void StoreToArrayf(float *p) const 
	{
		p[0] = x;
		p[1] = y;
	}

	inline void StoreToArrayf(int *p) const 
	{
		p[0] = (int)x;
		p[1] = (int)y;
	}

	inline void StoreToArrayi(int *p) const 
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

	inline float32 Length() const
	{
		float32 res = 0.0f;
		float32 sum = x*x + y*y;
		res = OSqrt(sum);
		return res;
	}	

	//清0操作
	inline void Clear()
	{
		this->x = 0.0f;
		this->y = 0.0f;
	}

	inline float32 LengthNotSqrt()
	{
		return x*x + y*y;
	}	

	/** 向量点乘 */
	inline float32  Dot(const OVector2& v) const 
	{
		return x*v.x + y*v.y;
	}

	/** 计算x轴分量与y轴分量的平均值 */
	inline float32 Average() const	
	{
		return (x + y) * 0.5f;
	}

	/** 求原向量的正交向量 内积为0 相当于垂直向量*/
	inline OVector2 Perpendicular(void) const 
	{ 
		return OVector2 (-y, x);
	}

//Debug
	inline void Display()
	{
		printf("Vector 2: ( %5.2f,%5.2f )\n", x, y);
	}

	inline const char* ToCString()
	{
		char *buf = new char[128];
		memset(buf, 0 , 128);
		sprintf_s(buf, 128, "Vector 2: ( %5.2f,%5.2f )\n", x, y);
		return buf;
	}

	inline const wchar_t* ToWString()
	{
		wchar_t *buf = new wchar_t[128];
		memset(buf, 0 , 128);
		swprintf_s(buf, 128, L"Vector 2: ( %5.2f,%5.2f )\n", x, y);
		return buf;
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
		if( OEquals(len, 1.0) || OEquals(len, 0.0f) || len < 0.0f )
		{
			return returnlen;
		}

		len = 1.0f / len;
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
		if( OEquals(len, 1.0) || OEquals(len, 0.0f) || len < 0.0f )
		{
			return ;
		}

		len = 1.0f / len;
		x *= len;
		y *= len;
	}

	//const OVector2& Nomarlized() const
	const OVector2 Nomarlized() const
	{
		float32 len = Length();
		if( OEquals(len, 1.0) || OEquals(len, 0.0f) || len < 0.0f )
		{
			return OVector2::ZERO;
		}

		len = 1.0f / len;
		//x *= len;
		//y *= len;

		return OVector2(x*len, y*len);
	}

	inline bool  IsZero()
	{
		return *this == OVector2::ZERO;
	}

	inline float32 MaxValuef()
	{
		return x > y ? x : y;
	}

	inline float32 MinValuef()
	{
		return x < y ? x : y;
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

	inline bool Equals(const OVector2 &rhl) const
	{
		return OEquals(x, rhl.x) && OEquals(y, rhl.y);
	}

	/** 重载<<运算符，可以将二维向量按照Vector2(x,y)的格式输出 */
	inline friend std::ostream& operator <<	( std::ostream& o, const OVector2& v )
	{
		o << "Vector2(" << v.x << ", " << v.y <<  ")";
		return o;
	}


	
	/** 得到原向量旋转一定角度后的新向量 \n
	 *	@param [float] radian: 旋转的角度，单位是弧度
	 */
	inline OVector2 GetRotatedInRadian(float radian)
	{
		float cosD = cosf(radian);
		float sinD = sinf(radian);

		OVector2 result;
		result.x = x*cosD + y*sinD;
		result.y = y*cosD + x*sinD;

		return result;
	}

	/** 得到原向量旋转一定角度后的新向量 \n
	*	@param [float] degree: 旋转的角度，单位是角度
	*/
	inline OVector2 GetRotatedInDegree(float32 degree)
	{
		float32 radian = DEG_TO_RAD * degree;
		return GetRotatedInRadian(radian);
	}

	/** 得到两个向量之间的夹角，从src到dest \n
	*	@param [Vector2] src: 原方向
	*	@param [Vector2] dest: 目标方向
	*	@param [float] : 旋转角度，(-PI,PI],左手法则
	*/
	static float GetRadianBetween2Vector2(OVector2 src, OVector2 dest);


	/** 判断原向量是否长度为0 */
	inline bool IsZeroLength(void) const
	{
		if (Length() < EPSILON8)
			return true;
		else return false;
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

	static const OVector2 ZERO;
	/// (-1,0) vector.
	static const OVector2 LEFT;
	/// (1,0) vector.
	static const OVector2 RIGHT;
	/// (0,1) vector.
	static const OVector2 UP;
	/// (0,-1) vector.
	static const OVector2 DOWN;
	/// (1,1) vector.
	static const OVector2 ONE;

	static const OVector2 X_AXIS;		/// (1,0)
	static const OVector2 Y_AXIS;		/// (0,1)
	static const OVector2 NEG_X_AXIS;	/// (-1,0)
	static const OVector2 NEG_Y_AXIS;	/// (0,-1)
public:
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

	inline OVector2& operator *= (float32 value)
	{
		x *= value;
		y *= value;
		return *this;
	}

	inline OVector2& operator *=(const OVector2 &value)
	{
		x *= value.x;
		y *= value.y;
		return *this;
	}

	inline OVector2& operator -=(const OVector2 &value)
	{
		x -= value.x;
		y -= value.y;
		return *this;
	}



	inline OVector2 operator =(const OVector2 &value)
	{
		x = value.x;
		y = value.y;
		return *this;
	}

	inline OVector2 &operator/=(const OVector2 &value)
	{
		assert(value.x != 0.0f);
		assert(value.y != 0.0f);
		x /= value.x;
		y /= value.y;
		return *this;
	}

	inline OVector2 &operator/=(float32 value)
	{
		assert(value != 0.0f);
		float32 temp = 1.0f / value;
		x *= temp;
		y *= temp;
		return *this;
	}
	


	inline OVector2 &operator=(float32 value)
	{
		Setf(value);
		return *this;
	}

	inline bool operator ==(const OVector2 &value) const 
	{
		return OEquals( x, value.x) && OEquals( y, value.y);
	}

	inline bool operator !=(const OVector2 &value) const 
	{
		return x!=value.x||y!=value.y;
	}



	inline OVector2 operator-() const
	{
		return OVector2(-x,-y);
	}


	/** 初始化，传入两个数分别赋给x，y */
	inline void operator() (float32 nx, float32 ny)	
	{x = nx; y = ny;}	


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

inline float Vec2_DotAbsf(const OVector2 &a, const OVector2 &b)
{
	float result = OAbs(a.x * b.x) + OAbs(a.y * b.y);
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