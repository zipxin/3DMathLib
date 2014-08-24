//////////////////////////////////////////////////////////////////////////
//File : Only Matrix3x4 ( Only Math Lib)
//Author : Zipxin  [China]
//E-mail: zipxin@163.com
//Project : OnlyGameEngine
//////////////////////////////////////////////////////////////////////////
#ifndef __OM_MATRIX3X4_H__
#define __OM_MATRIX3X4_H__

#include "../OInclude/Common/OnlyGameDefine.h"

#include "../OInclude/Math/OVector4.h"
#include "../OInclude/Math/OMatrix3x3.h"
#include "../OInclude/Math/OMatrix4x4.h"


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
class OMatrix3x4;

//Global//////////////////////////////////////////////////////////////////
extern OMatrix3x4 g_Matrix3x4_Identity;
extern OMatrix3x4 g_Matrix3x4_Zero;

//Define
class OMatrix3x4
{
private:
	union 
	{
		float32 ele_f[3][4];
		int32 ele_i[3][4];
		struct 
		{
			float32 m11, m12, m13, m14;
			float32 m21, m22, m23, m24;
			float32 m31, m32, m33, m34;
		};
		struct
		{
			OVector4 vec1;
			OVector4 vec2;
			OVector4 vec3;
		};
	};

public:
	inline OMatrix3x4(){}

	inline OMatrix3x4(
		float32 f00, float32 f01, float32 f02, float32 f03,
		float32 f10, float32 f11, float32 f12, float32 f13,
		float32 f20, float32 f21, float32 f22, float32 f23
		)
	{
		m11 = f00; m12 = f01; m13 = f02; m14 = f03;
		m21 = f10; m22 = f11; m23 = f12; m24 = f13;
		m31 = f20; m32 = f21; m33 = f22; m34 = f23;
	}

	inline OMatrix3x4(const OMatrix3x4 &m) {
		vec1 = m.vec1;
		vec2 = m.vec2;
		vec3 = m.vec3;
	}


	/// Copy-construct from a 4x4 matrix which is assumed to contain no projection.
	OMatrix3x4(const OMatrix4x4& matrix) :
		m11(matrix.m11),
		m12(matrix.m12),
		m13(matrix.m13),
		m14(matrix.m14),
		m21(matrix.m21),
		m22(matrix.m22),
		m23(matrix.m23),
		m24(matrix.m24),
		m31(matrix.m31),
		m32(matrix.m32),
		m33(matrix.m33),
		m34(matrix.m34)
	{
	}

		/// Construct from a float array.
	OMatrix3x4(const float32* data) :
		m11(data[0]),
		m12(data[1]),
		m13(data[2]),
		m14(data[3]),
		m21(data[4]),
		m22(data[5]),
		m23(data[6]),
		m24(data[7]),
		m31(data[8]),
		m32(data[9]),
		m33(data[10]),
		m34(data[11])
	{
	}


	inline OMatrix3x4
		(OVector4 &v1, OVector4 &v2, OVector4 &v3, OVector4 &v4 = g_Vector4f_Zero)
		:vec1(v1),vec2(v2),vec3(v3){}
	
	inline OMatrix3x4(const OMatrix3x3& m)
		: vec1(m.vec1.GetXf(),m.vec1.GetYf(),m.vec1.GetZf(),0.0f),
		vec2(m.vec2.GetXf(),m.vec2.GetYf(),m.vec2.GetZf(),0.0f),
		vec3(m.vec3.GetXf(),m.vec3.GetYf(),m.vec3.GetZf()){}

/*
	explicit OMatrix4x4(const OMatrix3x3 &m) {
		vec1 = m.vec1;
		vec2 = m.vec2;
		vec3 = m.vec3;
		vec4.Set(0.0f);
	}
*/

	~OMatrix3x4(){};

//////////////////////////////////////////////////////////////////////////
	inline void SetZero()
	{
		m11 = m12 = m13 = m14 = 0.0f;
		m21 = m22 = m23 = m24 = 0.0f;
		m31 = m32 = m33 = m34 = 0.0f;
	}


	inline void SetRow(const int32 row, OVector4 &vec)
	{
		assert( row>=0 && row<3 );
		OVector4 *rows = &vec1;
		rows[row] = vec;
	}

	inline void SetColumn(const int32 column, OVector4 &vec)
	{
		assert( column>=0 && column<4 );
		float *p = &m11 + column;
		p[0] =  vec.GetXf(); 
		p[3] =  vec.GetYf(); 
		p[6] =  vec.GetZf(); 
		p[9] =  vec.GetWf(); 
	}

	inline OVector4 &GetRow(const int32 row)
	{
		assert( row>=0 && row<3 );
		OVector4 *rows = &vec1;
		return rows[row];
	}

	inline const OVector4 &GetRow(const int32 row) const
	{
		assert( row>=0 && row<3 );
		const OVector4 *rows = &vec1;
		return rows[row];
	}

	inline OVector4 GetColumn(const int32 column)
	{
		assert(column>=0 && column<4);
		OVector4 vec;
		float *p = &m11 + column;

		vec.SetXf(p[0]);
		vec.SetYf(p[3]);
		vec.SetZf(p[6]);
		vec.SetWf(p[9]);
		return vec;
	}

	inline const OVector4 GetColumn(const int32 column) const
	{
		assert(column>=0 && column<4);
		OVector4 vec;
		const float *p = &m11 + column;

		vec.SetXf(p[0]);
		vec.SetYf(p[3]);
		vec.SetZf(p[6]);
		vec.SetWf(p[9]);
		return vec;
	}
	

	/// Return the combined rotation and scaling matrix.
	OMatrix3x3 ToMatrix3x3() const
	{
		return OMatrix3x3(
			m11,
			m12,
			m13,
			m21,
			m22,
			m23,
			m31,
			m32,
			m33
			);
	}

	/// Convert to a 4x4 matrix by filling in an identity last row.
	OMatrix4x4 ToMatrix4x4() const
	{
		return OMatrix4x4(
			m11,
			m12,
			m13,
			m14,
			m21,
			m22,
			m23,
			m24,
			m31,
			m32,
			m33,
			m34,
			0.0f,
			0.0f,
			0.0f,
			1.0f
			);
	}
//////////////////////////////////////////////////////////////////////////

	void SetScale(const OVector3& scale)
	{
		m11 = scale.x;
		m22 = scale.y;
		m33 = scale.z;
	}

	void SetScale(float32 scale)
	{
		m11 = scale;
		m22 = scale;
		m33 = scale;
	}

	void SetRotation(const OMatrix3x3& rotation)
	{
		m11 = rotation.m11;
		m12 = rotation.m12;
		m13 = rotation.m13;
		m21 = rotation.m21;
		m22 = rotation.m22;
		m23 = rotation.m23;
		m31 = rotation.m31;
		m32 = rotation.m32;
		m33 = rotation.m33;
	}

	void SetTranslation(const OVector3& translation)
	{
		m14 = translation.x;
		m24 = translation.y;
		m34 = translation.z;
	}



//////////////////////////////////////////////////////////////////////////
//static
	static OMatrix4x4 &GetIdentityMatrix(void)
	{
		return g_Matrix4x4_Identity;
	}

/// Zero matrix.
	static const OMatrix3x4 ZERO;
/// Identity matrix.
	static const OMatrix3x4 IDENTITY;
/*

//////////////////////////////////////////////////////////////////////////
//Operator
*/
	inline OMatrix3x4 &operator-=(const OMatrix3x4 &rhs)
	{
		vec1 -= rhs.vec1;
		vec2 -= rhs.vec2;
		vec3 -= rhs.vec3;
		
		return *this;
	}

	inline OMatrix3x4 &operator-=(const float32 value)
	{
		vec1 -= value;
		vec2 -= value;
		vec3 -= value;

		return *this;
	}

	inline OMatrix3x4 &operator*=(const float32 f)
	{
		vec1 *= f;
		vec2 *= f;
		vec3 *= f;
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

	inline OMatrix3x4 &operator+=(OMatrix3x4 &rhs)
	{
		vec1 += rhs.vec1;
		vec2 += rhs.vec2;
		vec3 += rhs.vec3;

		return *this;
	}

	inline float32 &operator()(int32 x, int32 y)
	{
		assert(x>=0 && x<3);
		assert(y>=0 && y<3);
		return GetRow(x)[y];
	}

	inline OMatrix3x4 &operator=(const OMatrix3x4 &rhs)
	{
		vec1 = rhs.vec1;
		vec2 = rhs.vec2;
		vec3 = rhs.vec3;

		return *this;
	}

	/// Assign from a 3x3 matrix and set the extra elements to identity.
	OMatrix3x4& operator = (const OMatrix3x3& rhs)
	{
		m11 = rhs.m11; m12 = rhs.m12; m13 = rhs.m13; m14 = 0.0;
		m21 = rhs.m21; m22 = rhs.m22; m23 = rhs.m23; m24 = 0.0;
		m31 = rhs.m31; m32 = rhs.m32; m33 = rhs.m33; m34 = 0.0;
		return *this;
	}

	inline OMatrix3x4 &operator=(const OMatrix4x4 &rhs)
	{
		vec1 = rhs.vec1;
		vec2 = rhs.vec2;
		vec3 = rhs.vec3;
		return *this;
	}



	inline OMatrix3x4 &operator=(const float32 f)
	{
		OVector4 temp(f);

		vec1 = temp;
		vec2 = temp;
		vec3 = temp;

		return *this;
	}

	/// 实际上还是与OVector4相乘， 相当于w分量为0
	OVector3 operator * (const OVector3& rhs) const
	{
		return OVector3(
			(m11 * rhs.x + m12 * rhs.y + m13 * rhs.z + m14),
			(m21 * rhs.x + m22 * rhs.y + m23 * rhs.z + m24),
			(m31 * rhs.x + m32 * rhs.y + m33 * rhs.z + m34)
			);
	}

	OVector3 operator * (const OVector4& rhs) const
	{
		return OVector3(
			(m11 * rhs.x + m12 * rhs.y + m13 * rhs.z + m14 * rhs.w),
			(m21 * rhs.x + m22 * rhs.y + m23 * rhs.z + m24 * rhs.w),
			(m31 * rhs.x + m32 * rhs.y + m33 * rhs.z + m34 * rhs.w)
			);
	}

	/// Multiply a 4x4 matrix.
// 	OMatrix4x4 operator * (const OMatrix4x4& rhs) const
// 	{
// 		return OMatrix4x4(
// 			m00_ * rhs.m00_ + m01_ * rhs.m10_ + m02_ * rhs.m20_ + m03_ * rhs.m30_,
// 			m00_ * rhs.m01_ + m01_ * rhs.m11_ + m02_ * rhs.m21_ + m03_ * rhs.m31_,
// 			m00_ * rhs.m02_ + m01_ * rhs.m12_ + m02_ * rhs.m22_ + m03_ * rhs.m32_,
// 			m00_ * rhs.m03_ + m01_ * rhs.m13_ + m02_ * rhs.m23_ + m03_ * rhs.m33_,
// 			m10_ * rhs.m00_ + m11_ * rhs.m10_ + m12_ * rhs.m20_ + m13_ * rhs.m30_,
// 			m10_ * rhs.m01_ + m11_ * rhs.m11_ + m12_ * rhs.m21_ + m13_ * rhs.m31_,
// 			m10_ * rhs.m02_ + m11_ * rhs.m12_ + m12_ * rhs.m22_ + m13_ * rhs.m32_,
// 			m10_ * rhs.m03_ + m11_ * rhs.m13_ + m12_ * rhs.m23_ + m13_ * rhs.m33_,
// 			m20_ * rhs.m00_ + m21_ * rhs.m10_ + m22_ * rhs.m20_ + m23_ * rhs.m30_,
// 			m20_ * rhs.m01_ + m21_ * rhs.m11_ + m22_ * rhs.m21_ + m23_ * rhs.m31_,
// 			m20_ * rhs.m02_ + m21_ * rhs.m12_ + m22_ * rhs.m22_ + m23_ * rhs.m32_,
// 			m20_ * rhs.m03_ + m21_ * rhs.m13_ + m22_ * rhs.m23_ + m23_ * rhs.m33_,
// 			rhs.m30_,
// 			rhs.m31_,
// 			rhs.m32_,
// 			rhs.m33_
// 			);
// 	}


	inline OMatrix3x4 &operator/=(const float32 f)
	{
		assert(f!=0.0f);
		vec1 /= f;
		vec2 /= f;
		vec3 /= f;

		return *this;
	}


};

inline bool operator==(const OMatrix3x4 &a, const OMatrix3x4 &b)
{
	bool result = a.vec1==b.vec1 && a.vec2==b.vec2 && a.vec3==b.vec3 ;
	return result;
}

inline bool operator!=(const OMatrix3x4 &a, const OMatrix3x4 &b)
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


inline OMatrix3x4 operator+(const OMatrix3x4 &a, const OMatrix3x4 &b)
{
	OMatrix3x4 result;

	result.vec1 = a.vec1 + b.vec1;
	result.vec2 = a.vec2 + b.vec2;
	result.vec3 = a.vec3 + b.vec3;

	return result;
}

inline OMatrix3x4 operator-(OMatrix3x4 &a, float f)
{
	OMatrix3x4 result = a;
	result -= f;
	return result;
}

/*

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
*/
#endif/* File Is Over */