//////////////////////////////////////////////////////////////////////////
//File : Only Vector4 ( Only Math Lib)
//Author : Zipxin  
//Project : OnlyGameEngine
//////////////////////////////////////////////////////////////////////////
#ifndef __OM_VECTOR4_H__
#define __OM_VECTOR4_H__

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
class OVector4;


//////////////////////////////////////////////////////////////////////////
//Global
//////////////////////////////////////////////////////////////////////////
extern OVector4 g_Vector4f_Zero;
extern OVector4 g_Vector4f_One;

//Define//////////////////////////////////////////////////////////////////
class OVector4
{
private :
	union
	{
		struct 
		{
			float32 x, y, z, w;
		};
		float32 elem_f[4];
		int32 elem_i[4];
	};
public :
	inline OVector4(){};

	inline OVector4(float32 ix, float32 iy, float32 iz, float32 iw = 0.0f):x(ix),y(iy),z(iz),w(iw){}

	inline OVector4(const OVector4 &a):x(a.x),y(a.y),z(a.z),w(a.w){}

	inline OVector4(float32 f):x(f),y(f),z(f),w(f){}

	inline OVector4(int32 x, int32 y, int32 z, int32 w)
	{
		elem_i[0] = x;
		elem_i[1] = y;
		elem_i[2] = z;
		elem_i[3] = w;
	}

	inline OVector4( uint32 value )
	{
		elem_i[0] = value;
		elem_i[1] = value;
		elem_i[2] = value;
		elem_i[3] = value;
	}


//////////////////////////////////////////////////////////////////////////
	inline void Set(float x, float y, float z, float w=0.0f)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	inline void Set(float value)
	{
		this->x = value;
		this->y = value;
		this->z = value;
		this->w = value;
	}

	inline void Set(float *p)
	{
		this->x = p[0];
		this->y = p[1];
		this->z = p[2];
		this->w = p[3];
	}

	inline void SetX(float x)
	{
		this->x = x;
	}

	inline float32 GetXf() { return x; }

	inline float32 GetYf() { return y; }

	inline float32 GetZf() { return z; }

	inline float32 GetWf() { return w; }


	inline OVector4 GetXXXXf(void)
	{
		OVector4 result(x);
		return result;
	}


	inline OVector4 GetYYYYf(void)
	{
		OVector4 result(y);
		return result;
	}


	inline OVector4 GetZZZZf(void)
	{
		OVector4 result(z);
		return result;
	}


	inline OVector4 GetWWWWf(void)
	{
		OVector4 result(w);
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

	inline void SetW(float w)
	{
		this->w = w;
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
		p[3] = w;
	}

	inline void StoreToArrayf(int *p)
	{
		p[0] = (int)x;
		p[1] = (int)y;
		p[2] = (int)z;
		p[3] = (int)w;
	}

	inline void StoreToArrayi(int *p)
	{
		p[0] = elem_i[0];
		p[1] = elem_i[1];
		p[2] = elem_i[2];
		p[3] = elem_i[3];
	}


	inline void StoreXYZToArrayf(float *p)
	{
		p[0] = x;
		p[1] = y;
		p[2] = z;
	}

	inline void StoreXYToArrayf(float *p)
	{
		p[0] = x;
		p[1] = y;
	}
//////////////////////////////////////////////////////////////////////////

	inline OVector4& InvertSign()
	{
		x = -x;
		y = -y;
		z = -z;
		w = -w;
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
		return  x*x + y*y + z*z;
	}	

	inline void Display()
	{
		printf("Vector 4: (%5.2f,%5.2f,%5.2f,%5.2f)\n", x, y, z, w);
	}

	//将元素绝对值化
	inline OVector4 &Abs()
	{
		x = OAbs(x);
		y = OAbs(y);
		z = OAbs(z);
		w = OAbs(w);
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
		w = 1.0f/w;
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
	inline OVector4 &Saturate(void)
	{
		if ( x > 1.0f ) x = 1.0f;
		if ( y > 1.0f ) y = 1.0f;
		if ( z > 1.0f ) z = 1.0f;
		if ( w > 1.0f ) w = 1.0f;

		if ( x < 0.0f ) x = 0.0f;
		if ( y < 0.0f ) y = 0.0f;
		if ( z < 0.0f ) z = 0.0f;
		if ( w < 0.0f ) w = 0.0f;

		return *this;
	}
	inline OVector4 &Clamp_to_0(void)
	{
		if ( x < 0.0f ) x = 0.0f;
		if ( y < 0.0f ) y = 0.0f;
		if ( z < 0.0f ) z = 0.0f;
		if ( w < 0.0f ) w = 0.0f;

		return *this;
	}

	inline OVector4 &Clamp_to_1(void)
	{
		if ( x > 1.0f ) x = 1.0f;
		if ( y > 1.0f ) y = 1.0f;
		if ( z > 1.0f ) z = 1.0f;
		if ( w > 1.0f ) w = 1.0f;

		return *this;
	}

//////////////////////////////////////////////////////////////////////////
/*Operator*/

public:

	inline static OVector4 &GetZero(void)
	{
		return g_Vector4f_Zero;
	}

	inline static OVector4 &GetOne(void)
	{
		return g_Vector4f_One;
	}

	inline OVector4 &Floor(void)
	{
		x = floor(x);
		y = floor(y);
		z = floor(z);
		w = floor(w);
		return *this;
	}


public:

	inline OVector4& operator *= (float32 value)
	{
		x *= value;
		y *= value;
		z *= value;
		w *= value;
		return *this;
	}
	inline OVector4 operator =(const OVector4 &value)
	{
		x = value.x;
		y = value.y;
		z = value.z;
		w = value.w;
		return *this;
	}

	
	inline OVector4 &operator+=(OVector4 &rhs)
	{
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
		w += rhs.w;
		return *this;
	}

	inline OVector4 &operator+=(float32 value)
	{
		x += value;
		y += value;
		z += value;
		w += value;
		return *this;
	}

	inline OVector4 &operator=(float32 value)
	{
		Set(value);
		return *this;
	}

	inline bool operator ==(const OVector4 &value) const 
	{
		return x==value.x && y == value.y && z == value.z && w == value.w;
	}

	inline bool operator !=(const OVector4 &value) const 
	{
		return x!=value.x||y!=value.y||z!=value.z||w!=value.w;
	}

	inline OVector4 operator -=(const OVector4 &value) const 
	{
		OVector4 result;
		result.x = x - value.x;
		result.y = y - value.y;
		result.z = z - value.z;
		result.w = w - value.w;

		return result;
	}


	inline OVector4 operator-() const
	{
		return OVector4(-x,-y,-z,-w);
	}


	inline OVector4 &operator/=(float32 value)
	{
		x /= value;
		y /= value;
		z /= value;
		w /= value;
		return *this;
	}


	inline float32 &operator[](int32 index)
	{
		assert(index < 4 && index >= 0 &&"下标越界");
		return elem_f[index];
	}

	inline const float32 &operator[](int32 index) const
	{
		assert(index < 4 && index >= 0 &&"下标越界");
		return elem_f[index];
	}

	inline const tchar *GetVector4Info(void)
	{
		return _T("Vector4 : General , C++ , v 0.5.6");
	}

//////////////////////////////////////////////////////////////////////////
//Debug
	inline void Vec4_FPrint(FILE* file, const tchar* str) const 
	{
		_ftprintf(file, _T("%s Vector 4: <%f, %f, %f, %f>\n"), str, x, y, z, w);
	}
};



extern OVector4 TempVector4List[256];
extern int TempVector4ListIndex ;

inline OVector4* GetNextTempVector4()
{
	TempVector4ListIndex = (TempVector4ListIndex++) & 255;
	return &TempVector4List[TempVector4ListIndex];
}


inline OVector4 operator+(const OVector4 &a, const OVector4 &b)
{
	OVector4 *c = GetNextTempVector4();

	c->x = a.x + b.x;
	c->y = a.y + b.y;
	c->z = a.z + b.z;
	c->w = a.w + b.w;

	return *c;
}

inline OVector4 operator-(const OVector4 &a, const OVector4 &b)
{
	OVector4 *c = GetNextTempVector4();

	c->x = a.x - b.x;
	c->y = a.y - b.y;
	c->z = a.z - b.z;
	c->w = a.w - b.w;

	return *c;
}

inline OVector4 operator*(const float32 f, const OVector4 &v)
{
	OVector4 *result = GetNextTempVector4();

	result->x = f * v.x;
	result->y = f * v.y;
	result->z = f * v.z;
	result->w = f * v.w;

	return *result;
}

inline OVector4 operator*(const OVector4 &v, const float32 f)
{
	OVector4 *result = GetNextTempVector4();

	result->x = f * v.x;
	result->y = f * v.y;
	result->z = f * v.z;
	result->w = f * v.w;

	return *result;
}

inline float Vec4_Dotf(const OVector4 &a, const OVector4 &b)
{
	float result = a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
	return result;
}


inline OVector4 Vec4_CrossProduct(const OVector4 &a, const OVector4 &b)
{
	OVector4 *c = GetNextTempVector4();

	c->x = a.y * b.z - a.z * b.y;
	c->y = a.z * b.x - a.x * b.z;
	c->z = a.x * b.y - a.y * b.x;
	c->w = 0.0f;

	return *c;
}


inline OVector4 Vec4_Lerp(const OVector4 &a, const OVector4 &b, const float32 t)
{
	OVector4 c = a + (b - a) * t;
	return c;
}

inline OVector4 Vec4_Max(const OVector4 &a, const OVector4 &b)
{
	OVector4 *c = GetNextTempVector4();

	c->x = a.x > b.x ? a.x : b.x;
	c->y = a.y > b.y ? a.y : b.y;
	c->z = a.z > b.z ? a.z : b.z;
	c->w = a.w > b.w ? a.w : b.w;

	return *c;
}


inline OVector4 Vec4_Min(const OVector4 &a, const OVector4 &b)
{
	OVector4 *c = GetNextTempVector4();

	c->x = a.x < b.x ? a.x : b.x;
	c->y = a.y < b.y ? a.y : b.y;
	c->z = a.z < b.z ? a.z : b.z;
	c->w = a.w < b.w ? a.w : b.w;

	return *c;
}


inline OVector4 Vec4_Normalize(const OVector4 &a)
{
	OVector4 result = a;
	result.Nomarlize();
	return result;
}

inline OVector4 Vec4_Abs(const OVector4 &a)
{
	OVector4 result = a;
	result.Abs();
	return result;
}

inline OVector4 Vec4_InvertSign(const OVector4 &a)
{
	OVector4 result = a;
	result.InvertSign();

	return result;
}

inline OVector4 Vec4_Saturate(const OVector4 &a)
{
	OVector4 result = a;
	result.Saturate();
	return result;
}

inline void Vec4_Swap(OVector4 &a, OVector4 &b)
{
	OVector4 temp = a;
	a = b;
	b = temp;
}


inline bool Vec4_NearlyEquals( const OVector4& a, const OVector4& b, float32 r ) 
{
	OVector4 diff = a - b;   

	return(Vec4_Dotf(diff, diff) < r*r);  // radius
}




//////////////////////////////////////////////////////////////////////////
//Utility Function
//////////////////////////////////////////////////////////////////////////
//plane 为平面法向量，单位为1
//保证结果为正
inline float32 PointToPlaneDistance(OVector4 &point, OVector4 &plane)
{
	return Vec4_Dotf(point, plane);
}


//plane 为平面法向量，单位为1
inline OVector4 MirrorPoint(OVector4 &point, OVector4 &plane)
{
	OVector4 mirrored_point;

	float32 d = PointToPlaneDistance(point, plane);
	mirrored_point = point - (2.0f * d ) * plane;

	return mirrored_point;
}


// 计算vector相对于plane平面对称方向
inline OVector4 MirrorVector(OVector4 &vector, OVector4 &plane)
{
	OVector4 mirrored_a, mirrored_b, mirrored_vector;
	OVector4 vZero = OVector4::GetZero();

	float32 d = PointToPlaneDistance(vector, plane);
	mirrored_a = vector - (2.0f * d ) * plane;

	d = plane[3];
	mirrored_b = vZero - (2.0f * d ) * plane;

	mirrored_vector = mirrored_a - mirrored_b;
	mirrored_vector[3] = 1.0f;

	return mirrored_vector;
}



#endif/* File Is Over */