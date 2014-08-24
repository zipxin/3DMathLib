//////////////////////////////////////////////////////////////////////////
//File : Only Vector3 ( Only Math Lib )
//Author : Zipxin  [China]
//E-mail: zipxin@163.com
//Project : OnlyGameEngine
//////////////////////////////////////////////////////////////////////////
#ifndef _ONLY_VECTOR3_H_
#define _ONLY_VECTOR3_H_

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


class OMatrix3x3;
class OMatrix4x4;
class OVector4;

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

	explicit inline OVector3(float32 f):x(f),y(f),z(f){}

	inline OVector3(float32 *f):x(f[0]),y(f[1]),z(f[2]){}


	inline OVector3(int32 x, int32 y, int32 z)
	{
		elem_i[0] = x;
		elem_i[1] = y;
		elem_i[2] = z;
	}

	explicit inline OVector3( uint32 value )
	{
		elem_i[0] = value;
		elem_i[1] = value;
		elem_i[2] = value;
	}


//////////////////////////////////////////////////////////////////////////
	inline void Setf(float32 x, float32 y, float32 z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	inline void Setf(float32 value)
	{
		this->x = value;
		this->y = value;
		this->z = value;
	}


	inline void Setf(float *p)
	{
		this->x = p[0];
		this->y = p[1];
		this->z = p[2];
	}

	inline void SetXf(float x)
	{
		this->x = x;
	}

	inline void SetYf(float y)
	{
		this->y = y;
	}

	inline void SetZf(float z)
	{
		this->z = z;
	}

	inline float32 GetXf() const { return x; }

	inline float32 GetYf() const { return y; }

	inline float32 GetZf() const { return z; }


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


//////////////////////////////////////////////////////////////////////////
	//���������p�У�ֵΪfloat����
	inline void StoreToArrayf(float *p) const 
	{
		p[0] = x;
		p[1] = y;
		p[2] = z;
	}

	inline void StoreToArrayf(int *p) const 
	{
		p[0] = (int)x;
		p[1] = (int)y;
		p[2] = (int)z;
	}

	inline void StoreToArrayi(int *p) const 
	{
		p[0] = elem_i[0];
		p[1] = elem_i[1];
		p[2] = elem_i[2];
	}


//////////////////////////////////////////////////////////////////////////
	inline bool Equals(const OVector3& rhs) const 
	{
		return OEquals(x, rhs.x) && OEquals(y, rhs.y) && OEquals(z, rhs.z); 
	}


	inline OVector3& InvertSign()
	{
		x = -x;
		y = -y;
		z = -z;
		return *this;
	}

	inline float32 Length() const
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

	inline void Clear()
	{
		this->x = 0.0f;
		this->y = 0.0f;
		this->z = 0.0f;
	}

	inline bool  IsZero()
	{
		return *this == OVector3::ZERO;
	}

	/** (x + y + z)/3 */
	inline float32  Average() const						
	{
		return (x + y + z) * 0.333333f;
	}


	/** �����������е����� */
	inline OVector3 HalfWay(const OVector3& dest) const	
	{
		return OVector3(0.5f * (x + dest.x),
			            0.5f * (y + dest.y),
						0.5f * (z + dest.z));
	}


	inline float32 MaxValuef()
	{
		return OMax3<float32>(x,y,z);
	}

	inline float32 MinValuef()
	{
		return OMin3<float32>(x,y,z);
	}

	inline void Display()
	{
		printf("Vector 3: (%5.2f,%5.2f,%5.2f)\n", x, y, z);
	}

	inline const char* ToCString()
	{
		char *buf = new char[128];
		memset(buf, 0 , 128);
		sprintf_s(buf, 128, "Vector 3: (%5.2f,%5.2f,%5.2f)\n", x, y, z);
		return buf;
	}

	inline const wchar_t* ToWString()
	{
		wchar_t *buf = new wchar_t[128];
		memset(buf, 0 , 128);
		swprintf_s(buf, 128, L"Vector 3: (%5.2f,%5.2f,%5.2f)\n", x, y, z);
		return buf;
	}



	//��Ԫ�ؾ���ֵ��
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
		if( OEquals(len, 1.0) || OEquals(len, 0.0f) || len < 0.0f )
		{
			return len;
		}

		float32 returnlen = len;
		len = 1.0f / len;
		x *=len;
		y *=len;
		z *=len;
		return returnlen;
	}

	//��Ԫ������
	inline void Reciprocal(void)
	{
		if(x != 0.0f)
			x = 1.0f/x;
		if(y != 0.0f)
			y = 1.0f/y;
		if(z != 0.0f)
			z = 1.0f/z;
	}


	inline void Nomarlize()
	{
		float32 len = Length();
		if( OEquals(len, 1.0) || OEquals(len, 0.0f) || len < 0.0f )
		{
			return;
		}
		len = 1.0f / len;
		x *=len;
		y *=len;
		z *=len;
	}
//! Ҫ��Ҫ�ı�thisֵ �ڷ���*this��?
	inline const OVector3 Nomarlized() const
	{
		float32 len = Length();
		if( OEquals(len, 1.0) || OEquals(len, 0.0f) || len < 0.0f )
		{
			return OVector3::ZERO;
		}
		len = 1.0f / len;

		return OVector3(x*len, y*len, z*len);
	}

	//���ʹ���
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

	/** 3ά�������	*/
	inline float32 Dot(const OVector3& v) const
	{
		return v.x*x + v.y*y + v.z*z; 
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
	/// (0,0,0) vector.
	static const OVector3 ZERO;
	/// (-1,0,0) vector.
	static const OVector3 LEFT;
	/// (1,0,0) vector.
	static const OVector3 RIGHT;
	/// (0,1,0) vector.
	static const OVector3 UP;
	/// (0,-1,0) vector.
	static const OVector3 DOWN;
	/// (0,0,1) vector.
	static const OVector3 FORWARD;
	/// (0,0,-1) vector.
	static const OVector3 BACK;
	/// (1,1,1) vector.
	static const OVector3 ONE;

	static const OVector3 X_AXIS;
	static const OVector3 Y_AXIS;
	static const OVector3 Z_AXIS;
	static const OVector3 NEG_X_AXIS;
	static const OVector3 NEG_Y_AXIS;
	static const OVector3 NEG_Z_AXIS;

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

	/** �õ�ԭ�����ڲ���������ͶӰ�ĳ��� */ 
	inline float32  ScalarProjectionOntoVector(OVector3& v1)	{return Dot(v1)/v1.Length();}

// 	/** �õ�ԭ�����ڲ��������ϵ�ͶӰ���� */ 
// 	 	inline OVector3 ProjectionOntoVector(const OVector3& v1)	
// 		{
// 			return v1*(Dot(v1)/v1.DotSelf());
// 		}

	/** ����ԭ�����Ͳ���������ƫ��Ļ��� */ 
	inline float  RadAngle(const OVector3& v1) const		{return acosf(Dot(v1)/(Length()*v1.Length()));}
	/** ����ԭ�����Ͳ���������ƫ��Ļ��ȵ�cosֵ */ 
	inline float  CosAngle(const OVector3& v1) const {return Dot(v1)/(Length()*v1.Length());}

	/** ����ԭ������������������֮������(P0-P1)�ľ��� */
	//inline float  DistanceToLine(const OVector3& p0, const OVector3& p1) const;

	
	/** �жϸ������Ƿ��Ǹ��ǳ�С���������ӽ���0 /n
	 *	@note: �жϷ����������ĸ��������ǳ�С
	 */
	inline int IsNearlyZero() const
	{
		return
			(	fabsf(x)< EPSILON8 
			&&	fabsf(y)< EPSILON8
			&&	fabsf(z)< EPSILON8);
	}
public:

	inline OVector3& operator *= (float32 value)
	{
		x *= value;
		y *= value;
		z *= value;
		return *this;
	}

	
	inline OVector3& operator *= (OVector3 value)
	{
		x *= value.x;
		y *= value.y;
		z *= value.z;
		return *this;
	}

	//�������wֵΪ1.0f
	OVector3 OVector3::operator * ( const OMatrix4x4 &m ) const;

	inline OVector3 &operator =(const OVector3 &value)
	{
		x = value.x;
		y = value.y;
		z = value.z;
		return *this;
	}


	inline OVector3 &operator+=(const OVector3 &rhs)
	{
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
		return *this;
	}

	inline OVector3 &operator+=(const float32 value)
	{
		x += value;
		y += value;
		z += value;
		return *this;
	}

	inline OVector3 &operator-=(float32 value)
	{
		x -= value;
		y -= value;
		z -= value;
		return *this;
	}

	inline OVector3 &operator=(float32 value)
	{
		Setf(value);
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

	inline OVector3 &operator -=(const OVector3 &value)
	{
		x -= value.x;
		y -= value.y;
		z -= value.z;

		return *this;
	}



	inline OVector3 operator-() const
	{
		return OVector3(-x,-y,-z);
	}


	inline OVector3 &operator/=(float32 value)
	{
		assert(value != 0.0f);
		float32 temp = 1.0f / value;
		x *= temp;
		y *= temp;
		z *= temp;
		return *this;
	}

	inline OVector3 &operator/(float32 value)
	{
		assert(value != 0.0f);
		float32 temp = 1.0f / value;
		x *= temp;
		y *= temp;
		z *= temp;
		return *this;
	}

	inline OVector3& operator /= (const OVector3& rhs)
	{
		assert(rhs.x != 0.0f);
		assert(rhs.y != 0.0f);
		assert(rhs.z != 0.0f);
		x /= rhs.x;
		y /= rhs.y;
		z /= rhs.z;
		return *this;
	}


	inline float32 &operator[](int32 index)
	{
		assert(index < 3 && index >= 0 &&"�±�Խ��");
		return elem_f[index];
	}

	inline const float32 &operator[](int32 index) const 
	{
		assert(index < 3 && index >= 0 &&"�±�Խ��");
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

	/** ���������<<,ʹ֮��װ��ʽVector3(vx,y,z)��� */
	inline friend std::ostream& operator <<
		( std::ostream& o, const OVector3& v )
	{
		o << "Vector3(" << v.x << ", " << v.y << ", " << v.z << ")";
		return o;
	}

};



extern OVector3 TempVector3List[256];
extern int32    TempVector3ListIndex ;

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

inline OVector3 operator*(const OVector3 &lhs, const OVector3 &rhs)
{
	OVector3 *result = GetNextTempVector3();

	result->x = lhs.x * rhs.x;
	result->y = lhs.y * rhs.y;
	result->z = lhs.z * rhs.z;

	return *result;
}


inline float32 Vec3_Dotf(const OVector3 &a, const OVector3 &b)
{
	float32 result = a.x * b.x + a.y * b.y + a.z * b.z;
	return result;
}

inline float32 Vec3_DotAbsf(const OVector3 &a, const OVector3 &b)
{
	float32 result = OAbs(a.x * b.x) + OAbs(a.y * b.y) + OAbs(a.z * b.z);
	return result;
}


inline OVector3 Vec3_CrossProduct(const OVector3 &a, const OVector3 &b)
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


/** 3ά������һ��4��4�任������ˣ��˺����� \n
 *	@param [const Matrix4&]: 4��4�任����ĳ�������
 *	@return [Vector3]: result = this �� Matrix4
 *	@note: �����Ƚ�ԭVector3�任ΪVector4(w = 1),
 *   �任��Vector3�ĸ�����������w'
 */    
//OVector3 operator*(const OVector3 &v, const OMatrix4x4 &m ) const;

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
/** ��z_axis���ղ����еĽǶ���ת�����ҵ�λ����� */
OVector3 MakeDirection(float yaw, float pitch, float roll);
/** ��v0,v1,v2��������ɵ�ƽ��ķ����� */
OVector3 NormalFromTriangle(const OVector3& v0, const OVector3& v1, const OVector3& v2);


#endif/* File Is Over */