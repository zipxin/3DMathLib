//////////////////////////////////////////////////////////////////////////
//File : Only Matrix3x3 ( Only Math Lib)
//Author : Zipxin 
//E-mail: zipxin@163.com
//Project : OnlyGameEngine
//////////////////////////////////////////////////////////////////////////
#ifndef __OM_MATRIX3X3_H__
#define __OM_MATRIX3X3_H__

#include "../OInclude/Common/OnlyGameDefine.h"

//Declare/////////////////////////////////////////////////////////////////
class OMatrix3x3;
class OVector3;

#include "../OInclude/Math/OVector3.h"
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


//Global//////////////////////////////////////////////////////////////////


//Define
class OMatrix3x3
{
public:

	union 
	{
		float32 ele_f[3][3];
		int32 ele_i[3][3]; //一般不用
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

	inline explicit  OMatrix3x3(const float32* data) :
			m11(data[0]), m12(data[1]), m13(data[2]),
			m21(data[3]), m22(data[4]), m23(data[5]),
			m31(data[6]), m32(data[7]), m33(data[8]) {}

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

	inline void SetColumn(int column,const OVector3 &vec)
	{
		assert( column>=0 && column<3 );
		float *p = &m11 + column;
		p[0] =  vec.GetXf(); 
		p[3] =  vec.GetYf(); 
		p[6] =  vec.GetZf(); 
	}

	void FromAxes(const OVector3& xAxis, const OVector3& yAxis, const OVector3& zAxis)
	{
		SetColumn(0,xAxis);
		SetColumn(1,yAxis);
		SetColumn(2,zAxis);
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

		vec.SetXf(p[0]);
		vec.SetYf(p[3]);
		vec.SetZf(p[6]);
		return vec;
	}

	// 得到绕相应轴的旋转矩阵
	/** 得到这样一个3*3矩阵：它乘以对象矩阵后，让对象矩阵得到绕X轴旋转radian弧度的效果 */
	OMatrix3x3 RotateX_Replace(float radian);
	/** 得到这样一个3*3矩阵：它乘以对象矩阵后，让对象矩阵得到绕Y轴旋转radian弧度的效果 */
	OMatrix3x3 RotateY_Replace(float radian);
	/** 得到这样一个3*3矩阵：它乘以对象矩阵后，让对象矩阵得到绕Z轴旋转radian弧度的效果 */
	OMatrix3x3 RotateZ_Replace(float radian);
	/** 得到这样一个3*3矩阵：它乘以对象矩阵后，让对象矩阵得到分别绕XYZ三轴旋转参数弧度后的效果 */
	OMatrix3x3 RotateXYZ_Replace(float radianX, float radianY,  float radianZ);	


	// 自身旋转 , 输入绕相应轴的弧度值
	/** 绕X轴自身旋转 弧度radian，返回旋转后3*3矩阵的指针 */
	const OMatrix3x3& RotateX(float radian);
	/** 绕Y轴自身旋转 弧度radian，返回旋转后3*3矩阵的指针 */
	const OMatrix3x3& RotateY(float radian);
	/** 绕Z轴自身旋转 弧度radian，返回旋转后3*3矩阵的指针 */
	const OMatrix3x3& RotateZ(float radian);
	/** 分别绕XYZ三轴自身旋转 参数弧度后，返回旋转后3*3矩阵的指针 */
	const OMatrix3x3& RotateXYZ(float radianX, float radianY,  float radianZ);



	/** 求3*3矩阵的行列式值 */
	float32 Determinant () const;

//////////////////////////////////////////////////////////////////////////
	/** 对3*3矩阵求逆矩阵,如果逆矩阵存在，则返回逆矩阵；
	 *  如果逆矩阵不存在，则返回零矩阵与原矩阵相乘为O的矩阵.
	 * @note: 函数是const的 
	 */
	OMatrix3x3 Inverse() const;
	
	/** 对3*3矩阵求转置矩阵 */
	inline OMatrix3x3 &Transpose(void)
	{
		OSwap<float32>(m12,m21);
		OSwap<float32>(m13,m31);
		OSwap<float32>(m23,m32);
		return *this;

// 		return Matrix3(
// 			m00_,
// 			m10_,
// 			m20_,
// 			m01_,
// 			m11_,
// 			m21_,
// 			m02_,
// 			m12_,
// 			m22_
// 			);
	}

	inline void Identity(void)
	{
		*this = IDENTITY;
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
		m11 = x;
		m22 = y;
		m33 = z;
	}

	void Scale_Replace(float32 f)
	{
		m11 = f;
		m22 = f;
		m33 = f;
	}

	static void BulkTranspose(float32* dest, const float32* src, unsigned count)
	{
		for (unsigned i = 0; i < count; ++i)
		{
			dest[0] = src[0];
			dest[1] = src[3];
			dest[2] = src[6];
			dest[3] = src[1];
			dest[4] = src[4];
			dest[5] = src[7];
			dest[6] = src[2];
			dest[7] = src[5];
			dest[8] = src[8];

			dest += 9;
			src += 9;
		}
	}

	bool Equals(const OMatrix3x3& rhs) const
	{
		return vec1.Equals(rhs.vec1) && vec2.Equals(rhs.vec2) && vec3.Equals(rhs.vec3);
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

	/** <<操作符重载，按行输出4*4矩阵 */
	inline friend std::ostream& operator <<
		( std::ostream& o, const OMatrix3x3& m )
	{
		o << "Matrix3x3(";
		for (int i = 0; i < 3; ++i)
		{
			o << " row" << (unsigned)i << "{";
			for(int j = 0; j < 3; ++j)
			{
				o << m[i][j] << " ";
			}
			o << "}";
		}
		o << ")";
		return o;
	}
//////////////////////////////////////////////////////////////////////////
//static
	static const OMatrix3x3 &GetIdentityMatrix3x3(void)
	{
		return IDENTITY;
	}

	/// Zero matrix.
	static const OMatrix3x3 ZERO;
	/// Identity matrix.
	static const OMatrix3x3 IDENTITY;

//////////////////////////////////////////////////////////////////////////
//Operator

	inline OMatrix3x3 &operator-=(const OMatrix3x3 &rhs)
	{
		vec1 -= rhs.vec1;
		vec2 -= rhs.vec2;
		vec3 -= rhs.vec3;
		return *this;
	}

	inline OMatrix3x3 &operator+=(OMatrix3x3 &rhs)
	{
		vec1 += rhs.vec1;
		vec2 += rhs.vec2;
		vec3 += rhs.vec3;

		return *this;
	}


	OVector3 operator * (const OVector3& rhs) const
	{
		return OVector3(
			Vec3_Dotf(vec1,rhs),
			Vec3_Dotf(vec2,rhs),
			Vec3_Dotf(vec3,rhs)
			);
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


	inline float32 &operator()(int x, int y)
	{
		assert(x>=0 && x<4);
		assert(y>=0 && y<4);
		return GetRow(x)[y];
	}

	inline OMatrix3x3 &operator=(const OMatrix3x3 &rhs)
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
		assert(f != 0.0f && "非法除数");
		vec1 /= f;
		vec2 /= f;
		vec3 /= f;

		return *this;
	}


	//-----------------------------------------------------------------------
	OMatrix3x3 operator -()
	{
		for (int iRow = 0; iRow < 3; iRow++)
		{
			for (int iCol = 0; iCol < 3; iCol++)
				ele_f[iRow][iCol] = -ele_f[iRow][iCol];
		}
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

inline OMatrix3x3 operator+(OMatrix3x3 &lhs, OMatrix3x3 &rhs)
{
	OMatrix3x3 result;
	result.vec1 = lhs.vec1 + rhs.vec1;
	result.vec2 = lhs.vec2 + rhs.vec2;
	result.vec3 = lhs.vec3 + rhs.vec3;

	return result;
}

inline OMatrix3x3 operator-(OMatrix3x3 &lhs, OMatrix3x3 &rhs)
{
	OMatrix3x3 result;
	result.vec1 = lhs.vec1 - rhs.vec1;
	result.vec2 = lhs.vec2 - rhs.vec2;
	result.vec3 = lhs.vec3 - rhs.vec3;
	return result;
}
// 
// inline OVector3 operator* (const OVector3& rkPoint, const OMatrix3x3 lhs) const
// {
// 	OVector3 kProd;
// 	for (int iCol = 0; iCol < 3; iCol++)
// 	{
// 		kProd[iCol] =
// 			rkPoint[0] * lhs.ele_f[0][iCol]+
// 			rkPoint[1] * lhs.ele_f[1][iCol]+
// 			rkPoint[2] * lhs.ele_f[2][iCol];
// 	}
// 	return kProd;
// }

inline OMatrix3x3 operator*(OMatrix3x3 &lhs, float32 &rhs)
{
	OMatrix3x3 result;
	result.vec1 = lhs.vec1 * rhs;
	result.vec2 = lhs.vec2 * rhs;
	result.vec3 = lhs.vec3 * rhs;
	return result;
}

inline OMatrix3x3 operator*(float32 &lhs,OMatrix3x3 &rhs)
{
	OMatrix3x3 result;
	result.vec1 = lhs * rhs.vec1;
	result.vec2 = lhs * rhs.vec2;
	result.vec3 = lhs * rhs.vec3;
	return result;
}

//待优化
inline OMatrix3x3 operator*(OMatrix3x3 &lhs, OMatrix3x3 &rhs)
{
	return OMatrix3x3(
		lhs.m11 * rhs.m11 + lhs.m12 * rhs.m21 + lhs.m13 * rhs.m31,
		lhs.m11 * rhs.m12 + lhs.m12 * rhs.m22 + lhs.m13 * rhs.m32,
		lhs.m11 * rhs.m13 + lhs.m12 * rhs.m23 + lhs.m13 * rhs.m33,
		lhs.m21 * rhs.m11 + lhs.m22 * rhs.m21 + lhs.m23 * rhs.m31,
		lhs.m21 * rhs.m12 + lhs.m22 * rhs.m22 + lhs.m23 * rhs.m32,
		lhs.m21 * rhs.m13 + lhs.m22 * rhs.m23 + lhs.m23 * rhs.m33,
		lhs.m31 * rhs.m11 + lhs.m32 * rhs.m21 + lhs.m33 * rhs.m31,
		lhs.m31 * rhs.m12 + lhs.m32 * rhs.m22 + lhs.m33 * rhs.m32,
		lhs.m31 * rhs.m13 + lhs.m32 * rhs.m23 + lhs.m33 * rhs.m33
		);
}



/*
inline OMatrix4x4 operator+(float f, OMatrix4x4 &a)
{
	//OMatrix4x4 result = a;
	//result += f;
	//return result;
}*/

#endif/* File Is Over */