//////////////////////////////////////////////////////////////////////////
//File : Only Vector3 ( Only Math Lib)
//Author : Zipxin  
//Project : OnlyGameEngine
//////////////////////////////////////////////////////////////////////////
#ifndef __OM_VECTOR3_H__
#define __OM_VECTOR3_H__

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
class OVector3;

//////////////////////////////////////////////////////////////////////////
//Global
//////////////////////////////////////////////////////////////////////////
extern OVector3 g_Vector3f_Zero;
extern OVector3 g_Vector3f_One;

//Define//////////////////////////////////////////////////////////////////
class OVector3
{
private :
	union 
	{
		struct 
		{
			float32 x, y, z;
		};
		float32 elem_f[3];
		int32   elem_i[3];
	};
public :
	inline OVector3(){};

	inline OVector3(float32 ix, float32 iy, float32 iz):x(ix),y(iy),z(iz){}

	inline OVector3(const OVector3 &a):x(a.x),y(a.y),z(a.z){}

	inline OVector3(float32 f):x(f),y(f),z(f){}


	inline OVector3(int32 x, int32 y, int32 z)
	{
		elem_i[0] = x;
		elem_i[1] = y;
		elem_i[2] = z;
	}

	inline OVector3( uint32 value )
	{
		elem_i[0] = value;
		elem_i[1] = value;
		elem_i[2] = value;
	}


	//////////////////////////////////////////////////////////////////////////
	inline void Set(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	inline void Set(float value)
	{
		this->x = value;
		this->y = value;
		this->z = value;
	}

	inline void Set(float *p)
	{
		this->x = p[0];
		this->y = p[1];
		this->z = p[2];
	}

	inline void SetX(float x)
	{
		this->x = x;
	}

	inline float32 GetXf() { return x; }

	inline float32 GetYf() { return y; }

	inline float32 GetZf() { return z; }


	inline OVector3 GetXXXf(void)
	{
		OVector3 result(x);
		return result;
	}


	inline OVector3 GetYYYf(void)
	{
		OVector3 result(y);
		return result;
	}


	inline OVector3 GetZZZf(void)
	{
		OVector3 result(z);
		return result;
	}


	inline void SetY(float y)
	{
		this->y = y;
	}

	inline void SetZ(float z)
	{
		this->z = z;
	}


	inline void SetXYZ(float *p)
	{
		x = p[0];
		y = p[1];
		z = p[2];
	}
	//////////////////////////////////////////////////////////////////////////
	//存放在数组p中，值为float类型
	inline void StoreToArrayf(float *p)
	{
		p[0] = x;
		p[1] = y;
		p[2] = z;
	}

	inline void StoreToArrayf(int *p)
	{
		p[0] = (int)x;
		p[1] = (int)y;
		p[2] = (int)z;
	}

	inline void StoreToArrayi(int *p)
	{
		p[0] = elem_i[0];
		p[1] = elem_i[1];
		p[2] = elem_i[2];
	}


	inline void StoreXYZToArrayf(float *p)
	{
		p[0] = x;
		p[1] = y;
		p[2] = z;
	}
	//////////////////////////////////////////////////////////////////////////

	inline OVector3& InvertSign()
	{
		x = -x;
		y = -y;
		z = -z;
		return *this;
	}

	inline float32 Length()
	{
		float32 res = 0.0f;
		float32 sum = x*x + y*y + z*z;// + w*w;
		res = OSqrt(sum);
		return res;
	}	

	inline float32 LengthNotSqrt()
	{
		return x*x + y*y + z*z;
	}	

	inline void Display()
	{
		printf("Vector 3: (%5.2f,%5.2f,%5.2f)\n", x, y, z);
	}

	//将元素绝对值化
	inline OVector3 &Abs()
	{
		x = OAbs(x);
		y = OAbs(y);
		z = OAbs(z);
		return *this;
	}

	inline float NormalizeAndGetLength(void)
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
		x *=len;
		y *=len;
		z *=len;
		return returnlen;
	}

	//对元素求倒数
	inline void Reciprocal(void)
	{
		x = 1.0f/x;
		y = 1.0f/y;
		z = 1.0f/z;
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
		x *=len;
		y *=len;
		z *=len;
	}

	//饱和处理
	inline OVector3 &Saturate(void)
	{
		if ( x > 1.0f ) x = 1.0f;
		if ( y > 1.0f ) y = 1.0f;
		if ( z > 1.0f ) z = 1.0f;

		if ( x < 0.0f ) x = 0.0f;
		if ( y < 0.0f ) y = 0.0f;
		if ( z < 0.0f ) z = 0.0f;

		return *this;
	}
	inline OVector3 &Clamp_to_0(void)
	{
		if ( x < 0.0f ) x = 0.0f;
		if ( y < 0.0f ) y = 0.0f;
		if ( z < 0.0f ) z = 0.0f;

		return *this;
	}

	inline OVector3 &Clamp_to_1(void)
	{
		if ( x > 1.0f ) x = 1.0f;
		if ( y > 1.0f ) y = 1.0f;
		if ( z > 1.0f ) z = 1.0f;

		return *this;
	}

	//////////////////////////////////////////////////////////////////////////
	/*Operator*/

public:

	inline static OVector3 &GetZero(void)
	{
		return g_Vector3f_Zero;
	}

	inline static OVector3 &GetOne(void)
	{
		return g_Vector3f_One;
	}

	inline OVector3 &Floor(void)
	{
		x = floor(x);
		y = floor(y);
		z = floor(z);
		return *this;
	}


public:

	inline OVector3& operator *= (float32 value)
	{
		x *= value;
		y *= value;
		z *= value;
		return *this;
	}
	inline OVector3 operator =(const OVector3 &value)
	{
		x = value.x;
		y = value.y;
		z = value.z;
		return *this;
	}


	inline OVector3 &operator+=(OVector3 &rhs)
	{
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
		return *this;
	}

	inline OVector3 &operator+=(float32 value)
	{
		x += value;
		y += value;
		z += value;
		return *this;
	}

	inline OVector3 &operator=(float32 value)
	{
		Set(value);
		return *this;
	}

	inline bool operator ==(const OVector3 &value) const 
	{
		return x==value.x && y == value.y && z == value.z ;
	}

	inline bool operator !=(const OVector3 &value) const 
	{
		return x!=value.x||y!=value.y||z!=value.z;
	}

	inline OVector3 operator -=(const OVector3 &value) const 
	{
		OVector3 result;
		result.x = x - value.x;
		result.y = y - value.y;
		result.z = z - value.z;

		return result;
	}



	inline OVector3 operator-() const
	{
		return OVector3(-x,-y,-z);
	}


	inline OVector3 &operator/=(float32 value)
	{
		x /= value;
		y /= value;
		z /= value;
		return *this;
	}


	inline float32 &operator[](int32 index)
	{
		assert(index < 3 && index >= 0 &&"下标越界");
		return elem_f[index];
	}

	inline const float32 &operator[](int32 index) const 
	{
		assert(index < 3 && index >= 0 &&"下标越界");
		return elem_f[index];
	}


	inline const tchar *GetVector4Info(void)
	{
		return _T("Vector3 : General , C++ , v 0.5.6");
	}

//////////////////////////////////////////////////////////////////////////
//Debug
	inline void Vec3_FPrint(FILE* file, const tchar* str) const 
	{
		_ftprintf(file, _T("%s Vector 3: <%f, %f, %f>\n"), str, x, y, z);
	}
};



extern OVector3 TempVector3List[256];
extern int TempVector3ListIndex ;

inline OVector3* GetNextTempVector3()
{
	TempVector3ListIndex = (TempVector3ListIndex++) & 255;
	return &TempVector3List[TempVector3ListIndex];
}


inline OVector3 operator+(const OVector3 &a, const OVector3 &b)
{
	OVector3 *c = GetNextTempVector3();

	c->x = a.x + b.x;
	c->y = a.y + b.y;
	c->z = a.z + b.z;

	return *c;
}

inline OVector3 operator-(const OVector3 &a, const OVector3 &b)
{
	OVector3 *c = GetNextTempVector3();

	c->x = a.x - b.x;
	c->y = a.y - b.y;
	c->z = a.z - b.z;

	return *c;
}

inline OVector3 operator*(const float32 f, const OVector3 &v)
{
	OVector3 *result = GetNextTempVector3();

	result->x = f * v.x;
	result->y = f * v.y;
	result->z = f * v.z;

	return *result;
}

inline OVector3 operator*(const OVector3 &v, const float32 f)
{
	OVector3 *result = GetNextTempVector3();

	result->x = f * v.x;
	result->y = f * v.y;
	result->z = f * v.z;

	return *result;
}
inline float Vec3_Dotf(const OVector3 &a, const OVector3 &b)
{
	float result = a.x * b.x + a.y * b.y + a.z * b.z;
	return result;
}


inline OVector3 Vect3_CrossProduct(const OVector3 &a, const OVector3 &b)
{
	OVector3 *c = GetNextTempVector3();

	c->x = a.y * b.z - a.z * b.y;
	c->y = a.z * b.x - a.x * b.z;
	c->z = a.x * b.y - a.y * b.x;

	return *c;
}

inline OVector3 Vec3_Lerp(const OVector3 &a, const OVector3 &b, const float32 t)
{
	OVector3 c = a + (b - a) * t;
	return c;
}

inline OVector3 Vec3_Max(const OVector3 &a, const OVector3 &b)
{
	OVector3 *c = GetNextTempVector3();

	c->x = a.x > b.x ? a.x : b.x;
	c->y = a.y > b.y ? a.y : b.y;
	c->z = a.z > b.z ? a.z : b.z;

	return *c;
}


inline OVector3 Vec3_Min(const OVector3 &a, const OVector3 &b)
{
	OVector3 *c = GetNextTempVector3();

	c->x = a.x < b.x ? a.x : b.x;
	c->y = a.y < b.y ? a.y : b.y;
	c->z = a.z < b.z ? a.z : b.z;

	return *c;
}


inline OVector3 Vec3_Normalize(const OVector3 &a)
{
	OVector3 result = a;
	result.Nomarlize();
	return result;
}

inline OVector3 Vec3_Abs(const OVector3 &a)
{
	OVector3 result = a;
	result.Abs();
	return result;
}

inline OVector3 Vec3_InvertSign(const OVector3 &a)
{
	OVector3 result = a;
	result.InvertSign();

	return result;
}

inline OVector3 Vec3_Saturate(const OVector3 &a)
{
	OVector3 result = a;
	result.Saturate();
	return result;
}

inline void Vec3_Swap(OVector3 &a, OVector3 &b)
{
	OVector3 temp = a;
	a = b;
	b = temp;
}

inline bool Vec3_NearlyEquals( const OVector3& a, const OVector3& b, float32 r ) 
{
	OVector3 diff = a - b;   

	return(Vec3_Dotf(diff, diff) < r*r);  // radius
}





//////////////////////////////////////////////////////////////////////////
//Utility Function
//////////////////////////////////////////////////////////////////////////


#endif/* File Is Over */