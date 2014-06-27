//////////////////////////////////////////////////////////////////////////
//File : Only Matrix3x3 ( Only Math Lib)
//Author : Zipxin  
//Project : OnlyGameEngine
//////////////////////////////////////////////////////////////////////////
#ifndef __OM_MATRIX3X3_H__
#define __OM_MATRIX3X3_H__

#include "OnlyGameDefine.h"

#include "OVector3.h"


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
class OMatrix3x3;

//Global//////////////////////////////////////////////////////////////////
extern OMatrix3x3 g_Matrix3x3_Identity;
extern OMatrix3x3 g_Matrix3x3_Zero;

//Define
class OMatrix3x3
{
private:

	union 
	{
		float32 ele_f[3][43];
		int32 ele_i[3][3];
		struct 
		{
			float32 m11, m12, m13;
			float32 m21, m22, m23;
			float32 m31, m32, m33;
		};
		struct
		{
			OVector3 vec1;
			OVector3 vec2;
			OVector3 vec3;
		};
	};

public:
	inline OMatrix3x3(){}
	inline OMatrix3x3(
		float32 f00, float32 f01, float32 f02,
		float32 f10, float32 f11, float32 f12,
		float32 f20, float32 f21, float32 f22
		)
	{
		m11 = f00; m12 = f01; m13 = f02; 
		m21 = f10; m22 = f11; m23 = f12; 
		m31 = f20; m32 = f21; m33 = f22; 
	}

	inline OMatrix3x3
		(OVector3 &v1, OVector3 &v2, OVector3 &v3)
		:vec1(v1),vec2(v2),vec3(v3){}
	
	inline OMatrix3x3(const OMatrix3x3 &copy)
	{
		vec1 = copy.vec1;
		vec2 = copy.vec2;
		vec3 = copy.vec3;
	}

	

	~OMatrix3x3(){};

//////////////////////////////////////////////////////////////////////////
	inline void SetZero()
	{
		m11 = m12 = m13 = 0.0f;
		m21 = m22 = m23 = 0.0f;
		m31 = m32 = m33 = 0.0f;
	}


	inline void SetRow(int row, OVector3 &vec)
	{
		assert( row>=0 && row<3 );
		OVector3 *rows = &vec1;
		rows[row] = vec;
	}

	inline void SetColumn(int column, OVector3 &vec)
	{
		assert( column>=0 && column<3 );
		float *p = &m11 + column;
		p[0] =  vec.GetXf(); 
		p[3] =  vec.GetYf(); 
		p[6] =  vec.GetZf(); 
	}

	inline OVector3 &GetRow(const int32 row)
	{
		assert( row>=0 && row<3 );
		OVector3 *rows = &vec1;
		return rows[row];
	}

	inline const OVector3 &GetRow(const int32 row) const
	{
		assert( row>=0 && row<3 );
		const OVector3 *rows = &vec1;
		return rows[row];
	}

	inline OVector3 GetColumn(const int32 column)
	{
		assert(column>=0 && column<3);
		OVector3 vec;
		float *p = &m11 + column;

		vec.SetX(p[0]);
		vec.SetY(p[3]);
		vec.SetZ(p[6]);
		return vec;
	}

//////////////////////////////////////////////////////////////////////////

	inline OMatrix3x3 &Transpose(void)
	{
		OSwap<float32>(m12,m21);
		OSwap<float32>(m13,m31);
		OSwap<float32>(m23,m32);
		return *this;
	}

	inline void Identity(void)
	{
		*this = g_Matrix3x3_Identity;
	}
/*
	inline OVector4 Transform_Vec4(OVector4 &vec)
	{
		OVector4 result = vec * (*this);
		return result;
	}
*/
//Scale
	void Scale(OVector3 &scale)
	{
		Scale(scale[0], scale[1], scale[2]);
	}

	void Scale(float32 x, float32 y, float32 z)
	{
		vec1 *= x;
		vec2 *= y;
		vec3 *= z;
	}

	void Scale_Replace(OVector3 &scale)
	{
		Scale_Replace(scale[0], scale[1], scale[2]);
	}

	void Scale_Replace(float32 x, float32 y, float32 z)
	{
		vec1.Set(x, 0, 0);
		vec2.Set(0, y, 0);
		vec3.Set(0, 0, z);
	}

//translate
	/*
	void Translate(float x, float y, float z)
	{
		vec4 += vec1 * x + vec2 * y + vec3 * z;
	}

	void Translate(OVector4 &v)
	{
		vec4 += vec1 * v.GetXf() + vec2 * v.GetYf() + vec3 * v.GetZf();
	}

	void Translate_Replace(float x, float y, float z)
	{
		Identity();
		
	}

	void Translate_Replace(OVector3 &v)
	{
		Identity();
	}*/

//////////////////////////////////////////////////////////////////////////
//static
	static OMatrix3x3 &GetIdentityMatrix3x3(void)
	{
		return g_Matrix3x3_Identity;
	}

//////////////////////////////////////////////////////////////////////////
//Operator

	inline OMatrix3x3 &operator-=(const OMatrix3x3 &rhs)
	{
		vec1 -= rhs.vec1;
		vec2 -= rhs.vec2;
		vec3 -= rhs.vec3;
		return *this;
	}

	inline OMatrix3x3 &operator*=(const float32 f)
	{
		vec1 *= f;
		vec2 *= f;
		vec3 *= f;
		return *this;
	}

	inline OVector3 &operator[](const int32 row)
	{
		return GetRow(row);
	}

	inline const OVector3 &operator[](int32 row) const
	{
		return GetRow(row);
	}

	inline OMatrix3x3 &operator+=(OMatrix3x3 &rhs)
	{
		vec1 += rhs.vec1;
		vec2 += rhs.vec2;
		vec3 += rhs.vec3;

		return *this;
	}

	inline float32 &operator()(int x, int y)
	{
		assert(x>=0 && x<4);
		assert(y>=0 && y<4);
		return GetRow(x)[y];
	}

	inline OMatrix3x3 &operator=(OMatrix3x3 &rhs)
	{
		vec1 = rhs.vec1;
		vec2 = rhs.vec2;
		vec3 = rhs.vec3;

		return *this;
	}

	inline OMatrix3x3 &operator-=(float32 f)
	{
		vec1 -= f;
		vec2 -= f;
		vec3 -= f;
		return *this;
	}

	inline OMatrix3x3 &operator=(float32 f)
	{
		OVector3 temp(f);

		vec1 = temp;
		vec2 = temp;
		vec3 = temp;

		return *this;
	}

	inline OMatrix3x3 &operator/=(float32 f)
	{
		vec1 /= f;
		vec2 /= f;
		vec3 /= f;

		return *this;
	}
};

inline bool operator==(const OMatrix3x3 &a,const OMatrix3x3 &b)
{
	bool result = a.vec1==b.vec1 && a.vec2==b.vec2 && a.vec3==b.vec3 ;
	return result;
}

inline bool operator!=(const OMatrix3x3 &a, const OMatrix3x3 &b)
{
	bool result = a.vec1!=b.vec1 || a.vec2!=b.vec2 || a.vec3!=b.vec3 ;
	return result;
}

/*
inline OMatrix4x4 operator+(float f, OMatrix4x4 &a)
{
	//OMatrix4x4 result = a;
	//result += f;
	//return result;
}*/

#endif/* File Is Over */