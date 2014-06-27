//////////////////////////////////////////////////////////////////////////
//File : Only Matrix4x4 ( Only Math Lib)
//Author : Zipxin  [China]
//Project : OnlyGameEngine
//////////////////////////////////////////////////////////////////////////
#ifndef __OM_MATRIX4X4_H__
#define __OM_MATRIX4X4_H__

#include "OnlyGameDefine.h"

#include "OVector4.h"


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
class OMatrix4x4;

//Global//////////////////////////////////////////////////////////////////
extern OMatrix4x4 g_Matrix4x4_Identity;
extern OMatrix4x4 g_Matrix4x4_Zero;

//Define
class OMatrix4x4
{
private:

	union 
	{
		float32 ele_f[4][4];
		int32 ele_i[4][4];
		struct 
		{
			float32 m11, m12, m13, m14;
			float32 m21, m22, m23, m24;
			float32 m31, m32, m33, m34;
			float32 m41, m42, m43, m44;
		};
		struct
		{
			OVector4 vec1;
			OVector4 vec2;
			OVector4 vec3;
			OVector4 vec4;
		};
	};

public:
	inline OMatrix4x4(){}
	inline OMatrix4x4(
		float32 f00, float32 f01, float32 f02, float32 f03,
		float32 f10, float32 f11, float32 f12, float32 f13,
		float32 f20, float32 f21, float32 f22, float32 f23,
		float32 f30, float32 f31, float32 f32, float32 f33
		)
	{
		m11 = f00; m12 = f01; m13 = f02; m14 = f03;
		m21 = f10; m22 = f11; m23 = f12; m24 = f13;
		m31 = f20; m32 = f21; m33 = f22; m34 = f23;
		m41 = f30; m42 = f31; m43 = f32; m44 = f33;
	}

	inline OMatrix4x4
		(OVector4 &v1, OVector4 &v2, OVector4 &v3, OVector4 &v4 = g_Vector4f_Zero)
		:vec1(v1),vec2(v2),vec3(v3),vec4(v4){}

	inline OMatrix4x4(const OMatrix4x4 &m) {
		vec1 = m.vec1;
		vec2 = m.vec2;
		vec3 = m.vec3;
		vec4 = m.vec4;
	}
/*
	explicit OMatrix4x4(const OMatrix3x3 &m) {
		vec1 = m.vec1;
		vec2 = m.vec2;
		vec3 = m.vec3;
		vec4.Set(0.0f);
	}
*/
	~OMatrix4x4(){};

//////////////////////////////////////////////////////////////////////////
	inline void SetZero()
	{
		m11 = m12 = m13 = m14 = 0.0f;
		m21 = m22 = m23 = m24 = 0.0f;
		m31 = m32 = m33 = m34 = 0.0f;
		m41 = m42 = m43 = m44 = 0.0f;
	}


	inline void SetRow(const int32 row, OVector4 &vec)
	{
		assert( row>=0 && row<4 );
		OVector4 *rows = &vec1;
		rows[row] = vec;
	}

	inline void SetColumn(const int32 column, OVector4 &vec)
	{
		assert( column>=0 && column<4 );
		float *p = &m11 + column;
		p[0] =  vec.GetXf(); 
		p[4] =  vec.GetYf(); 
		p[8] =  vec.GetZf(); 
		p[12] = vec.GetWf(); 
	}

	inline OVector4 &GetRow(const int32 row)
	{
		assert( row>=0 && row<4 );
		OVector4 *rows = &vec1;
		return rows[row];
	}

	inline const OVector4 &GetRow(const int32 row) const
	{
		assert( row>=0 && row<4 );
		const OVector4 *rows = &vec1;
		return rows[row];
	}

	inline OVector4 GetColumn(const int32 column)
	{
		assert(column>=0 && column<4);
		OVector4 vec;
		float *p = &m11 + column;

		vec.SetX(p[0]);
		vec.SetY(p[4]);
		vec.SetZ(p[8]);
		vec.SetW(p[12]);
		return vec;
	}

	inline const OVector4 GetColumn(const int32 column) const
	{
		assert(column>=0 && column<4);
		OVector4 vec;
		const float *p = &m11 + column;

		vec.SetX(p[0]);
		vec.SetY(p[4]);
		vec.SetZ(p[8]);
		vec.SetW(p[12]);
		return vec;
	}

//////////////////////////////////////////////////////////////////////////

	inline OMatrix4x4 &Transpose(void)
	{
		OSwap<float32>(m12,m21);
		OSwap<float32>(m13,m31);
		OSwap<float32>(m14,m41);
		OSwap<float32>(m23,m32);
		OSwap<float32>(m24,m42);
		OSwap<float32>(m34,m43);
		return *this;
	}

	inline void Identity(void)
	{
		*this = g_Matrix4x4_Identity;
	}

	//之所以是快速转置是又原因的
	//正交矩阵
	inline OMatrix4x4 &FastInvert(void)
	{
		OVector4 pos = Vec4_InvertSign(vec4);
		vec4 =  g_Matrix4x4_Identity.vec4;

		Transpose();
		Translate(pos);

		return *this;
	}

	void NoTranslate(void)
	{
		vec4 = GetIdentityMatrix()[3];
	}

	void NoRotate(void)
	{
		vec1 = GetIdentityMatrix()[0];
		vec2 = GetIdentityMatrix()[1];
		vec3 = GetIdentityMatrix()[2];
	}

/*
	inline OVector4 Transform_Vec4(OVector4 &vec)
	{
		OVector4 result = vec * (*this);
		return result;
	}
*/
//Scale
	void Scale(const OVector4 &scale)
	{
		Scale(scale[0], scale[1], scale[2]);
	}

	void Scale(float32 x, float32 y, float32 z)
	{
		vec1 *= x;
		vec2 *= y;
		vec3 *= z;
	}

	void Scale_Replace(const OVector4 &scale)
	{
		Scale_Replace(scale[0], scale[1], scale[2]);
	}

	void Scale_Replace(float32 x, float32 y, float32 z)
	{
		vec1.Set(x, 0, 0, 0);
		vec2.Set(0, y, 0, 0);
		vec3.Set(0, 0, z, 0);
		vec4.Set(0, 0, 0, 1);
	}

//translate
	void Translate(float32 x, float32 y, float32 z)
	{
		vec4 += vec1 * x + vec2 * y + vec3 * z;
	}

	void Translate(OVector4 &v)
	{
		vec4 += vec1 * v.GetXf() + vec2 * v.GetYf() + vec3 * v.GetZf();
	}

	void Translate_Replace(const float32 x, const float32 y, const float32 z)
	{
		Identity();
		vec4[0] = x;
		vec4[1] = y;
		vec4[2] = z;
	}

	void Translate_Replace(OVector4 &v)
	{
		Identity();
		vec4 = v;
	}

//rotate
	void RotateX_Replace( const float radian )
	{
		float32 fSin = OSin(radian);
		float32 fCos = OCos(radian);

		vec1.Set(1.0f,  0.0f,  0.0f, 0.0f);
		vec2.Set(0.0f,  fCos,  fSin, 0.0f);
		vec3.Set(0.0f, -fSin,  fCos, 0.0f);
		vec4.Set(0.0f,  0.0f,  0.0f, 1.0f);
	}

	void RotateX( const float radian )
	{
		float32 Sin = OSin(radian);
		float32 Cos = OCos(radian);

		float Temp10, Temp11, Temp12, Temp13;
		float Temp20, Temp21, Temp22, Temp23;

		Temp10 = m21 * Cos + m31 * Sin;
		Temp11 = m22 * Cos + m32 * Sin;
		Temp12 = m23 * Cos + m33 * Sin;
		Temp13 = m24 * Cos + m34 * Sin;

		Temp20 = m21 *-Sin + m31 * Cos;
		Temp21 = m22 *-Sin + m32 * Cos;
		Temp22 = m23 *-Sin + m33 * Cos;
		Temp23 = m24 *-Sin + m34 * Cos;

		m21 = Temp10;
		m22 = Temp11;
		m23 = Temp12;
		m24 = Temp13;
		m31 = Temp20;
		m32 = Temp21;
		m33 = Temp22;
		m34 = Temp23;
	}


	void RotateY( const float radian )
	{
		float Temp00, Temp01, Temp02, Temp03;
		float Temp20, Temp21, Temp22, Temp23;
		
		float32 Sin = OSin(radian);
		float32 Cos = OCos(radian);

		Temp00 = m11 * Cos - m31 * Sin;
		Temp01 = m12 * Cos - m32 * Sin;
		Temp02 = m13 * Cos - m33 * Sin;
		Temp03 = m14 * Cos - m34 * Sin;

		Temp20 = m11 * Sin + m31 * Cos;
		Temp21 = m12 * Sin + m32 * Cos;
		Temp22 = m13 * Sin + m33 * Cos;
		Temp23 = m14 * Sin + m34 * Cos;

		m11 = Temp00;
		m12 = Temp01;
		m13 = Temp02;
		m14 = Temp03;
		m31 = Temp20;
		m32 = Temp21;
		m33 = Temp22;
		m34 = Temp23;
	}

	void RotateY_Replace( const float radian )
	{
		float32 fSin = OSin(radian);
		float32 fCos = OCos(radian);

		vec1.Set( fCos,  0.0f, -fSin, 0.0f);
		vec2.Set( 0.0f,  1.0f,  0.0f, 0.0f);
		vec3.Set(-fSin,  0.0f,  fCos, 0.0f);
		vec4.Set( 0.0f,  0.0f,  0.0f, 1.0f);
	}

	void RotateZ( const float radian )
	{
		float Temp00, Temp01, Temp02, Temp03;
		float Temp10, Temp11, Temp12, Temp13;

		float32 Sin = OSin(radian);
		float32 Cos = OCos(radian);

		Temp00 = m11 * Cos + m21 * Sin;
		Temp01 = m12 * Cos + m22 * Sin;
		Temp02 = m13 * Cos + m23 * Sin;
		Temp03 = m14 * Cos + m24 * Sin;

		Temp10 = m11 *-Sin + m21 * Cos;
		Temp11 = m12 *-Sin + m22 * Cos;
		Temp12 = m13 *-Sin + m23 * Cos;
		Temp13 = m14 *-Sin + m24 * Cos;

		m11 = Temp00;
		m12 = Temp01;
		m13 = Temp02;
		m14 = Temp03;
		m21 = Temp10;
		m22 = Temp11;
		m23 = Temp12;
		m24 = Temp13;
	}

	void RotateZ_Replace( const float radian )
	{
		float32 fSin = OSin(radian);
		float32 fCos = OCos(radian);

		vec1.Set( fCos,  fSin, 0.0f, 0.0f);
		vec2.Set(-fSin,  fCos, 0.0f, 0.0f);
		vec3.Set( 0.0f,  0.0f, 1.0f, 0.0f);
		vec4.Set( 0.0f,  0.0f, 0.0f, 1.0f);
	}




//////////////////////////////////////////////////////////////////////////
//static
	static OMatrix4x4 &GetIdentityMatrix(void)
	{
		return g_Matrix4x4_Identity;
	}

//////////////////////////////////////////////////////////////////////////
//Operator

	inline OMatrix4x4 &operator-=(const OMatrix4x4 &rhs)
	{
		vec1 -= rhs.vec1;
		vec2 -= rhs.vec2;
		vec3 -= rhs.vec3;
		vec4 -= rhs.vec4;
		return *this;
	}

	inline OMatrix4x4 &operator*=(const float32 f)
	{
		vec1 *= f;
		vec2 *= f;
		vec3 *= f;
		vec4 *= f;
		return *this;
	}

	inline OVector4 &operator[](const int32 row)
	{
		return GetRow(row);
	}

	inline const OVector4 &operator[](const int32 row) const
	{
		return GetRow(row);
	}

	inline OMatrix4x4 &operator+=(OMatrix4x4 &rhs)
	{
		vec1 += rhs.vec1;
		vec2 += rhs.vec2;
		vec3 += rhs.vec3;
		vec4 += rhs.vec4;

		return *this;
	}

	inline float32 &operator()(int32 x, int32 y)
	{
		assert(x>=0 && x<4);
		assert(y>=0 && y<4);
		return GetRow(x)[y];
	}

	inline OMatrix4x4 &operator=(const OMatrix4x4 &rhs)
	{
		vec1 = rhs.vec1;
		vec2 = rhs.vec2;
		vec3 = rhs.vec3;
		vec4 = rhs.vec4;

		return *this;
	}

	inline OMatrix4x4 &operator-=(const float32 f)
	{
		vec1 -= f;
		vec2 -= f;
		vec3 -= f;
		vec4 -= f;
		return *this;
	}

	inline OMatrix4x4 &operator=(const float32 f)
	{
		OVector4 temp(f);

		vec1 = temp;
		vec2 = temp;
		vec3 = temp;
		vec4 = temp;

		return *this;
	}

	inline OMatrix4x4 &operator/=(const float32 f)
	{
		vec1 /= f;
		vec2 /= f;
		vec3 /= f;
		vec4 /= f;

		return *this;
	}
};

inline bool operator==(const OMatrix4x4 &a, const OMatrix4x4 &b)
{
	bool result = a.vec1==b.vec1 && a.vec2==b.vec2 && a.vec3==b.vec3 && a.vec4==b.vec4;
	return result;
}

inline bool operator!=(const OMatrix4x4 &a, const OMatrix4x4 &b)
{
	bool result = a.vec1!=b.vec1 || a.vec2!=b.vec2 || a.vec3!=b.vec3 || a.vec4!=b.vec4;
	return result;
}

/*
inline OMatrix4x4 operator+(float f, OMatrix4x4 &a)
{
	//OMatrix4x4 result = a;
	//result += f;
	//return result;
}*/


inline OMatrix4x4 operator+(const OMatrix4x4 &a, const OMatrix4x4 &b)
{
	OMatrix4x4 result;

	result.vec1 = a.vec1 + b.vec1;
	result.vec2 = a.vec2 + b.vec2;
	result.vec3 = a.vec3 + b.vec3;
	result.vec4 = a.vec4 + b.vec4;

	return result;
}

inline OMatrix4x4 operator-(OMatrix4x4 &a, float f)
{
	OMatrix4x4 result = a;
	result -= f;
	return result;
}



inline OMatrix4x4 operator-(float f, OMatrix4x4 &a)
{
	OMatrix4x4 result = a;
	result -= f;
	return result;
}

inline OMatrix4x4 operator-(const OMatrix4x4 &a, const OMatrix4x4 &b)
{
	OMatrix4x4 result;

	result.vec1 = a.vec1 - b.vec1;
	result.vec2 = a.vec2 - b.vec2;
	result.vec3 = a.vec3 - b.vec3;
	result.vec4 = a.vec4 - b.vec4;

	return result;
}

inline OVector4 operator*(OVector4 &v, OMatrix4x4 &m)
{
	OVector4 result;

	result.x = v.x*m.m11 + v.y*m.m12 + v.z*m.m13 + v.w*m.m14;
	result.y = v.x*m.m12 + v.y*m.m22 + v.z*m.m23 + v.w*m.m42;
	result.z = v.x*m.m13 + v.y*m.m23 + v.z*m.m33 + v.w*m.m43;
	result.w = v.x*m.m14 + v.y*m.m24 + v.z*m.m34 + v.w*m.m44;

	return result;
}
/*
|1  2  3  4 | |1|
|5  6  7  8 | |2|
|9  10 11 12|*|3|
|13 14 15 16| |4|
*/
inline OVector4 operator*(OMatrix4x4 &matrix, OVector4 &vec)
{
	OVector4 result;

	result[0] = Vec4_Dotf(vec, matrix[0]);
	result[1] = Vec4_Dotf(vec, matrix[1]);
	result[2] = Vec4_Dotf(vec, matrix[2]);
	result[3] = Vec4_Dotf(vec, matrix[3]);

	return result;
}



inline OMatrix4x4 operator*(OMatrix4x4 &a, OMatrix4x4 &b)
{
	OMatrix4x4 result;

	result.vec1 = a.vec1 * b;
	result.vec2 = a.vec2 * b;
	result.vec3 = a.vec3 * b;
	result.vec4 = a.vec4 * b;

	return result;
}

#endif/* File Is Over */